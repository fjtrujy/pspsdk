/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * PixelMask sample - Demonstrates sceGuPixelMask channel write-masking
 */

#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspdebug.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include <pspctrl.h>
#include <pspgu.h>
#include <psprtc.h>

#include "../common/callbacks.h"
#include "smile.h"

PSP_MODULE_INFO("PixelMask Sample", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

static unsigned int __attribute__((aligned(16))) list[1024];

#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)

#define COLOR_BLACK_NO_ALPHA 0x00000000
#define COLOR_GREEN_NO_ALPHA 0x0000FF00
#define COLOR_BLUE_NO_ALPHA 0x00FF0000
#define COLOR_RED_NO_ALPHA 0x000000FF

#define COLOR_BLACK 0xFF000000
#define COLOR_GREEN 0xFF00FF00
#define COLOR_BLUE 0xFFFF0000
#define COLOR_RED 0xFF0000FF

struct Vertex
{
    float u, v;
    uint32_t color;
    float x, y, z;
};

struct VertexNoTex
{
    uint32_t color;
    float x, y, z;
};

// Draw a full-screen sprite mapping only the first 6 texels horizontally (6 vertical slices)
static void drawFullscreenTexture(uint32_t color, uint32_t textureWidth, uint32_t textureHeight)
{
    struct Vertex *vertices = (struct Vertex *)sceGuGetMemory(2 * sizeof(struct Vertex));

    vertices[0].u = 0.0f;
    vertices[0].v = 0.0f;
    vertices[0].x = 0.0f;
    vertices[0].y = 0.0f;
    vertices[0].z = 0.0f;
    vertices[0].color = color;

    vertices[1].u = (float)textureWidth;
    vertices[1].v = (float)textureHeight;
    vertices[1].x = (float)SCR_WIDTH;
    vertices[1].y = (float)SCR_HEIGHT;
    vertices[1].z = 0.0f;
    vertices[1].color = color;

    sceGuEnable(GU_TEXTURE_2D);
    sceGuDrawArray(GU_SPRITES, GU_TEXTURE_32BITF | GU_COLOR_8888 | GU_VERTEX_32BITF | GU_TRANSFORM_2D, 2, 0, vertices);
    sceGuDisable(GU_TEXTURE_2D);
}

static void drawFullscreenSpriteNoTex(uint32_t color)
{
    struct VertexNoTex *vertices = (struct VertexNoTex *)sceGuGetMemory(2 * sizeof(struct VertexNoTex));
    vertices[0].color = color;
    vertices[0].x = 0.0f;
    vertices[0].y = 0.0f;
    vertices[0].z = 0.0f;

    vertices[1].x = (float)SCR_WIDTH;
    vertices[1].y = (float)SCR_HEIGHT;
    vertices[1].z = 0.0f;
    vertices[1].color = color;

    sceGuDrawArray(GU_SPRITES, GU_COLOR_8888 | GU_VERTEX_32BITF | GU_TRANSFORM_2D, 2, 0, vertices);
}

int main(int argc, char *argv[])
{
    int drawFormat = GU_PSM_8888;

    pspDebugScreenInit();
    setupCallbacks();

    // Setup GU

    void *fbp0 = guGetStaticVramBuffer(BUF_WIDTH, SCR_HEIGHT, drawFormat);
    void *fbp1 = guGetStaticVramBuffer(BUF_WIDTH, SCR_HEIGHT, drawFormat);
    void *targetTexture = guGetStaticVramBuffer(BUF_WIDTH, SCR_HEIGHT, drawFormat);

    sceGuInit();

    sceGuStart(GU_DIRECT, list);
    sceGuDrawBuffer(drawFormat, fbp0, BUF_WIDTH);
    sceGuDispBuffer(SCR_WIDTH, SCR_HEIGHT, fbp1, BUF_WIDTH);
    sceGuOffset(2048 - (SCR_WIDTH / 2), 2048 - (SCR_HEIGHT / 2));
    sceGuViewport(2048, 2048, SCR_WIDTH, SCR_HEIGHT);
    sceGuScissor(0, 0, SCR_WIDTH, SCR_HEIGHT);
    sceGuEnable(GU_SCISSOR_TEST);
    sceGuClear(GU_COLOR_BUFFER_BIT | GU_DEPTH_BUFFER_BIT);

    sceGuDisable(GU_ALPHA_TEST);
    sceGuDisable(GU_STENCIL_TEST);
    sceGuShadeModel(GU_SMOOTH);

    sceGuTexFunc(GU_TFX_REPLACE, GU_TCC_RGBA);
    sceGuTexFilter(GU_NEAREST, GU_NEAREST);

    sceGuFinish();
    sceGuSync(GU_SYNC_FINISH, GU_SYNC_WHAT_DONE);

    sceDisplayWaitVblankStart();
    sceGuDisplay(GU_TRUE);

    sceKernelDcacheWritebackAll();

    pspDebugScreenInitEx(fbp0, drawFormat, 1);

    while (running())
    {
        sceGuStart(GU_DIRECT, list);

        // Set the texture as render target
        sceGuDrawBufferList(drawFormat, targetTexture, BUF_WIDTH);

        // sceGuClearStencil(0xFF);
        // sceGuClear(GU_STENCIL_BUFFER_BIT);

        // Draw a solid BLACK no alpha sprite
        sceGuDisable(GU_BLEND);
        drawFullscreenSpriteNoTex(COLOR_BLUE);

        // Reset the pixel mask and disable blending
        sceGuPixelMask(0);
        sceGuDisable(GU_BLEND);

        // Put back the original backbuffer
        sceGuDrawBufferList(drawFormat, fbp0, BUF_WIDTH);

        // Draw a solid RED sprite on the original backbuffer
        drawFullscreenSpriteNoTex(COLOR_RED);

        // Draw the content of the rendered texture
        sceGuTexMode(drawFormat, 0, 0, 0);
        sceGuTexImage(0, BUF_WIDTH, BUF_WIDTH, BUF_WIDTH, sceGeEdramGetAddr() + (int)targetTexture);
        drawFullscreenTexture(0xFFFFFFFF, SCR_WIDTH, SCR_HEIGHT);

        sceGuFinish();
        sceGuSync(GU_SYNC_FINISH, GU_SYNC_WHAT_DONE);

        // HUD text
        pspDebugScreenSetOffset((int)fbp0);
        pspDebugScreenSetXY(0, 0);
        // pspDebugScreenPrintf("PixelMask + Blend demo (ABGR_8888)");
        // pspDebugScreenPrintf("Background: green (A=0)\n");
        // pspDebugScreenPrintf("Alpha slices: 0x00,0x33,0x66,0x99,0xCC,0xFF left->right\n");


        printf("First pixel of target texture: 0x%08X\n", *(uint32_t*)(sceGeEdramGetAddr() + (int)targetTexture));
        sceDisplayWaitVblankStart();
        fbp0 = sceGuSwapBuffers();
    }

    sceGuTerm();

    sceKernelExitGame();
    return 0;
}
