AC_PREREQ(2.63)
AC_INIT([myBot],[0.1],[mircsux@gmail.com])
AC_COPYRIGHT([Copyright (c) 2016 Ron Robbins Jr.])
AC_REVISION([$Revision])
AC_CONFIG_SRCDIR([main.c])
# Preserve 8.3 file format for MS-DOS compatibility.
AC_CONFIG_HEADERS([config.h:config-h.in])

AM_INIT_AUTOMAKE([foreign 1.10 -Wall -Werror subdir-objects no-dependencies])


# Checks for programs
AC_PROG_CC
AC_PROG_CC_C_O
AC_PROG_INSTALL
AC_PROG_MAKE_SET
AC_PROG_RANLIB
AC_USE_SYSTEM_EXTENSIONS

gl_USE_SYSTEM_EXTENSIONS

LIB_SOCKET_NSL

AC_CHECK_HEADERS([errno.h netdb.h netinit/in.h sys/socket.h string.h unistd.h])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
