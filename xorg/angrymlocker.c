/*
 * Copyright (c) 2011 by Stiletto <blasux@blasux.ru>.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of the copyright holder(s)
 * and author(s) shall not be used in advertising or otherwise to promote
 * the sale, use or other dealings in this Software without prior written
 * authorization from the copyright holder(s) and author(s).
 */

#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <xorg/xf86Module.h>
#include <xorg/xorg-server.h>

#define ZZZ_MAJOR_VERSION 0
#define ZZZ_MINOR_VERSION 1
#define ZZZ_PATCHLEVEL 1

static XF86ModuleVersionInfo zzzVersRec =
{
    "angrymlocker",
    "Stiletto <blasux@blasux.ru>",
    MODINFOSTRING1,
    MODINFOSTRING2,
    XORG_VERSION_CURRENT,
    ZZZ_MAJOR_VERSION, ZZZ_MINOR_VERSION, ZZZ_PATCHLEVEL,
    ABI_CLASS_ANSIC,
    ABI_ANSIC_VERSION,
    MOD_CLASS_NONE,
    {0,0,0,0}
};

static MODULESETUPPROTO(zzzSetup);
static MODULETEARDOWNPROTO(zzzTearDown);

XF86ModuleData angrymlockerModuleData = { &zzzVersRec, zzzSetup, zzzTearDown };

static int debug_enabled;

static pointer
zzzSetup(pointer module, pointer opts, int *errmaj, int *errmin)
{
    char* env_debug = getenv("ANGRYMLOCKER_NODEBUG");
    debug_enabled = env_debug && strcmp(env_debug,"1");
    int res = mlockall(MCL_CURRENT | MCL_FUTURE);
    if (debug_enabled) {
	if (!res)
	    fprintf(stderr,"mlock()'ed entire process's address space.\n");
        else {
	    perror("mlockall()");
	    return NULL;
	}
    }
    return (pointer)1;
}

static void
zzzTearDown(pointer lol)
{
    int res = munlockall();
    if (debug_enabled) {
	if (!res)
	    fprintf(stderr,"munlock()'ed entire process's address space.\n");
        else
	    perror("munlockall()");
    }
}

