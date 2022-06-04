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

#include "php_locale.h"
#include "src/php/classes/php_exceptions_ce.h"
#include "src/php/classes/php_locale_ce.h"
#include "src/php/handlers/php_locale_handlers.h"
#include "src/unicode/bcp47.h"

#include <unicode/ucal.h>
#include <unicode/udatpg.h>
#include <unicode/uloc.h>
#include <unicode/unumsys.h>

#define SET_PROPERTY(name)                                                     \
  if (valueLen == 0) {                                                         \
    zend_update_property_null(ecmaIntlClassLocale, object, name,               \
                              sizeof(name) - 1);                               \
  } else {                                                                     \
    zend_update_property_stringl(ecmaIntlClassLocale, object, name,            \
                                 sizeof(name) - 1, value, valueLen);           \
  }

zend_object *ecmaIntlLocaleObjCreate(zend_class_entry *classType) {
  ecmaIntlLocaleObj *localeObj;

  localeObj = zend_object_alloc(sizeof(ecmaIntlLocaleObj), classType);
  localeObj->bcp47Locale = NULL;

  zend_object_std_init(&localeObj->std, classType);
  object_properties_init(&localeObj->std, classType);

  localeObj->std.handlers = &ecmaIntlLocaleObjHandlers;

  return &localeObj->std;
}

void localeSetBaseName(zend_object *object, char *localeId) {
  char *baseName = NULL, *value = NULL;
  int valueLen;
  UErrorCode status = U_ZERO_ERROR;

  baseName = (char *)ecalloc(1, sizeof(char *) * ULOC_FULLNAME_CAPACITY);
  uloc_getBaseName(localeId, baseName, ULOC_FULLNAME_CAPACITY, &status);

  /* The base name is in ICU format, so we need to convert it to BCP 47 format.
   */
  value = (char *)ecalloc(1, sizeof(char *) * ULOC_FULLNAME_CAPACITY);
  valueLen = icuToBcp47LanguageTag(baseName, value);

  SET_PROPERTY(PROPERTY_BASE_NAME)

  efree(baseName);
  efree(value);
}

void localeSetCalendar(zend_object *object, char *localeId) {
  char *value = NULL;
  int valueLen;
  UErrorCode status = U_ZERO_ERROR;

  value = (char *)emalloc(sizeof(char *) * ULOC_FULLNAME_CAPACITY);
  valueLen = uloc_getKeywordValue(localeId, KEYWORD_ICU_CALENDAR, value,
                                  ULOC_FULLNAME_CAPACITY, &status);

  if (valueLen == 0) {
    zend_update_property_null(ecmaIntlClassLocale, object, PROPERTY_CALENDAR,
                              sizeof(PROPERTY_CALENDAR) - 1);
  } else {
    zend_update_property_string(
        ecmaIntlClassLocale, object, PROPERTY_CALENDAR,
        sizeof(PROPERTY_CALENDAR) - 1,
        uloc_toUnicodeLocaleType(KEYWORD_ICU_CALENDAR, value));
  }

  efree(value);
}

void localeSetCalendars(zend_object *object, char *localeId) {
  UEnumeration *values = NULL;
  UErrorCode status = U_ZERO_ERROR;
  int count, length, i;
  const char *identifier;
  zval calendars;

  values = ucal_getKeywordValuesForLocale(KEYWORD_ICU_CALENDAR, localeId, 1,
                                          &status);

  if (U_FAILURE(status)) {
    zend_throw_error(ecmaIntlClassIcuException, "%s", u_errorName(status));
  } else {
    count = uenum_count(values, &status);
    uenum_reset(values, &status);

    array_init_size(&calendars, count);

    for (i = 0; i < count; i++) {
      identifier = uenum_next(values, &length, &status);
      add_next_index_string(&calendars, uloc_toUnicodeLocaleType(
                                            KEYWORD_ICU_CALENDAR, identifier));
    }

    zend_update_property(ecmaIntlClassLocale, object, PROPERTY_CALENDARS,
                         sizeof(PROPERTY_CALENDARS) - 1, &calendars);

    zend_array_release(Z_ARRVAL(calendars));
  }

  uenum_close(values);
}

