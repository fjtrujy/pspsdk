/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#ifndef __guInternal_h__
#define __guInternal_h__

#include "pspgu.h"

/* max depth of stack(GU_SIGNAL_CALL) */
#define STACK_MAX		32	
/* max number of list mode */
#define LISTMODE_MAX	3
/* max number of signal */
#define SIGNAL_MAX		16
/* signal buffer size */
#define EVFLAG_SIGNAL	0x00000001U

/* Callback function */
typedef void (*GuCallback)(int, const void *);

/* Interrupt structure */
/* Interrupt structure parameter */
typedef struct {
	void (*cbSignal)(int, const void *);
	void (*cbFinish)(int, const void *);
	int count;
	unsigned int evid;
	unsigned short buffer[SIGNAL_MAX];
} IntrParam;
extern IntrParam __intrParam;

/* Settings structure */
typedef struct {
	/* libgu initialized flag*/
	int library_initialized;
	
	/* dither initialized flag */
	int dither_initialized;
	/* display switch
		GU_DISPLAY_OFF
		GU_DISPLAY_ON
	*/
	int disp_sw;

	/* current list mode 
		GU_DIRECT
		GU_SEND
		GU_CALL
	*/
	int list_mode;
	/* call mode
		GU_CALL_NORMAL
		GU_CALL_SIGNAL
	*/
	int call_mode;

	/* swap buffers behaviour
		PSP_DISPLAY_SETBUF_NEXTHSYNC
		PSP_DISPLAY_SETBUF_NEXTVSYNC
	*/
	int swap_buffers_behaviour;

	/* swap buffers callback */
	GuSwapBuffersCallback swap_buffers_callback;

	/* GE eDram Top Address */
	unsigned char *ge_edram_address;

	/* GE queue id 
		queid[0] = for current display list
		queid[1] = sceGuSendList() use
	*/
	int queid[2];

	/* GE interrupt handler id */
	int intrId;

	/* frame buffer information */
	struct {
		int fpf;
		int fbw;
		int wbp;
		int dbp;
		int zbp;
		int zbw;
		int sw;
		int sh;
	} frameBuf;

	/* Enable/Disable status */
	unsigned int states;

	/* context for current list 
		shortcut for &__guSettings.listctx[__guSettings.list_mode].packet
	*/
	SceGupContext *context;

	/* context for making display list 
		listctx[0] for GU_DIRECT
		listctx[1] for GU_SEND
		listctx[2] for GU_CALL
	*/
	struct {
		SceGupContext packet;
		int prevmode;
	} listctx[LISTMODE_MAX];
} GU_Settings;
extern GU_Settings __guSettings;

static inline int _sceGuUpdateStallAddr(void) {
	if (__guSettings.context == GU_DIRECT) {
		// Just if there are no objects in the stack (no guBeginObject)
		if (!sceGupGetBoundingBoxNest(__guSettings.context) == 0) {
			void *pCurrent = sceGupGetCurrentAddr(__guSettings.context);
			int res;
			res = sceGeListUpdateStallAddr(__guSettings.queid[0], pCurrent);
			if (res < 0) {
				return res;
			}
		}
	} 
	return 0;
}

#endif
