ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS} -I m4
AM_CPPFLAGS = -I$(top_srcdir)/roots/include

include_HEADERS = $(top_srcdir)/roots/include/roots.h
noinst_HEADERS = utils.h

lib_LTLIBRARIES = libroots.la
libroots_la_SOURCES = check_a_b_compute_fa_fb.c roots_bisection.c roots_dekker.c roots_false_position.c roots_info.c roots_ridder.c roots_secant.c
