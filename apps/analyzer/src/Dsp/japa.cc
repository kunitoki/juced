//  ----------------------------------------------------------------------------
//
//  Copyright (C) 2004-2008 Fons Adriaensen <fons@kokkinizita.net>
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.

//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
//  ----------------------------------------------------------------------------

#if 0

#include <stdlib.h>
#include <stdio.h>
#include <clthreads.h>
#include "clxclient.h"
#include "messages.h"
#include "mainwin.h"
#include "audio.h"


#define NOPTS 7


XrmOptionDescRec options [NOPTS] =
{
    {"-h",   ".help",      XrmoptionNoArg,  "true"  },
    {"-J",   ".jack",      XrmoptionNoArg,  "true"  },
    {"-A",   ".alsa",      XrmoptionNoArg,  "true"  },
    {"-d",   ".device",    XrmoptionSepArg,  0      },
    {"-r",   ".fsamp",     XrmoptionSepArg,  0      },
    {"-p",   ".period",    XrmoptionSepArg,  0      },
    {"-n",   ".nfrags",    XrmoptionSepArg,  0      }
};


static void help (void)
{
    fprintf (stderr, "japa-%s\n  (C) Fons Adriaensen\n  <fons@kokkinizita.net>\n\n", VERSION);
    fprintf (stderr, "-h                 Display this text\n");
    fprintf (stderr, "-J                 Use JACK\n");
    fprintf (stderr, "-A                 Use ALSA, with options:\n");
    fprintf (stderr, "  -d <device>        Alsa device [hw:0.0]\n");
    fprintf (stderr, "  -r <rate>          Sample frequency [48000]\n");
    fprintf (stderr, "  -p <period>        Period size [1024]\n");
    fprintf (stderr, "  -n <nfrags>        Number of fragments [2]\n\n");
    fprintf (stderr, "Either -J or -A must be given.\n\n");
    exit (1);
}


int main (int argc, char *argv [])
{
    X_resman       xrm;
    X_display     *display;
    X_handler     *xhandler;
    X_rootwin     *rootwin;
    Mainwin       *mainwin;
    Audio         *driver;
    ITC_ctrl       itcc;

    // Initialse resource database
    xrm.init (&argc, argv, "japa", options, NOPTS);
    if (xrm.getb (".help", 0)) help ();
            
    // Open display
    display = new X_display (xrm.get (".display", 0));
    if (display->dpy () == 0)
    {
	fprintf (stderr, "Can't open display !\n");
        delete display;
	exit (1);
    }
    // Open audio interface
    driver = new Audio (&itcc, xrm.rname ());

    if (xrm.getb (".jack", 0))
    {
        driver->init_jack ();
    }
    else if (xrm.getb (".alsa", 0))
    {
	const char *p;
        int  fsamp, period, nfrags;

        p = xrm.get (".fsamp", 0);
        if (! p || sscanf (p, "%d", &fsamp) != 1) fsamp = 48000;
        p = xrm.get (".period", 0);
        if (! p || sscanf (p, "%d", &period) != 1) period = 1024;
        p = xrm.get (".nfrags", 0);
        if (! p || sscanf (p, "%d", &nfrags) != 1) nfrags = 2;
        p = xrm.get (".device", 0);
        if (! p) p = "default";
        driver->init_alsa (p, fsamp, period, nfrags);
    }
    else help ();

    // Initialise resources and create windows
    init_styles (display, &xrm);
    rootwin = new X_rootwin (display);
    mainwin = new Mainwin (rootwin, &xrm, driver);

    // Create X handler
    xhandler = new X_handler (display, &itcc, EV_X11);
    xhandler->next_event ();
    XFlush (display->dpy ());

    // Enter main loop
    while (mainwin->running ())
    {
	switch (itcc.get_event ())
	{
        case EV_TRIG:
            mainwin->handle_trig ();
	    rootwin->handle_event ();
            XFlush (display->dpy ());
            break;

        case EV_JACK:
            mainwin->handle_term ();
            break;

        case EV_MESG:
            mainwin->handle_mesg (itcc.get_message ());
	    rootwin->handle_event ();
            XFlush (display->dpy ());
            break;

	case EV_X11:
	    rootwin->handle_event ();
	    xhandler->next_event ();
            break;
	}
    }

    // Cleanup
    delete xhandler;
    delete driver;
    delete mainwin;
    delete rootwin;
    delete display;
   
    return 0;
}

#endif


