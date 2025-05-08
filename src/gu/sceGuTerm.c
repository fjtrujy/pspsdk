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

#define ERROR_NOT_INITIALIZED 0x80000001

int sceGuTerm(void)
{
	if (__guSettings.library_initialized==0) {
		return ERROR_NOT_INITIALIZED;
	}
	sceKernelDeleteEventFlag(__intrParam.evid);
	sceGeUnsetCallback(__guSettings.intrId);
	__intrParam.evid  = -1;
	__guSettings.intrId  = -1;
	__guSettings.context = NULL;
	__guSettings.library_initialized = 0;
	return 0;
}
