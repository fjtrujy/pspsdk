/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * init.c - The global init/deinit code for our crt0.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/param.h>

void __init_cwd(char *argv_0);
void __timezone_update();
void __fdman_init();

#ifdef F___psp_libc_init
/* Note: This function is being linked into _exit.o.  
   Because __psp_libc_init is a weak import in crt0.c, the linker
   chooses to ignore an object file in libc.a that contains just this
   function, since it's not necessary for successful compilation.
   By putting it instead in _exit.o, which is already used by crt0.c,
   the linker sees __psp_libc_init and resolves the symbol properly.
*/
__attribute__((weak))
void __psp_libc_init(int argc, char *argv[])
{
    (void) argc;

	/* Initialize cwd from this program's path */
	__init_cwd(argv[0]);

	/* Initialize timezone */
	__timezone_update();

	/* Initialize filedescriptor management */
	__fdman_init();
}
#endif