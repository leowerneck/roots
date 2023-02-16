# Basic initialization
AC_INIT([Roots], [0.1], [wernecklr@gmail.com], [roots-0.1], [https://github.com/leowerneck/roots])
AM_INIT_AUTOMAKE([-Wall -Werror foreign enable-silent-rules])

# Basic configuration
AC_CONFIG_SRCDIR([src/roots_info_warn_error.c])
AC_CONFIG_HEADERS([config.h])

# Program checks
AC_PROG_CC
AC_PROG_LIBTOOL
AM_PROG_AR

# Check for compiler characteristics
AC_C_RESTRICT

# Makefile generation
AC_CONFIG_FILES([Makefile src/Makefile])

# All done
AC_OUTPUT
