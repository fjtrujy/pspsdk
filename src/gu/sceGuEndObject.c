/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

int sceGuEndObject(void)
{
	int res;
	res = sceGupEndObject(__guSettings.context);
	if (res < 0)
	{
		return res;
	}

	if (__guSettings.list_mode == GU_DIRECT)
	{
		void *pCurrent = sceGupGetCurrentAddr(__guSettings.context);
		res = sceGeListUpdateStallAddr(__guSettings.queid[0], pCurrent);
		if (res < 0)
		{
			return res;
		}
	}

	return 0;
}