/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuClutMode(unsigned int cpsm, unsigned int shift, unsigned int mask, unsigned int csa)
{
	sceGupClutMode(__guSettings.context, cpsm, shift, mask, csa);
}
