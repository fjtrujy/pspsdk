/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuDrawArray(int prim, int vtype, int count, const void *indices, const void *vertices)
{
  sceGupDrawArray(__guSettings.context, prim, vtype, count, indices, vertices);
  _sceGuUpdateStallAddr();
}
