#  Copyright (C) 2004-2008 Fons Adriaensen <fons@kokkinizita.net>
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.

#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.


PREFIX = /usr/local
SUFFIX := $(shell uname -m | sed -e 's/^unknown/$//' -e 's/^i.86/$//' -e 's/^x86_64/$/64/')
LIBDIR = lib$(SUFFIX)
VERSION = 0.4.0
DISTDIR = japa-$(VERSION)
CPPFLAGS += -O3 -Wall -MMD -MP -DVERSION=\"$(VERSION)\" -DPREFIX=\"$(PREFIX)\" -I/usr/include/freetype2
#CPPFLAGS += -march=pentium4

LDFLAGS += -L$(PREFIX)/$(LIBDIR) -L/usr/X11R6/$(LIBDIR)
LDLIBS += -lclalsadrv -lclthreads -lclxclient -lpthread -lfftw3f -ljack -lasound -lpthread -lXft -lX11 -lrt


JAPA_O = analyser.o audio.o gobjects.o japa.o mainwin.o styles.o rngen.o
japa:	$(JAPA_O)
	g++ $(LDFLAGS) -o $@ $(JAPA_O) $(LDLIBS)

$(JAPA_O):
-include $(JAPA_O:%.o=%.d)


install:	japa
	/usr/bin/install -m 755 japa $(PREFIX)/bin

$(JAPA_O):	$(JAPA_H)


clean:
	/bin/rm -f *~ *.o *.a *.d *.so japa


tarball:
	cd ..; \
	/bin/rm -f -r $(DISTDIR)*; \
	svn export japa $(DISTDIR); \
	tar cvf $(DISTDIR).tar $(DISTDIR); \
	bzip2 $(DISTDIR).tar; \
	/bin/rm -f -r $(DISTDIR);
