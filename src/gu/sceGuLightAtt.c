/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuLightAtt(int light, float atten0, float atten1, float atten2)
{
	sceGupLightAtt(__guSettings.context, light, atten0, atten1, atten2);
}
