/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuBeginObject(int vertex_type, int count, const void *indices, const void *vertices)
{
	sceGupBeginObject(__guSettings.context, vertex_type, count, indices, vertices);
}
