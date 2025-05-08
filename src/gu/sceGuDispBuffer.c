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


static void sceGuDispBufferExt(int fpf, int width, int height, void *dispbp, int dispbw)
{
	__guSettings.frameBuf.fpf = fpf;
	__guSettings.frameBuf.sw  = width;
	__guSettings.frameBuf.sh  = height;
	__guSettings.frameBuf.dbp = (unsigned int)dispbp;
	__guSettings.frameBuf.fbw = dispbw;

	sceDisplaySetMode(PSP_DISPLAY_MODE_LCD, __guSettings.frameBuf.sw, __guSettings.frameBuf.sh);
	if (__guSettings.disp_sw == GU_DISPLAY_ON) {
		sceDisplaySetFrameBuf((void *)(__guSettings.ge_edram_address + __guSettings.frameBuf.dbp), dispbw, fpf, PSP_DISPLAY_SETBUF_NEXTVSYNC);
	}
}

void sceGuDispBuffer(int width, int height, void *dispbp, int dispbw)
{
	int i;

	sceGuDispBufferExt(__guSettings.frameBuf.fpf, width, height, dispbp, dispbw);

	/* updates all list_mode's draw buffer */
	for (i=0; i<LISTMODE_MAX; i++) {
		sceGupSetFrameBuffer(&__guSettings.listctx[i].packet, __guSettings.frameBuf.fpf, __guSettings.frameBuf.sw, __guSettings.frameBuf.sh);
	}
}
