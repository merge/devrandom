#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT([sdltest], [1.0], [thebohemian@gmx.net])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/sdltest.c])
AC_CONFIG_HEADER([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([SDL], [SDL_Init])

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h])
AC_CHECK_HEADERS([SDL/SDL.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([\
  Makefile\
  src/Makefile\
])

AC_OUTPUT
