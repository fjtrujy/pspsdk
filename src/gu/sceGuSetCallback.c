/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void *sceGuSetCallback(int signal, GuCallback callback)
{
	GuCallback old_callback = NULL;

	switch (signal)
	{
	case GU_CALLBACK_SIGNAL:
		old_callback = __intrParam.cbSignal;
		__intrParam.cbSignal = callback;
		break;
	case GU_CALLBACK_FINISH:
		old_callback = __intrParam.cbFinish;
		__intrParam.cbFinish = callback;
		break;
	}

	return old_callback;
}
