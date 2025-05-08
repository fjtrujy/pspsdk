/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuCopyImage(int psm, int sx, int sy, int width, int height, int srcw, void *src, int dx, int dy, int destw, void *dest)
{
	sceGupCopyImage(__guSettings.context, psm, sx, sy, width, height, srcw, src, dx, dy, destw, dest);
}
