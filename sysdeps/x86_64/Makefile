# The i387 `long double' is a distinct type we support.
long-double-fcts = yes

ifeq ($(subdir),csu)
sysdep_routines += hp-timing
elide-routines.os += hp-timing
gen-as-const-headers += link-defines.sym
endif

ifeq ($(subdir),gmon)
sysdep_routines += _mcount
endif

ifeq ($(subdir),malloc)
tests += tst-mallocalign1
endif

ifeq ($(subdir),string)
sysdep_routines += cacheinfo strcasecmp_l-nonascii strncase_l-nonascii
gen-as-const-headers += locale-defines.sym
endif

ifeq ($(subdir),elf)
sysdep-dl-routines += tlsdesc dl-tlsdesc
sysdep_routines += tlsdesc dl-tlsdesc
sysdep-rtld-routines += tlsdesc dl-tlsdesc

tests += tst-quad1 tst-quad2
modules-names += tst-quadmod1 tst-quadmod2

$(objpfx)tst-quad1: $(objpfx)tst-quadmod1.so
$(objpfx)tst-quad2: $(objpfx)tst-quadmod2.so

quad-pie-test += tst-quad1pie tst-quad2pie
tests += $(quad-pie-test)
tests-pie += $(quad-pie-test)

$(objpfx)tst-quad1pie: $(objpfx)tst-quadmod1pie.o
$(objpfx)tst-quad2pie: $(objpfx)tst-quadmod2pie.o

tests += tst-audit3 tst-audit4 tst-audit5 tst-audit10
ifeq (yes,$(config-cflags-avx))
tests += tst-audit6 tst-audit7
endif
modules-names += tst-auditmod3a tst-auditmod3b \
		tst-auditmod4a tst-auditmod4b \
		tst-auditmod5a tst-auditmod5b \
		tst-auditmod6a tst-auditmod6b tst-auditmod6c \
		tst-auditmod7a tst-auditmod7b \
		tst-auditmod10a tst-auditmod10b

$(objpfx)tst-audit3: $(objpfx)tst-auditmod3a.so
$(objpfx)tst-audit3.out: $(objpfx)tst-auditmod3b.so
tst-audit3-ENV = LD_AUDIT=$(objpfx)tst-auditmod3b.so

$(objpfx)tst-audit4: $(objpfx)tst-auditmod4a.so
$(objpfx)tst-audit4.out: $(objpfx)tst-auditmod4b.so
tst-audit4-ENV = LD_AUDIT=$(objpfx)tst-auditmod4b.so

$(objpfx)tst-audit5: $(objpfx)tst-auditmod5a.so
$(objpfx)tst-audit5.out: $(objpfx)tst-auditmod5b.so
tst-audit5-ENV = LD_AUDIT=$(objpfx)tst-auditmod5b.so

$(objpfx)tst-audit6: $(objpfx)tst-auditmod6a.so
$(objpfx)tst-audit6.out: $(objpfx)tst-auditmod6b.so \
			 $(objpfx)tst-auditmod6c.so
tst-audit6-ENV = LD_AUDIT=$(objpfx)tst-auditmod6b.so:$(objpfx)tst-auditmod6c.so

$(objpfx)tst-audit7: $(objpfx)tst-auditmod7a.so
$(objpfx)tst-audit7.out: $(objpfx)tst-auditmod7b.so
tst-audit7-ENV = LD_AUDIT=$(objpfx)tst-auditmod7b.so

$(objpfx)tst-audit10: $(objpfx)tst-auditmod10a.so
$(objpfx)tst-audit10.out: $(objpfx)tst-auditmod10b.so
tst-audit10-ENV = LD_AUDIT=$(objpfx)tst-auditmod10b.so

ifeq (yes,$(config-cflags-avx))
AVX-CFLAGS=-mavx
ifeq (yes,$(config-cflags-novzeroupper))
AVX-CFLAGS+=-mno-vzeroupper
endif
CFLAGS-tst-audit4.c += $(AVX-CFLAGS)
CFLAGS-tst-auditmod4a.c += $(AVX-CFLAGS)
CFLAGS-tst-auditmod4b.c += $(AVX-CFLAGS)
CFLAGS-tst-auditmod6b.c += $(AVX-CFLAGS)
CFLAGS-tst-auditmod6c.c += $(AVX-CFLAGS)
CFLAGS-tst-auditmod7b.c += $(AVX-CFLAGS)
endif
ifeq (yes,$(config-cflags-avx512))
AVX512-CFLAGS = -mavx512f
CFLAGS-tst-audit10.c += $(AVX512-CFLAGS)
CFLAGS-tst-auditmod10a.c += $(AVX512-CFLAGS)
CFLAGS-tst-auditmod10b.c += $(AVX512-CFLAGS)
endif
endif

ifeq ($(subdir),csu)
gen-as-const-headers += tlsdesc.sym
endif
