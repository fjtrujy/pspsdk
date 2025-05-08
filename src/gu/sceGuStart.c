/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

#include <pspkernel.h>
#include <pspge.h>
#include <pspuser.h>

#define ERROR_NOT_INITIALIZED 0x80000002
#define ERROR_BUSY 0x80000003

static SceGeStack g_SignalCallStack[STACK_MAX];

static PspGeListArgs g_ListOptImmediate = {
	.size        = sizeof(PspGeListArgs),
	.context  = NULL,
	.numStacks = STACK_MAX,
	.stacks   = g_SignalCallStack
};

int sceGuStart(int ctype, void *list, int size)
{
	int intr;

	if (__guSettings.library_initialized==0) {
		__guSettings.context = NULL;
		return (ERROR_NOT_INITIALIZED);
	}

	intr = sceKernelCpuSuspendIntr();

	// setup display list
	if (!(__guSettings.listctx[__guSettings.list_mode].prevmode < 0)) {
		sceKernelCpuResumeIntr(intr);
		__guSettings.context = NULL;
		return (ERROR_BUSY);
	}
	__guSettings.context = &__guSettings.listctx[__guSettings.list_mode].packet;
	__guSettings.listctx[__guSettings.list_mode].prevmode = __guSettings.list_mode;
	__guSettings.list_mode = ctype;
	sceKernelCpuResumeIntr(intr);

	sceGupStart(__guSettings.context, list, size);

	if (__guSettings.list_mode == GU_DIRECT) {
		int res;
		__intrParam.count = 0;
		res = sceGeListEnQueue(sceGupGetStartAddr(__guSettings.context), sceGupGetCurrentAddr(__guSettings.context), __guSettings.intrId, &g_ListOptImmediate);
		if (res < 0) {
			return res;
		}
		__guSettings.queid[0] = res;
	}

	if (__guSettings.dither_initialized==0) {
		static const ScePspIMatrix4 dither = {
			{-4,  0, -3,  1},
			{ 2, -2,  3, -1},
			{-3,  1, -4,  0},
			{ 3, -1,  2, -2}
		};
		sceGuSetDither(&dither);
		sceGuPatchDivide(16, 16);
		sceGuColorMaterial(GU_AMBIENT | GU_DIFFUSE | GU_SPECULAR);

		sceGuSpecular(1.0f);
		sceGuTexScale(1.0f, 1.0f);
		__guSettings.dither_initialized = 1;
	}

	if ((__guSettings.list_mode == GU_DIRECT) && (__guSettings.frameBuf.fbw != 0)) {
		sceGupSetFrameBuffer(__guSettings.context, __guSettings.frameBuf.fpf, __guSettings.frameBuf.sw, __guSettings.frameBuf.sh);
		sceGupDrawBuffer(__guSettings.context, __guSettings.frameBuf.fpf, (void *)__guSettings.frameBuf.wbp, __guSettings.frameBuf.fbw);
	}

	return 0;
}