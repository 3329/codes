# This Makefile is for the Bash/documentation directory -*- text -*-.
#
# Copyright (C) 2003-2013 Free Software Foundation, Inc.

#   This program is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.

#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.

#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <http://www.gnu.org/licenses/>.

PACKAGE = bash
VERSION = 4.3-release

PACKAGE_BUGREPORT = bug-bash@gnu.org
PACKAGE_NAME = bash
PACKAGE_STRING = bash 4.3-release
PACKAGE_VERSION = 4.3-release

PACKAGE_TARNAME = bash

#
SHELL = /bin/sh
RM	    = rm -f

topdir = ..
srcdir = .
VPATH = .

prefix = /usr/local
exec_prefix = ${prefix}

datarootdir = ${prefix}/share

infodir = ${datarootdir}/info

docdir = ${datarootdir}/doc/${PACKAGE_TARNAME}

# set this to a directory name to have the HTML files installed
htmldir = ${docdir}

# Support an alternate destination root directory for package building
DESTDIR =

mandir = ${datarootdir}/man
manpfx = man

man1ext = .1
man1dir = $(mandir)/$(manpfx)1
man3ext = .3
man3dir = $(mandir)/$(manpfx)3

INSTALL = /usr/bin/install -c
INSTALL_DATA = ${INSTALL} -m 644
BUILD_DIR = /home/young/codes/2014/0418/bash-4.3

SUPPORT_SRCDIR = $(topdir)/support

# bad style
RL_LIBDIR = $(topdir)/lib/readline

# unused
TEXINDEX    = texindex
TEX	    = tex

MAKEINFO    = makeinfo
TEXI2DVI    = ${SUPPORT_SRCDIR}/texi2dvi
TEXI2HTML   = ${SUPPORT_SRCDIR}/texi2html
MAN2HTML    = ${BUILD_DIR}/support/man2html
HTMLPOST    = ${srcdir}/htmlpost.sh
INFOPOST    = ${srcdir}/infopost.sh
QUIETPS	    = #set this to -q to shut up dvips
PAPERSIZE   = letter	# change to a4 for A4-size paper
PSDPI       = 600	# could be 300 if you like
DVIPS	    = dvips -D ${PSDPI} $(QUIETPS) -t ${PAPERSIZE} -o $@	# tricky

TEXINPUTDIR = $(RL_LIBDIR)/doc
SET_TEXINPUTS = TEXINPUTS=.:$(TEXINPUTDIR):$$TEXINPUTS

# These tools might not be available; they're not required
DVIPDF	    = dvipdfm -o $@ -p ${PAPERSIZE}
PSPDF       = gs -sPAPERSIZE=${PAPERSIZE} -sDEVICE=pdfwrite -dNOPAUSE -dBATCH -sOutputFile=$@

MKDIRS      = ${SUPPORT_SRCDIR}/mkdirs

# This should be a program that converts troff to an ascii-readable format
NROFF	    = groff -Tascii

# This should be a program that converts troff to postscript
GROFF	    = groff

HSUSER      = $(RL_LIBDIR)/doc/hsuser.texi
RLUSER      = $(RL_LIBDIR)/doc/rluser.texi

BASHREF_FILES = $(srcdir)/bashref.texi $(srcdir)/fdl.texi $(srcdir)/version.texi

.SUFFIXES:	.0 .1 .3 .ms .ps .txt .dvi .html .pdf

.1.ps:
	$(RM) $@
	-${GROFF} -man $< > $@

.1.0:
	$(RM) $@
	-${NROFF} -man $< > $@

.1.html:
	$(RM) $@
	-${MAN2HTML} $< | ${HTMLPOST} > $@

.ms.ps:
	$(RM) $@
	-${GROFF} -ms $< > $@

.ms.txt:
	$(RM) $@
	-${NROFF} -ms $< > $@

.3.ps:
	$(RM) $@
	-${GROFF} -man $< > $@

.3.0:
	$(RM) $@
	-${NROFF} -man $< > $@

.3.html:
	$(RM) $@
	-${MAN2HTML} $< > $@

.ps.pdf:
	$(RM) $@
	-${PSPDF} $<

.dvi.pdf:
	$(RM) $@
	-${DVIPDF} $<

