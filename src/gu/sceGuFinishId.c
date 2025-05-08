/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"
#include <pspdisplay.h>
#include <pspuser.h>

#define ERROR_BUSY 0x80020001

int sceGuFinishId(unsigned int id)
{
	int ret;
	int intr;
	int prevmode;

	if (sceGupGetBoundingBoxNest(__guSettings.context)!=0) {
		return ERROR_BUSY;
	}	

	switch (__guSettings.list_mode)
	{
	case GU_DIRECT:
		sceGupFinishId(__guSettings.context, id);
		ret = _sceGuUpdateStallAddr();
		if (ret < 0)
		{
			return ret;
		}
		break;
	case GU_SEND:
		sceGupFinishId(__guSettings.context, id);
		break;
	case GU_CALL:
		if (__guSettings.call_mode == GU_CALL_SIGNAL)
		{
			sceGupSignalRet(__guSettings.context, id);
		}
		else
		{
			sceGupRet(__guSettings.context);
		}
		break;
	default:
		return SCE_DISPLAY_ERROR_ARGUMENT;
	}

	ret = sceGupGetCurrentSize(__guSettings.context);	

	// go to parent list
	intr = sceKernelCpuSuspendIntr();
	prevmode = __guSettings.listctx[__guSettings.list_mode].prevmode;
	__guSettings.listctx[__guSettings.list_mode].prevmode = -1;
	__guSettings.list_mode = prevmode;

	if (prevmode < 0) {
		__guSettings.context  = NULL;
	} else {
		__guSettings.context  = &__guSettings.listctx[__guSettings.list_mode].packet;
	}
	sceKernelCpuResumeIntr(intr);
	return ret;
}