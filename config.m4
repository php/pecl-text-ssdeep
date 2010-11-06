m4_include(ax_libssdeep.m4)
AX_SSDEEP

if test $SSDEEP_FOUND = "yes"; then
    dnl Hard set ext_shared to yes as AC_ARG_WITH does not
    dnl set it but PHP_ARG_WITH would.
    ext_shared="yes";
    PHP_CHECK_LIBRARY($SSDEEP_LIB_NAME, fuzzy_compare,
    [
      dnl Add the neccessary paths
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
