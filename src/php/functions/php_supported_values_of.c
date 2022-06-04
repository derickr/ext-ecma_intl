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

#include "src/php/classes/php_exceptions_ce.h"
#include "src/unicode/units.h"

#include <unicode/ucal.h>
#include <unicode/ucol.h>
#include <unicode/ucurr.h>
#include <unicode/unumsys.h>

#define CATEGORY_CALENDAR "calendar"
#define CATEGORY_COLLATION "collation"
#define CATEGORY_CURRENCY "currency"
#define CATEGORY_NUMBERING_SYSTEM "numberingSystem"
#define CATEGORY_TIME_ZONE "timeZone"
#define CATEGORY_UNIT "unit"

#define UNIT_TOTAL_CAPACITY 200

static zend_always_inline int phpArrayStringCaseCompare(Bucket *f, Bucket *s) {
  return string_case_compare_function(&f->val, &s->val);
}

PHP_FUNCTION(supportedValuesOf) {
  zend_string *key;
  UEnumeration *values = NULL;
  UErrorCode status = U_ZERO_ERROR;
  int identifierLen;
  const char *identifier, **units = NULL;

  ZEND_PARSE_PARAMETERS_START(1, 1)
  Z_PARAM_STR(key)
  ZEND_PARSE_PARAMETERS_END();

  if (strcasecmp(CATEGORY_CALENDAR, ZSTR_VAL(key)) == 0) {
    values = ucal_getKeywordValuesForLocale("calendar", NULL, 0, &status);
  } else if (strcasecmp(CATEGORY_COLLATION, ZSTR_VAL(key)) == 0) {
    values = ucol_getKeywordValues("collation", &status);
  } else if (strcasecmp(CATEGORY_CURRENCY, ZSTR_VAL(key)) == 0) {
    values = ucurr_openISOCurrencies(UCURR_ALL, &status);
  } else if (strcasecmp(CATEGORY_NUMBERING_SYSTEM, ZSTR_VAL(key)) == 0) {
    values = unumsys_openAvailableNames(&status);
  } else if (strcasecmp(CATEGORY_TIME_ZONE, ZSTR_VAL(key)) == 0) {
    values = ucal_openTimeZones(&status);
  } else if (strcasecmp(CATEGORY_UNIT, ZSTR_VAL(key)) == 0) {
    units = (const char **)emalloc(sizeof(char *) * UNIT_TOTAL_CAPACITY);
    values = icuGetMeasurementUnits(units, &status);
  } else {
    zend_throw_error(ecmaIntlClassRangeError,
                     "Unknown key for Ecma\\Intl\\supportedValuesOf()");
    RETURN_THROWS();
  }

  if (U_FAILURE(status)) {
    zend_throw_error(ecmaIntlClassIcuException, "%s", u_errorName(status));
    RETURN_THROWS();
  }

  int count = uenum_count(values, &status);
  uenum_reset(values, &status);

  array_init_size(return_value, count);

  for (int i = 0; i < count; i++) {
    identifier = uenum_next(values, &identifierLen, &status);

    if (strcasecmp(CATEGORY_CALENDAR, ZSTR_VAL(key)) == 0) {
      add_next_index_string(
          return_value,
          uloc_toUnicodeLocaleType(KEYWORD_ICU_CALENDAR, identifier));
    } else if (strcasecmp(CATEGORY_COLLATION, ZSTR_VAL(key)) == 0) {
      add_next_index_string(
          return_value,
          uloc_toUnicodeLocaleType(KEYWORD_ICU_COLLATION, identifier));
    } else if (strcasecmp(CATEGORY_NUMBERING_SYSTEM, ZSTR_VAL(key)) == 0) {
      add_next_index_string(
          return_value,
          uloc_toUnicodeLocaleType(KEYWORD_ICU_NUMBERING_SYSTEM, identifier));
    } else {
      add_next_index_stringl(return_value, identifier, identifierLen);
    }
  }

  uenum_close(values);

  if (units) {
    efree(units);
  }

  zend_hash_sort(Z_ARRVAL_P(return_value), phpArrayStringCaseCompare, 1);
}
