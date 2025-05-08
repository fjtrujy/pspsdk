/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuTexMode(int tpsm, int maxmips, int mc, int swizzle)
{
	sceGupTexMode(__guSettings.context, tpsm, maxmips, mc, swizzle);
}
