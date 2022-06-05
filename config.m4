PHP_ARG_ENABLE(
  [ecma_intl],
  [for i18n support, Ecma-style (ECMA-402)],
  [AS_HELP_STRING(
    [--enable-ecma_intl],
    [Enable i18n support, Ecma-style (ECMA-402)])
  ],
  [yes]
)

if test "$PHP_ECMA_INTL" != "no"; then
  PKG_CHECK_MODULES([ICU], [icu-uc >= 71.1 icu-i18n icu-io])

  PHP_EVAL_INCLINE($ICU_CFLAGS)
  PHP_EVAL_LIBLINE($ICU_LIBS, ECMA_INTL_SHARED_LIBADD)

  PHP_SUBST(ECMA_INTL_SHARED_LIBADD)
  AC_DEFINE(HAVE_ECMA_INTL, 1, [ Have ecma_intl support ])

  ECMA_INTL_COMMON_FLAGS="$ICU_CFLAGS"

  PHP_NEW_EXTENSION(ecma_intl,                                               \
                                                                             \
    src/php/classes/php_exceptions_ce.c                                      \
    src/php/classes/php_locale_ce.c                                          \
    src/php/classes/php_locale_options_ce.c                                  \
    src/php/classes/php_locale_week_info_ce.c                                \
                                                                             \
    src/php/functions/php_get_canonical_locales.c                            \
    src/php/functions/php_get_supported_locales.c                            \
    src/php/functions/php_supported_values_of.c                              \
                                                                             \
    src/php/handlers/php_locale_handlers.c                                   \
    src/php/handlers/php_locale_options_handlers.c                           \
    src/php/handlers/php_locale_week_info_handlers.c                         \
                                                                             \
    src/php/objects/php_locale.c                                             \
    src/php/objects/php_locale_options.c                                     \
    src/php/objects/php_locale_week_info.c                                   \
                                                                             \
    src/unicode/bcp47.c                                                      \
                                                                             \
    php_ecma_intl.c                                                          \
                                                                             \
    , $ext_shared, , $ECMA_INTL_COMMON_FLAGS, cxx)

  PHP_ECMA_INTL_CXX_SOURCES="                                                \
    src/unicode/builder.cpp                                                  \
    src/unicode/units.cpp                                                    \
    "

  PHP_REQUIRE_CXX()
  PHP_CXX_COMPILE_STDCXX(11, mandatory, PHP_ECMA_INTL_STDCXX)
  PHP_ECMA_INTL_CXX_FLAGS="                                                  \
    $ECMA_INTL_COMMON_FLAGS                                                  \
    $PHP_ECMA_INTL_STDCXX                                                    \
    $ICU_CXXFLAGS                                                            \
    "

  if test "$ext_shared" = "no"; then
    PHP_ADD_SOURCES(
      PHP_EXT_DIR(ecma_intl),
      $PHP_ECMA_INTL_CXX_SOURCES,
      $PHP_ECMA_INTL_CXX_FLAGS
    )
  else
    PHP_ADD_SOURCES_X(
      PHP_EXT_DIR(ecma_intl),
      $PHP_ECMA_INTL_CXX_SOURCES,
      $PHP_ECMA_INTL_CXX_FLAGS,
      shared_objects_ecma_intl,
      yes
    )
  fi

  PHP_ADD_BUILD_DIR($ext_builddir/src, 1)
  PHP_ADD_BUILD_DIR($ext_builddir/src/php, 1)
  PHP_ADD_BUILD_DIR($ext_builddir/src/php/classes, 1)
  PHP_ADD_BUILD_DIR($ext_builddir/src/php/functions, 1)
  PHP_ADD_BUILD_DIR($ext_builddir/src/php/handlers, 1)
  PHP_ADD_BUILD_DIR($ext_builddir/src/php/objects, 1)
  PHP_ADD_BUILD_DIR($ext_builddir/src/unicode, 1)

  PHP_ADD_EXTENSION_DEP(ecma_intl, spl)
fi
