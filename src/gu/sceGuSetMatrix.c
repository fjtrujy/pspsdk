/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuSetMatrix(int type, const ScePspFMatrix4 *matrix)
{
	sceGupSetMatrix(__guSettings.context, type, matrix);
}
