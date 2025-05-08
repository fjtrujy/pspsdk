/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuLight(int light, int type, int components, const ScePspFVector3 *position)
{
	sceGupLight(__guSettings.context, light, type, components, position);
}
