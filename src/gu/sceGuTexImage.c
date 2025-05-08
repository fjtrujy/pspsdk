/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuTexImage(int mipmap, int width, int height, int tbw, const void *tbp)
{
	sceGupTexImage(__guSettings.context, mipmap, width, height, tbw, tbp);
}
