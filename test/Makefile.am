ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS} -I m4
bin_PROGRAMS = test_bisection test_secant
test_bisection_SOURCES = test_bisection.c
test_bisection_LDADD = $(top_srcdir)/src/libroots.la
test_secant_SOURCES = test_secant.c
test_secant_LDADD = $(top_srcdir)/src/libroots.la
AM_CPPFLAGS = -I$(top_srcdir)/include