void localeSetCaseFirst(zend_object *object, char *localeId) {
  char *value = NULL;
  int valueLen;
  UErrorCode status = U_ZERO_ERROR;

  value = (char *)ecalloc(1, sizeof(char *) * ULOC_FULLNAME_CAPACITY);
  valueLen = uloc_getKeywordValue(localeId, KEYWORD_ICU_CASE_FIRST, value,
                                  ULOC_FULLNAME_CAPACITY, &status);

  SET_PROPERTY(PROPERTY_CASE_FIRST)

  efree(value);
}

void localeSetCollation(zend_object *object, char *localeId) {
  char *value = NULL;
  int valueLen;
  UErrorCode status = U_ZERO_ERROR;

  value = (char *)ecalloc(1, sizeof(char *) * ULOC_FULLNAME_CAPACITY);
  valueLen = uloc_getKeywordValue(localeId, KEYWORD_ICU_COLLATION, value,
                                  ULOC_FULLNAME_CAPACITY, &status);

  if (valueLen == 0) {
    zend_update_property_null(ecmaIntlClassLocale, object, PROPERTY_COLLATION,
                              sizeof(PROPERTY_COLLATION) - 1);
  } else {
    zend_update_property_string(
        ecmaIntlClassLocale, object, PROPERTY_COLLATION,
        sizeof(PROPERTY_COLLATION) - 1,
        uloc_toUnicodeLocaleType(KEYWORD_ICU_COLLATION, value));
  }

  efree(value);
}

void localeSetHourCycle(zend_object *object, char *localeId) {
  char *value = NULL;
  int valueLen;
  UErrorCode status = U_ZERO_ERROR;

  value = (char *)ecalloc(1, sizeof(char *) * ULOC_FULLNAME_CAPACITY);
  valueLen = uloc_getKeywordValue(localeId, KEYWORD_ICU_HOUR_CYCLE, value,
                                  ULOC_FULLNAME_CAPACITY, &status);

  SET_PROPERTY(PROPERTY_HOUR_CYCLE)

  efree(value);
}

void localeSetHourCycles(zend_object *object, char *localeId) {
  UDateTimePatternGenerator *patternGenerator;
  UDateFormatHourCycle hourCycle;
  UErrorCode status = U_ZERO_ERROR;
  zval hourCycles;

  patternGenerator = udatpg_open(localeId, &status);

  if (U_FAILURE(status)) {
    zend_throw_error(ecmaIntlClassIcuException, "%s", u_errorName(status));
  } else {
    array_init_size(&hourCycles, 1);

    hourCycle = udatpg_getDefaultHourCycle(patternGenerator, &status);

    if (U_FAILURE(status)) {
      zend_throw_error(ecmaIntlClassIcuException, "%s", u_errorName(status));
    } else {
      if (hourCycle == UDAT_HOUR_CYCLE_11) {
        add_next_index_string(&hourCycles, HOUR_H_11);
      } else if (hourCycle == UDAT_HOUR_CYCLE_23) {
        add_next_index_string(&hourCycles, HOUR_H_23);
      } else if (hourCycle == UDAT_HOUR_CYCLE_24) {
        add_next_index_string(&hourCycles, HOUR_H_24);
      } else {
        add_next_index_string(&hourCycles, HOUR_H_12);
      }
    }

    zend_update_property(ecmaIntlClassLocale, object, PROPERTY_HOUR_CYCLES,
                         sizeof(PROPERTY_HOUR_CYCLES) - 1, &hourCycles);
    zend_array_release(Z_ARRVAL(hourCycles));
  }

  udatpg_close(patternGenerator);
}

void localeSetLanguage(zend_object *object, char *localeId) {
  char *value = NULL;
  int valueLen;
  UErrorCode status = U_ZERO_ERROR;

  value = (char *)ecalloc(1, sizeof(char *) * ULOC_FULLNAME_CAPACITY);
  valueLen = uloc_getLanguage(localeId, value, ULOC_FULLNAME_CAPACITY, &status);

  SET_PROPERTY(PROPERTY_LANGUAGE)

  efree(value);
}

