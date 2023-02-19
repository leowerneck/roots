dnl Basic initialization
AC_PREREQ([2.71])
AC_INIT([Roots], [0.5.0], [wernecklr@gmail.com])
AC_CONFIG_SRCDIR([roots/include/roots.h])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIRS([m4])

dnl Automake configuration
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

dnl Program checks
: ${CFLAGS="-Wall -O2 -march=native"}
AC_PROG_CC
AC_PROG_INSTALL
AM_PROG_AR
LT_INIT

dnl Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE
AC_C_RESTRICT

dnl Checks for library functions.
AC_CHECK_FUNCS([sqrt])

dnl Makefile generation
AC_CONFIG_FILES([Makefile roots/Makefile roots/src/Makefile test/Makefile])

dnl All done
AC_OUTPUT
