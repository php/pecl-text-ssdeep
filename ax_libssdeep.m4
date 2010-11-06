#####
#
# SYNOPSIS
#
#   AX_SSDEEP()
#
# DESCRIPTION
#
#   This macro provides tests of availability of SSDEEP library and headers.
#
#   This macro calls:
#
#     AC_SUBST(SSDEEP_LIBDIR)
#     AC_SUBST(SSDEEP_LIBS)
#     AC_SUBST(SSDEEP_INCLUDEDIR)
#
#####

AC_DEFUN([AX_SSDEEP], [
  AC_MSG_CHECKING(for ssdeep)
  AC_ARG_WITH(ssdeep,
    [[  --with-ssdeep[=PATH]   use ssdeep @<:@default=yes@:>@, optionally specify path to ssdeep build directory]],
    [withssdeep="$withval"],
    [withssdeep="yes"]
  )
  
  AC_ARG_ENABLE(debug,
    [  --enable-debug  Enable debugging],
    [ enabledebug=yes ]
  )
  
  SSDEEP_LIB_NAME="fuzzy"

  if test -z "$withssdeep" -o "$withssdeep" = "yes"; then
    for i in /usr/lib /usr/local/lib; do
      if test -f "$i/lib$SSDEEP_LIB_NAME.so"; then
        SSDEEP_LIB_DIR="$i"
      fi
    done
    if test "$SSDEEP_LIB_DIR" = ""; then
      AC_MSG_ERROR(["could not find ssdeep libfuzzy"])
    fi
  elif test "$withssdeep" = "no"; then
    AC_MSG_ERROR(["can not build with ssdeep disabled"])
  else
    if test -f "$withssdeep/lib$SSDEEP_LIB_NAME.so"; then
      SSDEEP_LIB_DIR="$withssdeep"
    else
      if test -f "$withssdeep/.libs/lib$SSDEEP_LIB_NAME.so"; then
        SSDEEP_LIB_DIR="$withssdeep"
      else
        AC_MSG_ERROR(["could not find ssdeep: $withssdeep/.libs/lib$SSDEEP_LIB_NAME.so"])
      fi
    fi
  fi

  SSDEEP_LIBDIR="-L$SSDEEP_LIB_DIR"
  SSDEEP_LIBS="-l$SSDEEP_LIB_NAME"
  SSDEEP_LIBDIR_NO_FLAG="$SSDEEP_LIB_DIR"

  if test -z "$withssdeep" -o "$withssdeep" = "yes"; then
    for i in /usr/include /usr/local/include; do
      if test -f "$i/$SSDEEP_LIB_NAME.h"; then
        SSDEEP_INCLUDEDIR="$i"
      fi
    done
    if test "$SSDEEP_INCLUDEDIR" = ""; then
      AC_MSG_ERROR(["could not find headers for ssdeep libfuzzy"])
    fi
  else
    if test -f "$withssdeep/../$SSDEEP_LIB_NAME.h"; then
      SSDEEP_INCLUDEDIR="$withssdeep/../"
    else
      if test -f "$withssdeep/$SSDEEP_LIB_NAME.h"; then
        SSDEEP_LIB_DIR="$withssdeep"
      else
        AC_MSG_ERROR(["could not find ssdeep $SSDEEP_LIB_NAME.h header file"])
      fi
    fi
  fi
  
  SSDEEP_INCLUDEDIR_NO_FLAG="$SSDEEP_INCLUDEDIR"
  SSDEEP_INCLUDEDIR="-I$SSDEEP_INCLUDEDIR"

  AC_MSG_RESULT([$SSDEEP_LIB_DIR])
    
  AC_DEFINE([SSDEEP_ENABLED], [1], [Enables ssdeep])
  
  SSDEEP_FOUND="yes"
  
  if test "$enabledebug" = "yes"; then
    echo " "
    echo "======================== Debug =============================="
    echo " "
    echo "\$SSDEEP_LIB_NAME            :  $SSDEEP_LIB_NAME"
    echo "\$SSDEEP_INC_DIR             :  $SSDEEP_INCLUDEDIR"
    echo "\$SSDEEP_INCLUDEDIR_NO_FLAG  :  $SSDEEP_INCLUDEDIR_NO_FLAG"
    echo "\$SSDEEP_LIBDIR              :  $SSDEEP_LIBDIR"
    echo "\$SSDEEP_LIBDIR_NO_FLAG      :  $SSDEEP_LIBDIR_NO_FLAG"
    echo "\$SSDEEP_FOUND               :  $SSDEEP_FOUND"
    echo "\$withssdeep                 :  $withssdeep"
    echo "\$enabledebug                :  $enabledebug"
    echo " "
    echo "============================================================="
    echo " "
  fi
  
  AC_SUBST(SSDEEP_LIBDIR)
  AC_SUBST(SSDEEP_LIBS)
  AC_SUBST(SSDEEP_INCLUDEDIR)
])
