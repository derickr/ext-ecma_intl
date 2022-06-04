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

#include "src/common.h"

#include "src/unicode/bcp47.h"

#include <unicode/uloc.h>

PHP_FUNCTION(getSupportedLocales) {
  ZEND_PARSE_PARAMETERS_NONE();

  int count = uloc_countAvailable();

  array_init_size(return_value, count);

  for (int i = 0; i < count; i++) {
    const char *locale;
    char languageTag[ULOC_FULLNAME_CAPACITY];
    locale = uloc_getAvailable(i);
    if (icuToBcp47LanguageTag(locale, languageTag)) {
      add_next_index_string(return_value, languageTag);
    }
  }
}
