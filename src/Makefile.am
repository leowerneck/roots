ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS} -I m4

noinst_LTLIBRARIES = libroots.la
include_HEADERS = $(top_srcdir)/include/roots.h
libroots_la_SOURCES = roots_bisection.c roots_info_warn_error.c roots_secant.c roots_dekker.c
AM_CPPFLAGS = -I$(top_srcdir)/include