.dvi.ps:
	${RM} $@
	-${DVIPS} $<

all: ps info dvi text html
nodvi: ps info text html
everything: all pdf

PSFILES = bash.ps bashbug.ps article.ps builtins.ps rbash.ps 
DVIFILES = bashref.dvi bashref.ps
INFOFILES = bashref.info
MAN0FILES = bash.0 bashbug.0 builtins.0 rbash.0
HTMLFILES = bashref.html bash.html
PDFFILES = bash.pdf bashref.pdf article.pdf rose94.pdf

ps: ${PSFILES}
dvi: ${DVIFILES}
info: ${INFOFILES}
text: ${MAN0FILES}
html: ${HTMLFILES}
pdf: ${PDFFILES}

bashref.dvi: $(BASHREF_FILES) $(HSUSER) $(RLUSER)
	${SET_TEXINPUTS} $(TEXI2DVI) $(srcdir)/bashref.texi || { ${RM} $@ ; exit 1; }

bashref.info: $(BASHREF_FILES) $(HSUSER) $(RLUSER)
	$(MAKEINFO) --no-split -I$(TEXINPUTDIR) $(srcdir)/bashref.texi

# can also use:
#	$(MAKEINFO) --html --no-split -I$(TEXINPUTDIR) $(srcdir)/bashref.texi
bashref.html: $(BASHREF_FILES) $(HSUSER) $(RLUSER)
	$(TEXI2HTML) -menu -monolithic -I $(TEXINPUTDIR) $(srcdir)/bashref.texi

bash.info: bashref.info
	${SHELL} ${INFOPOST} < $(srcdir)/bashref.info > $@ ; \

bash.txt: bash.1
bash.ps: bash.1
bash.html: bash.1 $(MAN2HTML)
bashbug.ps: bashbug.1
builtins.ps: builtins.1 bash.1
rbash.ps: rbash.1 bash.1
bash.0: bash.1
bashbug.0: bashbug.1
builtins.0: builtins.1 bash.1
rbash.0: rbash.1 bash.1
article.ps: article.ms

bashref.ps: bashref.dvi

article.pdf: article.ps
bashref.pdf: bashref.dvi
bash.pdf: bash.ps
rose94.pdf: rose94.ps

OTHER_DOCS = $(srcdir)/FAQ $(srcdir)/INTRO
OTHER_INSTALLED_DOCS = FAQ INTRO

$(MAN2HTML):	${topdir}/support/man2html.c
	-( cd ${BUILD_DIR}/support ; ${MAKE} ${MFLAGS} man2html)

clean:
	$(RM) *.aux *.bak *.cp *.fn *.ky *.log *.pg *.toc *.tp *.vr *.cps \
		*.pgs *.bt *.bts *.rw *.rws *.fns *.kys *.tps *.vrs *.o
	${RM} core *.core

mostlyclean: clean
	$(RM) Makefile

distclean: clean maybe-clean
	$(RM) Makefile

maintainer-clean:	clean
	${RM} ${PSFILES} ${DVIFILES} ${INFOFILES} ${MAN0FILES} ${HTMLFILES}
	${RM} ${CREATED_FAQ}
	$(RM) Makefile

maybe-clean:
	-if test "X$(topdir)" != "X$(BUILD_DIR)"; then \
		$(RM) ${PSFILES} ${DVIFILES} ${INFOFILES} ${MAN0FILES} ${HTMLFILES}; \
	fi

installdirs:
	-$(SHELL) $(SUPPORT_SRCDIR)/mkinstalldirs $(DESTDIR)$(man1dir)
	-$(SHELL) $(SUPPORT_SRCDIR)/mkinstalldirs $(DESTDIR)$(infodir)
	-$(SHELL) $(SUPPORT_SRCDIR)/mkinstalldirs $(DESTDIR)$(docdir)
	-if test -n "$(htmldir)" ; then \
		$(SHELL) $(SUPPORT_SRCDIR)/mkinstalldirs $(DESTDIR)$(htmldir) ; \
	fi
	
