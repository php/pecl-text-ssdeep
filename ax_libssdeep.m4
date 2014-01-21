#####
#
# SYNOPSIS
#
#   AX_SSDEEP()
#
# DESCRIPTION
#
#   This macro provides tests of availability for the SSDEEP library and headers.
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

  AC_CANONICAL_HOST
  LIB_EXTENSION="so"
  case $host_os in
    darwin*)
      LIB_EXTENSION="dylib"
      ;;
  esac

  SSDEEP_LIB_NAME="fuzzy"
  SSDEEP_LIB_FILENAME="lib$SSDEEP_LIB_NAME.$LIB_EXTENSION"

  if test -z "$withssdeep" -o "$withssdeep" = "yes"; then
    for i in /usr/lib /usr/local/lib; do
      if test -f "$i/$SSDEEP_LIB_FILENAME"; then
        SSDEEP_LIB_DIR="$i"
      fi
    done
    if test "$SSDEEP_LIB_DIR" = ""; then
      AC_MSG_ERROR(["Could not find '$SSDEEP_LIB_FILENAME'. Try specifying the path to the ssdeep build directory."])
    fi
  elif test "$withssdeep" = "no"; then
    AC_MSG_ERROR(["Cannot build whilst ssdeep is disabled."])
  else
    if test -f "$withssdeep/$SSDEEP_LIB_FILENAME"; then
      SSDEEP_LIB_DIR="$withssdeep"
    else
      if test -f "$withssdeep/.libs/$SSDEEP_LIB_FILENAME"; then
        SSDEEP_LIB_DIR="$withssdeep/.libs/"
      else
        AC_MSG_ERROR(["Could not find ssdeep library '$withssdeep/.libs/$SSDEEP_LIB_FILENAME'. Try specifying the path to the ssdeep build directory."])
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
      AC_MSG_ERROR(["Could not find ssdeep '$SSDEEP_LIB_NAME.h' header file. Try specifying the path to the ssdeep build directory."])
    fi
  else
    if test -f "$withssdeep/../$SSDEEP_LIB_NAME.h"; then
      SSDEEP_INCLUDEDIR="$withssdeep/../"
    else
      if test -f "$withssdeep/$SSDEEP_LIB_NAME.h"; then
        SSDEEP_INCLUDEDIR="$withssdeep"
      else
        AC_MSG_ERROR(["Could not find ssdeep '$SSDEEP_LIB_NAME.h' header file. Try specifying the path to the ssdeep build directory."])
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
    echo "\$host_os                    :  $host_os"
    echo "\$SSDEEP_LIB_NAME            :  $SSDEEP_LIB_NAME"
    echo "\$SSDEEP_LIB_FILENAME        :  $SSDEEP_LIB_FILENAME"
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
