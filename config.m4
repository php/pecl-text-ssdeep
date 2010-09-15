dnl config.m4 for extension ssdeep
PHP_ARG_WITH(ssdeep, for ssdeep support,
[  --with-ssdeep        Include ssdeep support])

if test "$PHP_SSDEEP" = "yes"; then
    PHP_SUBST(SSDEEP_SHARED_LIBADD)
    PHP_CHECK_LIBRARY(fuzzy, fuzzy_compare,
    [
        PHP_ADD_LIBRARY(fuzzy, 1, SSDEEP_SHARED_LIBADD)
    ],[
        AC_MSG_ERROR([fuzzy lib not found. See config.log for more information.])
    ],[]
    )

    AC_DEFINE(HAVE_SSDEEP, 1, [Whether you have SSDEEP])
    PHP_NEW_EXTENSION(ssdeep, ssdeep.c, $ext_shared)
fi