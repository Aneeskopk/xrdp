/*
Copyright 2013 Jay Sorg

Permission to use, copy, modify, distribute, and sell this software and its
documentation for any purpose is hereby granted without fee, provided that
the above copyright notice appear in all copies and that both that
copyright notice and this permission notice appear in supporting
documentation.

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
OPEN GROUP BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

rdp module main

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* this should be before all X11 .h files */
#include <xorg-server.h>

/* all driver need this */
#include <xf86.h>
#include <xf86_OSproc.h>

#include <mipointer.h>
#include <fb.h>
#include <micmap.h>
#include <mi.h>

#include "rdp.h"

/******************************************************************************/
#define LOG_LEVEL 1
#define LLOGLN(_level, _args) \
    do { if (_level < LOG_LEVEL) { ErrorF _args ; ErrorF("\n"); } } while (0)

#define XRDP_DRIVER_NAME "XORGXRDP"
#define XRDP_NAME "XORGXRDP"
#define XRDP_VERSION 1000

#define PACKAGE_VERSION_MAJOR 1
#define PACKAGE_VERSION_MINOR 0
#define PACKAGE_VERSION_PATCHLEVEL 0

static int g_initialised = 0;

/*****************************************************************************/
static pointer
xorgxrdpSetup(pointer Module, pointer Options, int *ErrorMajor, int *ErrorMinor)
{
    LLOGLN(0, ("xorgxrdpSetup:"));
    if (!g_initialised)
    {
        g_initialised = 1;
    }
    rdpInputInit();
    rdpPrivateInit();
    return (pointer) 1;
}

static MODULESETUPPROTO(xorgxrdpSetup);
static XF86ModuleVersionInfo RDPVersRec =
{
    XRDP_DRIVER_NAME,
    MODULEVENDORSTRING,
    MODINFOSTRING1,
    MODINFOSTRING2,
    XORG_VERSION_CURRENT,
    PACKAGE_VERSION_MAJOR,
    PACKAGE_VERSION_MINOR,
    PACKAGE_VERSION_PATCHLEVEL,
    ABI_CLASS_VIDEODRV,
    ABI_VIDEODRV_VERSION,
    0,
    { 0, 0, 0, 0 }
};

XF86ModuleData xorgxrdpModuleData = { &RDPVersRec, xorgxrdpSetup, NULL };