PHP_ARG_ENABLE(
  [ecma_intl],
  [for internationalization support, Ecma-style (ECMA-402)],
  [AS_HELP_STRING([--enable-ecma_intl], [Enable internationalization support, Ecma-style (ECMA-402)])],
  [yes]
)

if test "$PHP_ECMA_INTL" != "no"; then
  PKG_CHECK_MODULES([ICU], [icu-uc >= 71.1 icu-i18n icu-io])

  PHP_EVAL_INCLINE($ICU_CFLAGS)
  PHP_EVAL_LIBLINE($ICU_LIBS, ECMA_INTL_SHARED_LIBADD)

  PHP_SUBST(ECMA_INTL_SHARED_LIBADD)
  AC_DEFINE(HAVE_ECMA_INTL, 1, [ Have ecma_intl support ])

  ECMA_INTL_COMMON_FLAGS="$ICU_CFLAGS"

  PHP_NEW_EXTENSION(ecma_intl, php_ecma_intl.c \
    src/exceptions.c \
    src/functions.c \
    src/locale/locale.c \
    src/locale/options.c \
    src/locale/week_info.c \
    , $ext_shared,,$ECMA_INTL_COMMON_FLAGS,cxx)

  PHP_ECMA_INTL_CXX_SOURCES="src/measure_unit_bridge.cpp"

  PHP_REQUIRE_CXX()
  PHP_CXX_COMPILE_STDCXX(11, mandatory, PHP_ECMA_INTL_STDCXX)
  PHP_ECMA_INTL_CXX_FLAGS="$ECMA_INTL_COMMON_FLAGS $PHP_ECMA_INTL_STDCXX $ICU_CXXFLAGS"

  if test "$ext_shared" = "no"; then
    PHP_ADD_SOURCES(PHP_EXT_DIR(ecma_intl), $PHP_ECMA_INTL_CXX_SOURCES, $PHP_ECMA_INTL_CXX_FLAGS)
  else
    PHP_ADD_SOURCES_X(PHP_EXT_DIR(ecma_intl), $PHP_ECMA_INTL_CXX_SOURCES, $PHP_ECMA_INTL_CXX_FLAGS, shared_objects_ecma_intl, yes)
  fi

  PHP_ADD_BUILD_DIR($ext_builddir/src)
fi
