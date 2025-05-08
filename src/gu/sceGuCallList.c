/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

int sceGuCallList(const void *list)
{
	int res;
	unsigned int list_addr = (unsigned int)list;

	if (__guSettings.call_mode == GU_CALL_SIGNAL)
	{
		sceGupSignalCall(__guSettings.context, list_addr);
	}
	else
	{
		sceGupCall(__guSettings.context, list_addr);
	}

	res = _sceGuUpdateStallAddr();
	if (res < 0)
	{
		return res;
	}
	return 0;
}
