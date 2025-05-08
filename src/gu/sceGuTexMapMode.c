/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuTexMapMode(int mode, unsigned int lu, unsigned int lv)
{
	sceGupTexMapMode(__guSettings.context, mode, lu, lv);
}
