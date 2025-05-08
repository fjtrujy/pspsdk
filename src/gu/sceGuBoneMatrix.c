/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuBoneMatrix(unsigned int index, const ScePspFMatrix4 *matrix)
{
	sceGupBoneMatrix(__guSettings.context, index, matrix);
}