void localeSetNumberingSystem(zend_object *object, char *localeId) {
  char *value = NULL;
  int valueLen;
  UErrorCode status = U_ZERO_ERROR;

  value = (char *)ecalloc(1, sizeof(char *) * ULOC_FULLNAME_CAPACITY);
  valueLen = uloc_getKeywordValue(localeId, KEYWORD_ICU_NUMBERING_SYSTEM, value,
                                  ULOC_FULLNAME_CAPACITY, &status);

  if (valueLen == 0) {
    zend_update_property_null(ecmaIntlClassLocale, object,
                              PROPERTY_NUMBERING_SYSTEM,
                              sizeof(PROPERTY_NUMBERING_SYSTEM) - 1);
  } else {
    zend_update_property_string(
        ecmaIntlClassLocale, object, PROPERTY_NUMBERING_SYSTEM,
        sizeof(PROPERTY_NUMBERING_SYSTEM) - 1,
        uloc_toUnicodeLocaleType(KEYWORD_ICU_NUMBERING_SYSTEM, value));
  }

  efree(value);
}

void localeSetNumberingSystems(zend_object *object, char *localeId) {
  UNumberingSystem *numberingSystem;
  UErrorCode status = U_ZERO_ERROR;
  zval numberingSystems;

  numberingSystem = unumsys_open(localeId, &status);

  if (U_FAILURE(status)) {
    zend_throw_error(ecmaIntlClassIcuException, "%s", u_errorName(status));
  } else {
    array_init_size(&numberingSystems, 1);

    add_next_index_string(
        &numberingSystems,
        uloc_toUnicodeLocaleType(KEYWORD_ICU_NUMBERING_SYSTEM,
                                 unumsys_getName(numberingSystem)));

    zend_update_property(
        ecmaIntlClassLocale, object, PROPERTY_NUMBERING_SYSTEMS,
        sizeof(PROPERTY_NUMBERING_SYSTEMS) - 1, &numberingSystems);

    zend_array_release(Z_ARRVAL(numberingSystems));
  }

  unumsys_close(numberingSystem);
}

void localeSetNumeric(zend_object *object, char *localeId) {
  char *value = NULL;
  UErrorCode status = U_ZERO_ERROR;

  value = (char *)ecalloc(1, sizeof(char *) * ULOC_FULLNAME_CAPACITY);
  uloc_getKeywordValue(localeId, KEYWORD_ICU_NUMERIC, value,
                       ULOC_FULLNAME_CAPACITY, &status);

  if (strcmp(value, "yes") == 0) {
    zend_update_property_bool(ecmaIntlClassLocale, object, PROPERTY_NUMERIC,
                              sizeof(PROPERTY_NUMERIC) - 1, 1);
  } else {
    zend_update_property_bool(ecmaIntlClassLocale, object, PROPERTY_NUMERIC,
                              sizeof(PROPERTY_NUMERIC) - 1, 0);
  }

  efree(value);
}

void localeSetRegion(zend_object *object, char *localeId) {
  char *value = NULL;
  int valueLen;
  UErrorCode status = U_ZERO_ERROR;

  value = (char *)ecalloc(1, sizeof(char *) * ULOC_FULLNAME_CAPACITY);
  valueLen = uloc_getCountry(localeId, value, ULOC_FULLNAME_CAPACITY, &status);

  SET_PROPERTY(PROPERTY_REGION)

  efree(value);
}

void localeSetScript(zend_object *object, char *localeId) {
  char *value = NULL;
  int valueLen;
  UErrorCode status = U_ZERO_ERROR;

  value = (char *)ecalloc(1, sizeof(char *) * ULOC_FULLNAME_CAPACITY);
  valueLen = uloc_getScript(localeId, value, ULOC_FULLNAME_CAPACITY, &status);

  SET_PROPERTY(PROPERTY_SCRIPT)

  efree(value);
}
