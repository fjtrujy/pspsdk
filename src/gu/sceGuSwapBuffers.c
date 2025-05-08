/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

#include <pspkernel.h>
#include <pspdisplay.h>

void *sceGuSwapBuffers(void)
{
	// TODO: Implement swap buffers callback

	// if (__guSettings.swap_buffers_callback)
	// {
	// 	__guSettings.swap_buffers_callback(&__guSettings.frameBuf.dbp, &__guSettings.frameBuf.wbp);
	// } else {
	// 	unsigned int tmp = __guSettings.frameBuf.dbp;
	// 	__guSettings.frameBuf.dbp = __guSettings.frameBuf.wbp;
	// 	__guSettings.frameBuf.wbp = tmp;
	// }

	if (__guSettings.disp_sw == GU_DISPLAY_ON) {
		sceDisplaySetFrameBuf((void *)(__guSettings.ge_edram_address + __guSettings.frameBuf.dbp), __guSettings.frameBuf.fbw, __guSettings.frameBuf.fpf, __guSettings.swap_buffers_behaviour);
	}
	
	return ((void *)__guSettings.frameBuf.wbp);
}

void guSwapBuffersBehaviour(int behaviour)
{
	__guSettings.swap_buffers_behaviour = behaviour;
}

void guSwapBuffersCallback(GuSwapBuffersCallback callback)
{
	__guSettings.swap_buffers_callback = callback;
}
