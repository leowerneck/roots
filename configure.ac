# Basic initialization
AC_INIT([Roots],[0.1],[wernecklr@gmail.com],[roots-0.1],[https://github.com/leowerneck/roots])
AM_INIT_AUTOMAKE([-Wall -Werror foreign silent-rules])
AM_SILENT_RULES([yes])

# Basic configuration
AC_CONFIG_SRCDIR([src/roots_info_warn_error.c])
AC_CONFIG_HEADERS([config.h])
AC_PREFIX_DEFAULT([$(realpath .)])
AC_CONFIG_MACRO_DIRS([m4])

# Program checks
AC_PROG_CC
AM_PROG_AR
LT_INIT

# Check for compiler characteristics
AC_C_RESTRICT

# Makefile generation
AC_CONFIG_FILES([Makefile src/Makefile test/Makefile])

# All done
AC_OUTPUT
