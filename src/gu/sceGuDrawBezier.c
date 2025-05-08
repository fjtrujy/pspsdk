/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuDrawBezier(int vertex_type, int ucount, int vcount, const void *indices, const void *vertices)
{
  	sceGupDrawBezier(__guSettings.context, vertex_type, ucount, vcount, indices, vertices);
  	_sceGuUpdateStallAddr();
}
