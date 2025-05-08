/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuBlendFunc(int op, int src, int dest, unsigned int srcfix, unsigned int destfix)
{
	sceGupBlendFunc(__guSettings.context, op, src, dest, srcfix, destfix);
}
