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
 
 PSP_MODULE_INFO("PixelMask Sample", 0, 1, 1);
 PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);
 
 static unsigned int __attribute__((aligned(16))) list[1024];
 
 #define BUF_WIDTH (512)
 #define SCR_WIDTH (480)
 #define SCR_HEIGHT (272)
 
 #define COLOR_BLACK 0x00000000
 #define COLOR_GREEN_NO_ALPHA 0x0000FF00
 #define COLOR_BLUE_NO_ALPHA 0x00FF0000
 
 // 8x1 (power-of-two: 8 wide) texture storing a 6-step alpha ramp in the alpha channel of red texels.
 // Format is ABGR_8888: 0xAABBGGRR. Only the first 6 texels are used; the last two are duplicates.
 static uint32_t __attribute__((aligned(16))) alphaGradient8x1[8] = {
     0x000000FF, // A=0x00, R=0xFF
     0x330000FF, // A=0x33
     0x660000FF, // A=0x66
     0x990000FF, // A=0x99
     0xCC0000FF, // A=0xCC
     0xFF0000FF, // A=0xFF
     0xFF0000FF, // pad
     0xFF0000FF  // pad
 };
 
 struct Vertex
 {
     float u, v;
     float x, y, z;
 };
 
 struct VertexNoTex
 {
     float x, y, z;
 };
 
 // Draw a full-screen sprite mapping only the first 6 texels horizontally (6 vertical slices)
 static void drawFullscreenSpriteU0to6(void)
 {
     struct Vertex *vertices = (struct Vertex *)sceGuGetMemory(2 * sizeof(struct Vertex));
 
     vertices[0].u = 0.0f;
     vertices[0].v = 0.0f;
     vertices[0].x = 0.0f;
     vertices[0].y = 0.0f;
     vertices[0].z = 0.0f;
 
     vertices[1].u = 6.0f; // use only first 6 texels of the 8-wide texture
     vertices[1].v = 1.0f;
     vertices[1].x = (float)SCR_WIDTH;
     vertices[1].y = (float)SCR_HEIGHT;
     vertices[1].z = 0.0f;
 
     sceGuDrawArray(GU_SPRITES, GU_TEXTURE_32BITF | GU_VERTEX_32BITF | GU_TRANSFORM_2D, 2, 0, vertices);
 }
 
 // Draw a full-screen sprite without textures (positions only)
 static void drawFullscreenSpriteNoTex(void)
 {
     struct VertexNoTex *vertices = (struct VertexNoTex *)sceGuGetMemory(2 * sizeof(struct VertexNoTex));
     vertices[0].x = 0.0f; 
     vertices[0].y = 0.0f; 
     vertices[0].z = 0.0f;
     vertices[1].x = (float)SCR_WIDTH; 
     vertices[1].y = (float)SCR_HEIGHT; 
     vertices[1].z = 0.0f;
     sceGuDrawArray(GU_SPRITES, GU_VERTEX_32BITF | GU_TRANSFORM_2D, 2, 0, vertices);
 }
 
 int main(int argc, char *argv[])
 {
     int drawFormat = GU_PSM_8888;
 
     pspDebugScreenInit();
     setupCallbacks();
 
     // Setup GU
 
     void *fbp0 = guGetStaticVramBuffer(BUF_WIDTH, SCR_HEIGHT, drawFormat);
     void *fbp1 = guGetStaticVramBuffer(BUF_WIDTH, SCR_HEIGHT, drawFormat);
 
     sceGuInit();
 
     sceGuStart(GU_DIRECT, list);
     sceGuDrawBuffer(drawFormat, fbp0, BUF_WIDTH);
     sceGuDispBuffer(SCR_WIDTH, SCR_HEIGHT, fbp1, BUF_WIDTH);
     sceGuOffset(2048 - (SCR_WIDTH / 2), 2048 - (SCR_HEIGHT / 2));
     sceGuViewport(2048, 2048, SCR_WIDTH, SCR_HEIGHT);
     sceGuScissor(0, 0, SCR_WIDTH, SCR_HEIGHT);
     sceGuEnable(GU_SCISSOR_TEST);
     sceGuEnable(GU_TEXTURE_2D);
     sceGuClear(GU_COLOR_BUFFER_BIT | GU_DEPTH_BUFFER_BIT);
 
     // Setup 8x1 ABGR_8888 texture holding the alpha gradient
     sceGuTexMode(GU_PSM_8888, 0, 0, 0);
     sceGuTexImage(0, 8, 1, 8, alphaGradient8x1);
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
         // Pass 1: clear + alpha write
         sceGuStart(GU_DIRECT, list);
 
         sceGuClearColor(COLOR_GREEN_NO_ALPHA);
         sceGuClear(GU_COLOR_BUFFER_BIT);
 
         // Write only ALPHA from the 6x1 gradient stretched over the screen
         // 0x00FFFFFF blocks RGB, allows A
         sceGuPixelMask(0x00FFFFFF);
         sceGuEnable(GU_TEXTURE_2D);
         drawFullscreenSpriteU0to6();
         sceGuPixelMask(0);
 
         // Pass 2: visualize alpha = Green * DstAlpha
         sceGuEnable(GU_BLEND);
         sceGuBlendFunc(GU_ADD, GU_DST_ALPHA, GU_FIX, 0, 0);
         // Prevent alpha from being altered during this visualization pass
         sceGuPixelMask(0xFF000000);
         sceGuDisable(GU_TEXTURE_2D);
         sceGuColor(COLOR_BLUE_NO_ALPHA);
         drawFullscreenSpriteNoTex();
         sceGuPixelMask(0);
         sceGuDisable(GU_BLEND);
 
         sceGuFinish();
         sceGuSync(GU_SYNC_FINISH, GU_SYNC_WHAT_DONE);
 
         // HUD text
         pspDebugScreenSetOffset((int)fbp0);
         pspDebugScreenSetXY(0, 0);
         pspDebugScreenPrintf("PixelMask + Blend demo (ABGR_8888)\n");
         pspDebugScreenPrintf("Background: green (A=0)\n");
         pspDebugScreenPrintf("Alpha slices: 0x00,0x33,0x66,0x99,0xCC,0xFF left->right\n");
 
         sceDisplayWaitVblankStart();
         fbp0 = sceGuSwapBuffers();
     }
 
     sceGuTerm();
 
     sceKernelExitGame();
     return 0;
 }
 