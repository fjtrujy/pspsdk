/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuDrawArrayN(int primitive_type, int vertex_type, int vcount, int primcount, const void *indices, const void *vertices)
{
	sceGupDrawArrayN(__guSettings.context, primitive_type, vertex_type, vcount, primcount, indices, vertices);
	_sceGuUpdateStallAddr();
}
