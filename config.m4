PHP_ARG_WITH(ssdeep, for ssdeep support,
[  --with-ssdeep[=DIR]        Include ssdeep support. DIR is the optional path to the ssdeep directory.], yes)
PHP_ARG_ENABLE(ssdeep-debug, whether to enable build debug output,
[  --enable-ssdeep-debug        ssdeep: Enable debugging during build], no, no)

if test "$PHP_SSDEEP" != "no"; then
  withssdeep="$PHP_SSDEEP"
  ssdeep_enabledebug="$PHP_SSDEEP_DEBUG"
  dnl Pass in the library directory name specified by PHP - defaults to lib
  ssdeep_libdirname="$PHP_LIBDIR"

  dnl Include common ssdeep availability test function
  m4_include(ax_libssdeep.m4)
  AX_SSDEEP

  if test $SSDEEP_FOUND = "yes"; then
      PHP_CHECK_LIBRARY($SSDEEP_LIB_NAME, fuzzy_compare,
      [
        dnl Add the neccessary paths (vars declared in ax_libssdeep.m4)
        PHP_ADD_INCLUDE($SSDEEP_INCLUDEDIR_NO_FLAG)
        PHP_ADD_LIBRARY_WITH_PATH($SSDEEP_LIB_NAME, $SSDEEP_LIBDIR_NO_FLAG, SSDEEP_SHARED_LIBADD)
        AC_DEFINE(HAVE_SSDEEP, 1, [Whether you have SSDEEP])
      ],[
        AC_MSG_ERROR([ssdeep lib not found. See config.log for more information.])
      ],[$SSDEEP_LIBDIR]
      )
      PHP_NEW_EXTENSION(ssdeep, ssdeep.c, $ext_shared)
      PHP_SUBST(SSDEEP_SHARED_LIBADD)
  fi
else
  AC_MSG_RESULT([ssdeep was not enabled])
  AC_MSG_ERROR([Enable ssdeep to build this extension.])
fi