install: info installdirs bash.info
	-$(INSTALL_DATA) $(srcdir)/bash.1 $(DESTDIR)$(man1dir)/bash${man1ext}
	-$(INSTALL_DATA) $(srcdir)/bashbug.1 $(DESTDIR)$(man1dir)/bashbug${man1ext}
	-$(INSTALL_DATA) $(OTHER_DOCS) $(DESTDIR)$(docdir)
# uncomment the next lines to install the builtins man page
#	sed 's:bash\.1:man1/&:' $(srcdir)/builtins.1 > $${TMPDIR:-/var/tmp}/builtins.1
#	-$(INSTALL_DATA) $${TMPDIR:-/var/tmp}/builtins.1 $(DESTDIR)$(man1dir)/bash_builtins${man1ext}
#	-$(RM) $${TMPDIR:-/var/tmp}/builtins.1
	-if test -f bash.info; then d=.; else d=$(srcdir); fi; \
	  $(INSTALL_DATA) $$d/bash.info $(DESTDIR)$(infodir)/bash.info
# run install-info if it is present to update the info directory
	if $(SHELL) -c 'install-info --version' >/dev/null 2>&1; then \
		install-info --dir-file=$(DESTDIR)$(infodir)/dir $(DESTDIR)$(infodir)/bash.info; \
	else true; fi
# if htmldir is set, install the html files into that directory
	-if test -n "${htmldir}" ; then \
		$(INSTALL_DATA) $(srcdir)/bash.html $(DESTDIR)$(htmldir) ; \
		$(INSTALL_DATA) $(srcdir)/bashref.html $(DESTDIR)$(htmldir) ; \
	fi

install_builtins:	installdirs
	sed 's:bash\.1:man1/&:' $(srcdir)/builtins.1 > $${TMPDIR:-/var/tmp}/builtins.1
	-$(INSTALL_DATA) $${TMPDIR:-/var/tmp}/builtins.1 $(DESTDIR)$(man1dir)/bash_builtins${man1ext}
	-$(RM) $${TMPDIR:-/var/tmp}/builtins.1

install_everything:	install install_builtins

uninstall:
	-$(RM) $(DESTDIR)$(man1dir)/bash${man1ext} $(DESTDIR)$(man1dir)/bashbug${man1ext}
	-$(RM) $(DESTDIR)$(man1dir)/bash_builtins${man1ext}
	$(RM) $(DESTDIR)$(infodir)/bash.info
	-( cd $(DESTDIR)$(docdir) && $(RM) $(OTHER_INSTALLED_DOCS) )
	-if test -n "$(htmldir)" ; then \
		$(RM) $(DESTDIR)$(htmldir)/bash.html ; \
		$(RM) $(DESTDIR)$(htmldir)/bashref.html ; \
	fi

# for use by chet
CREATED_FAQ = faq.news faq.news2 faq.mail faq.version

faq:	${CREATED_FAQ}

faq.version:	FAQ.version FAQ
	sh mkfaqvers FAQ.version > $@

faq.headers.mail: FAQ.headers.mail FAQ
	sh mkfaqvers FAQ.headers.mail > $@

faq.headers.news: FAQ.headers.news FAQ
	sh mkfaqvers FAQ.headers.news > $@

faq.headers.news2: FAQ.headers.news2 FAQ
	sh mkfaqvers FAQ.headers.news2 > $@

faq.news: FAQ faq.headers.news faq.version
	$(RM) $@
	cat faq.headers.news faq.version FAQ > $@

faq.news2: FAQ faq.headers.news2 faq.version
	$(RM) $@
	cat faq.headers.news2 faq.version FAQ > $@

faq.mail: FAQ faq.headers.mail faq.version
	$(RM) $@
	cat faq.headers.mail faq.version FAQ > $@

inst:	bashref.texi
	$(SHELL) ./mkinstall
	cmp -s INSTALL ../INSTALL || mv INSTALL ../INSTALL
	$(RM) INSTALL

posix:	bashref.texi
	$(SHELL) ./mkposix
	cmp -s POSIX ../POSIX || mv POSIX ../POSIX
	$(RM) POSIX

rbash:	bashref.texi
	$(SH) ./mkrbash
	cmp -s RBASH ../RBASH || mv RBASH ../RBASH
	$(RM) RBASH

xdist: pdf inst posix rbash
