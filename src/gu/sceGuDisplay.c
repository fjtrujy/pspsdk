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

int sceGuDisplay(int state)
{
	int prev_state;

	if (state == GU_DISPLAY_OFF) {
		sceDisplaySetFrameBuf(NULL, 0, __guSettings.frameBuf.fpf, PSP_DISPLAY_SETBUF_NEXTVSYNC);
	} else {
		sceDisplaySetFrameBuf((void *)(__guSettings.ge_edram_address + __guSettings.frameBuf.dbp), __guSettings.frameBuf.fbw, __guSettings.frameBuf.fpf, PSP_DISPLAY_SETBUF_NEXTVSYNC);
	}
	prev_state = __guSettings.disp_sw;
	__guSettings.disp_sw = state;

	return prev_state;
}

int guGetDisplayState()
{
	return __guSettings.disp_sw;
}
