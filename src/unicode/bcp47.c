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

#include "bcp47.h"
#include "src/php/classes/php_exceptions_ce.h"

#include <unicode/uloc.h>

int icuToBcp47LanguageTag(const char *localeId, char *languageTag) {
  int languageTagLen;
  UErrorCode status = U_ZERO_ERROR;

  languageTagLen = uloc_toLanguageTag(localeId, languageTag,
                                      ULOC_FULLNAME_CAPACITY, true, &status);

  if (U_FAILURE(status)) {
    zend_throw_error(ecmaIntlClassRangeError, "invalid language tag");
    return 0;
  }

  return languageTagLen;
}
