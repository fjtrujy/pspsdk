/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuClutLoad(int num_blocks, const void *cbp)
{
	sceGupClutLoad(__guSettings.context, num_blocks, cbp);
}
