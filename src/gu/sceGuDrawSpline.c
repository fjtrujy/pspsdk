/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuDrawSpline(int vertex_type, int ucount, int vcount, int uedge, int vedge, const void *indices, const void *vertices)
{
    sceGupDrawSpline(__guSettings.context, vertex_type, ucount, vcount, uedge, vedge, indices, vertices);
    _sceGuUpdateStallAddr();
}
