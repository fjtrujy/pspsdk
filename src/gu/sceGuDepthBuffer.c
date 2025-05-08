/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuDepthBuffer(void *zbp, int zbw)
{
	sceGupDepthBuffer(__guSettings.context, zbp, zbw);	
	
	__guSettings.frameBuf.zbp = (unsigned int)zbp;
	__guSettings.frameBuf.zbw = zbw;
}
