/*
   +----------------------------------------------------------------------+
   | ecma_intl extension for PHP                                          |
   | Internationalization Support, Ecma-style (ECMA-402)                  |
   +----------------------------------------------------------------------+
   | Copyright (c) Ben Ramsey <ben@benramsey.com>                         |
   |                                                                      |
   | Licensed under the Apache License, Version 2.0 (the "License");      |
   | you may not use this file except in compliance with the License.     |
   | You may obtain a copy of the License at                              |
   |                                                                      |
   |     http://www.apache.org/licenses/LICENSE-2.0                       |
   |                                                                      |
   | Unless required by applicable law or agreed to in writing, software  |
   | distributed under the License is distributed on an "AS IS" BASIS,    |
   | WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or      |
   | implied. See the License for the specific language governing         |
   | permissions and limitations under the License.                       |
   +----------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>

#include <ext/standard/info.h>
#include <unicode/ucal.h>
#include <unicode/uchar.h>
#include <unicode/uversion.h>

#include "php_ecma_intl.h"
#include "src/exceptions.h"
#include "src/functions_arginfo.h"
#include "src/locale/locale.h"
#include "src/locale/options.h"
#include "src/locale/week_info.h"

zend_module_entry ecma_intl_module_entry = {STANDARD_MODULE_HEADER,
                                            "ecma_intl",
                                            ext_functions,
                                            PHP_MINIT(ecma_intl),
                                            PHP_MSHUTDOWN(ecma_intl),
                                            PHP_RINIT(ecma_intl),
                                            PHP_RSHUTDOWN(ecma_intl),
                                            PHP_MINFO(ecma_intl),
                                            PHP_ECMA_INTL_VERSION,
                                            STANDARD_MODULE_PROPERTIES};

#ifdef COMPILE_DL_ECMA_INTL
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(ecma_intl)
#endif

PHP_MINIT_FUNCTION(ecma_intl) {
  ecma_intl_register_exceptions();
  ecma_intl_register_Locale();
  ecma_intl_register_Locale_Options();
  ecma_intl_register_Locale_WeekInfo();

  return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(ecma_intl) { return SUCCESS; }

PHP_RINIT_FUNCTION(ecma_intl) {
#if defined(ZTS) && defined(COMPILE_DL_ECMA_INTL)
  ZEND_TSRMLS_CACHE_UPDATE();
#endif

  return SUCCESS;
}

PHP_RSHUTDOWN_FUNCTION(ecma_intl) { return SUCCESS; }

PHP_MINFO_FUNCTION(ecma_intl) {
  UErrorCode status = U_ZERO_ERROR;
  const char *timeZoneDataVersion = NULL;

  timeZoneDataVersion = ucal_getTZDataVersion(&status);
  if (U_ZERO_ERROR != status) {
    timeZoneDataVersion = "n/a";
  }

  php_info_print_table_start();
  php_info_print_table_header(
      2, "Internationalization Support, Ecma-style (ECMA-402)", "enabled");
  php_info_print_table_row(2, "ecma_intl version", PHP_ECMA_INTL_VERSION);
  php_info_print_table_row(2, "ICU version", U_ICU_VERSION);
  php_info_print_table_row(2, "ICU Data version", U_ICU_DATA_VERSION);
  php_info_print_table_row(2, "ICU TZData version", timeZoneDataVersion);
  php_info_print_table_row(2, "ICU Unicode version", U_UNICODE_VERSION);
  php_info_print_table_end();
}
