/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuDrawBuffer(int psm, void *fbp, int frame_width)
{
	int i;

	sceGupDrawBuffer(__guSettings.context, psm, fbp, frame_width);

	/* updates all list_mode's draw buffer */
	for (i=0; i<LISTMODE_MAX; i++) {
		sceGupSetFrameBuffer(&__guSettings.listctx[i].packet, __guSettings.frameBuf.fpf, __guSettings.frameBuf.sw, __guSettings.frameBuf.sh);
	}

	/* global variable __guSettings.frameBuf is not independent for each mode  */
	__guSettings.frameBuf.fpf = psm;
	__guSettings.frameBuf.wbp = (unsigned int)fbp;
	__guSettings.frameBuf.fbw = frame_width;

	/* conditionally approve when depth buffer has not been set */
	if ((__guSettings.frameBuf.zbp == 0) && (__guSettings.frameBuf.sh != 0)) {
		__guSettings.frameBuf.zbp = __guSettings.frameBuf.wbp;
		__guSettings.frameBuf.zbp += __guSettings.frameBuf.sh * (frame_width * 2) * 2; /* draw disp depth */
	}
	if (__guSettings.frameBuf.zbw == 0) {
		__guSettings.frameBuf.zbw = frame_width;
	}
}
