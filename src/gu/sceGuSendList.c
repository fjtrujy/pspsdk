/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

#include <pspkernel.h>
#include <pspge.h>

int sceGuSendList(int mode, const void *list, PspGeContext *context, int numStacks, SceGeStack *stacks)
{
	PspGeListArgs args;
	int list_id;

	__intrParam.count = 0;
	args.size = sizeof(PspGeListArgs);
	args.context = context;
	args.numStacks = numStacks;
	args.stacks = stacks;
	list_id = -1;

	switch (mode)
	{
	case GU_HEAD:
		list_id = sceGeListEnQueueHead(list, NULL, __guSettings.intrId, &args);
		break;
	case GU_TAIL:
		list_id = sceGeListEnQueue(list, NULL, __guSettings.intrId, &args);
		break;
	}

	if (list_id < 0)
	{
		return list_id;
	}

	__guSettings.queid[1] = list_id;
	return 0;
}
