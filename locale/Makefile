# Copyright (C) 1991-2014 Free Software Foundation, Inc.
# This file is part of the GNU C Library.

# The GNU C Library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.

# The GNU C Library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.

# You should have received a copy of the GNU Lesser General Public
# License along with the GNU C Library; if not, see
# <http://www.gnu.org/licenses/>.

#
#	Makefile for locales.
#
subdir	:= locale

include ../Makeconfig

headers		= locale.h bits/locale.h langinfo.h xlocale.h
routines	= setlocale findlocale loadlocale loadarchive \
		  localeconv nl_langinfo nl_langinfo_l mb_cur_max \
		  newlocale duplocale freelocale uselocale
tests		= tst-C-locale tst-locname tst-duplocale
categories	= ctype messages monetary numeric time paper name \
		  address telephone measurement identification collate
aux		= $(categories:%=lc-%) $(categories:%=C-%) SYS_libc C_name \
		  xlocale localename global-locale coll-lookup
others		= localedef locale
#others-static	= localedef locale
install-bin	= localedef locale
extra-objs	= $(localedef-modules:=.o) $(localedef-aux:=.o) \
		  $(locale-modules:=.o) $(lib-modules:=.o)

extra-libs	= libBrokenLocale
extra-libs-others = $(extra-libs)

libBrokenLocale-routines = broken_cur_max

subdir-dirs	= programs
vpath %.c programs ../crypt
vpath %.h programs
vpath %.gperf programs

localedef-modules	:= localedef $(categories:%=ld-%) \
			   charmap linereader locfile \
			   repertoire locarchive
localedef-aux		:= md5
locale-modules		:= locale locale-spec
lib-modules		:= charmap-dir simple-hash xmalloc xstrdup


GPERF = gperf
GPERFFLAGS = -acCgopt -k1,2,5,9,$$ -L ANSI-C

include ../Rules

CFLAGS-md5.c = -I../crypt

programs/%-kw.h: programs/%-kw.gperf
	cd programs \
	&& $(GPERF) $(GPERFFLAGS) -N $(@F:-kw.h=_hash) $(<F) > $(@F).new
	mv -f $@.new $@

$(objpfx)localedef: $(localedef-modules:%=$(objpfx)%.o)
$(objpfx)localedef: $(localedef-aux:%=$(objpfx)%.o)
$(objpfx)locale: $(locale-modules:%=$(objpfx)%.o)
$(objpfx)localedef $(objpfx)locale: $(lib-modules:%=$(objpfx)%.o)

C-translit.h: C-translit.h.in gen-translit.pl
	$(PERL) gen-translit.pl < $< > $@.tmp
	mv -f $@.tmp $@

localepath = "$(localedir):$(i18ndir)"

# -Iprograms doesn't really belong here, but this gets it at the head
# of the list instead of the tail, where CPPFLAGS-$(lib) gets added.
# We need it before the standard -I's to see programs/config.h first.
locale-CPPFLAGS = -DLOCALEDIR='"$(localedir)"' \
		  -DLOCALE_ALIAS_PATH='"$(msgcatdir)"' \
		  -Iprograms

CPPFLAGS-locale-programs = -DLOCALE_PATH='$(localepath)' \
			   -DCHARMAP_PATH='"$(i18ndir)/charmaps"' \
			   -DREPERTOIREMAP_PATH='"$(i18ndir)/repertoiremaps"' \
			   -DLOCSRCDIR='"$(i18ndir)/locales"' \
			   -DHAVE_CONFIG_H -DNOT_IN_libc

CFLAGS-charmap.c = -Wno-write-strings -Wno-char-subscripts
CFLAGS-locfile.c = -Wno-write-strings -Wno-char-subscripts
CFLAGS-charmap-dir.c = -Wno-write-strings

# This makes sure -DNOT_IN_libc et al are passed for all these modules.
cpp-srcs-left := $(addsuffix .c,$(localedef-modules) $(localedef-aux) \
				$(locale-modules) $(lib-modules))
lib := locale-programs
include $(patsubst %,$(..)cppflags-iterator.mk,$(cpp-srcs-left))
