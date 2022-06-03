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

#include <unicode/ucal.h>
#include <unicode/udatpg.h>
#include <unicode/uloc.h>

#include "../common.h"
#include "../functions.h"
#include "locale.h"
#include "locale_arginfo.h"
#include "locale_builder_bridge.h"
#include "locale_options.h"

#include <zend_interfaces.h>

#define SET_PROPERTY(name)                                                     \
  if (valueLen == 0) {                                                         \
    zend_update_property_null(ecmaIntlCeLocale, object, name,                  \
                              sizeof(name) - 1);                               \
  } else {                                                                     \
    zend_update_property_stringl(ecmaIntlCeLocale, object, name,               \
                                 sizeof(name) - 1, value, valueLen);           \
  }

zend_class_entry *ecmaIntlCeLocale = NULL;

static zend_object_handlers ecmaIntlLocaleObjHandlers;
static zend_object *ecmaIntlLocaleObjCreate(zend_class_entry *classType);
static void ecmaIntlLocaleObjFree(zend_object *object);

static void setBaseName(zend_object *object, char *localeId);
static void setCalendar(zend_object *object, char *localeId);
static void setCalendars(zend_object *object, char *localeId);
static void setCaseFirst(zend_object *object, char *localeId);
static void setCollation(zend_object *object, char *localeId);
static void setHourCycle(zend_object *object, char *localeId);
static void setHourCycles(zend_object *object, char *localeId);
static void setLanguage(zend_object *object, char *localeId);
static void setNumberingSystem(zend_object *object, char *localeId);
static void setNumeric(zend_object *object, char *localeId);
static void setRegion(zend_object *object, char *localeId);
static void setScript(zend_object *object, char *localeId);

static zend_object *ecmaIntlLocaleObjCreate(zend_class_entry *classType) {
  ecmaIntlLocaleObj *localeObj;

  localeObj = zend_object_alloc(sizeof(ecmaIntlLocaleObj), classType);
  localeObj->bcp47Locale = NULL;

  zend_object_std_init(&localeObj->std, classType);
  object_properties_init(&localeObj->std, classType);

  localeObj->std.handlers = &ecmaIntlLocaleObjHandlers;

  return &localeObj->std;
}

static void ecmaIntlLocaleObjFree(zend_object *object) {
  ecmaIntlLocaleObj *localeObj = ecmaIntlLocaleObjFromObj(object);

  zend_object_std_dtor(&localeObj->std);

  if (localeObj->bcp47Locale) {
    efree(localeObj->bcp47Locale);
    localeObj->bcp47Locale = NULL;
  }
}

static void setBaseName(zend_object *object, char *localeId) {
  char *baseName = NULL, *value = NULL;
  int valueLen;
  UErrorCode status = U_ZERO_ERROR;

  baseName = (char *)ecalloc(1, sizeof(char *) * ULOC_FULLNAME_CAPACITY);
  uloc_getBaseName(localeId, baseName, ULOC_FULLNAME_CAPACITY, &status);

  /* The base name is in ICU format, so we need to convert it to BCP 47 format.
   */
  value = (char *)ecalloc(1, sizeof(char *) * ULOC_FULLNAME_CAPACITY);
  valueLen = ecmaIntlToCanonicalBcp47LanguageTag(baseName, value);

  SET_PROPERTY(PROPERTY_BASE_NAME)

  efree(baseName);
  efree(value);
}

static void setCalendar(zend_object *object, char *localeId) {
  char *value = NULL;
  int valueLen;
  UErrorCode status = U_ZERO_ERROR;

  value = (char *)emalloc(sizeof(char *) * ULOC_FULLNAME_CAPACITY);
  valueLen = uloc_getKeywordValue(localeId, KEYWORD_ICU_CALENDAR, value,
                                  ULOC_FULLNAME_CAPACITY, &status);

  if (valueLen == 0) {
    zend_update_property_null(ecmaIntlCeLocale, object, PROPERTY_CALENDAR,
                              sizeof(PROPERTY_CALENDAR) - 1);
  } else {
    zend_update_property_string(
        ecmaIntlCeLocale, object, PROPERTY_CALENDAR,
        sizeof(PROPERTY_CALENDAR) - 1,
        uloc_toUnicodeLocaleType(KEYWORD_ICU_CALENDAR, value));
  }

  efree(value);
}

static void setCalendars(zend_object *object, char *localeId) {
  UEnumeration *values = NULL;
  UErrorCode status = U_ZERO_ERROR;
  int count, length, i;
  const char *identifier;
  zval calendars;

  values = ucal_getKeywordValuesForLocale(KEYWORD_ICU_CALENDAR, localeId, 1,
                                          &status);

  if (U_FAILURE(status)) {
    zend_throw_error(ecmaIntlCeIcuException, "%s", u_errorName(status));
  } else {
    count = uenum_count(values, &status);
    uenum_reset(values, &status);

    array_init_size(&calendars, count);

    for (i = 0; i < count; i++) {
      identifier = uenum_next(values, &length, &status);
      add_next_index_string(&calendars, uloc_toUnicodeLocaleType(
                                            KEYWORD_ICU_CALENDAR, identifier));
    }

    zend_update_property(ecmaIntlCeLocale, object, PROPERTY_CALENDARS,
                         sizeof(PROPERTY_CALENDARS) - 1, &calendars);

    zend_array_release(Z_ARRVAL(calendars));
  }

  uenum_close(values);
}

static void setCaseFirst(zend_object *object, char *localeId) {
  char *value = NULL;
  int valueLen;
  UErrorCode status = U_ZERO_ERROR;

  value = (char *)ecalloc(1, sizeof(char *) * ULOC_FULLNAME_CAPACITY);
  valueLen = uloc_getKeywordValue(localeId, KEYWORD_ICU_CASE_FIRST, value,
                                  ULOC_FULLNAME_CAPACITY, &status);

  SET_PROPERTY(PROPERTY_CASE_FIRST)

  efree(value);
}

static void setCollation(zend_object *object, char *localeId) {
  char *value = NULL;
  int valueLen;
  UErrorCode status = U_ZERO_ERROR;

  value = (char *)ecalloc(1, sizeof(char *) * ULOC_FULLNAME_CAPACITY);
  valueLen = uloc_getKeywordValue(localeId, KEYWORD_ICU_COLLATION, value,
                                  ULOC_FULLNAME_CAPACITY, &status);

  if (valueLen == 0) {
    zend_update_property_null(ecmaIntlCeLocale, object, PROPERTY_COLLATION,
                              sizeof(PROPERTY_COLLATION) - 1);
  } else {
    zend_update_property_string(
        ecmaIntlCeLocale, object, PROPERTY_COLLATION,
        sizeof(PROPERTY_COLLATION) - 1,
        uloc_toUnicodeLocaleType(KEYWORD_ICU_COLLATION, value));
  }

  efree(value);
}

static void setHourCycle(zend_object *object, char *localeId) {
  char *value = NULL;
  int valueLen;
  UErrorCode status = U_ZERO_ERROR;

  value = (char *)ecalloc(1, sizeof(char *) * ULOC_FULLNAME_CAPACITY);
  valueLen = uloc_getKeywordValue(localeId, KEYWORD_ICU_HOUR_CYCLE, value,
                                  ULOC_FULLNAME_CAPACITY, &status);

  SET_PROPERTY(PROPERTY_HOUR_CYCLE)

  efree(value);
}

static void setHourCycles(zend_object *object, char *localeId) {
  UDateTimePatternGenerator *patternGenerator;
  UDateFormatHourCycle hourCycle;
  UErrorCode status = U_ZERO_ERROR;
  zval hourCycles;

  patternGenerator = udatpg_open(localeId, &status);

  if (U_FAILURE(status)) {
    zend_throw_error(ecmaIntlCeIcuException, "%s", u_errorName(status));
  } else {
    array_init_size(&hourCycles, 1);

    hourCycle = udatpg_getDefaultHourCycle(patternGenerator, &status);

    if (U_FAILURE(status)) {
      zend_throw_error(ecmaIntlCeIcuException, "%s", u_errorName(status));
    } else {
      if (hourCycle == UDAT_HOUR_CYCLE_11) {
        add_next_index_string(&hourCycles, HOUR_H11);
      } else if (hourCycle == UDAT_HOUR_CYCLE_23) {
        add_next_index_string(&hourCycles, HOUR_H23);
      } else if (hourCycle == UDAT_HOUR_CYCLE_24) {
        add_next_index_string(&hourCycles, HOUR_H24);
      } else {
        add_next_index_string(&hourCycles, HOUR_H12);
      }
    }

    zend_update_property(ecmaIntlCeLocale, object, PROPERTY_HOUR_CYCLES,
                         sizeof(PROPERTY_HOUR_CYCLES) - 1, &hourCycles);
    zend_array_release(Z_ARRVAL(hourCycles));
  }

  udatpg_close(patternGenerator);
}

static void setLanguage(zend_object *object, char *localeId) {
  char *value = NULL;
  int valueLen;
  UErrorCode status = U_ZERO_ERROR;

  value = (char *)ecalloc(1, sizeof(char *) * ULOC_FULLNAME_CAPACITY);
  valueLen = uloc_getLanguage(localeId, value, ULOC_FULLNAME_CAPACITY, &status);

  SET_PROPERTY(PROPERTY_LANGUAGE)

  efree(value);
}

static void setNumberingSystem(zend_object *object, char *localeId) {
  char *value = NULL;
  int valueLen;
  UErrorCode status = U_ZERO_ERROR;

  value = (char *)ecalloc(1, sizeof(char *) * ULOC_FULLNAME_CAPACITY);
  valueLen = uloc_getKeywordValue(localeId, KEYWORD_ICU_NUMBERING_SYSTEM, value,
                                  ULOC_FULLNAME_CAPACITY, &status);

  if (valueLen == 0) {
    zend_update_property_null(ecmaIntlCeLocale, object,
                              PROPERTY_NUMBERING_SYSTEM,
                              sizeof(PROPERTY_NUMBERING_SYSTEM) - 1);
  } else {
    zend_update_property_string(
        ecmaIntlCeLocale, object, PROPERTY_NUMBERING_SYSTEM,
        sizeof(PROPERTY_NUMBERING_SYSTEM) - 1,
        uloc_toUnicodeLocaleType(KEYWORD_ICU_NUMBERING_SYSTEM, value));
  }

  efree(value);
}

static void setNumeric(zend_object *object, char *localeId) {
  char *value = NULL;
  UErrorCode status = U_ZERO_ERROR;

  value = (char *)ecalloc(1, sizeof(char *) * ULOC_FULLNAME_CAPACITY);
  uloc_getKeywordValue(localeId, KEYWORD_ICU_NUMERIC, value,
                       ULOC_FULLNAME_CAPACITY, &status);

  if (strcmp(value, "yes") == 0) {
    zend_update_property_bool(ecmaIntlCeLocale, object, PROPERTY_NUMERIC,
                              sizeof(PROPERTY_NUMERIC) - 1, 1);
  } else {
    zend_update_property_bool(ecmaIntlCeLocale, object, PROPERTY_NUMERIC,
                              sizeof(PROPERTY_NUMERIC) - 1, 0);
  }

  efree(value);
}

static void setRegion(zend_object *object, char *localeId) {
  char *value = NULL;
  int valueLen;
  UErrorCode status = U_ZERO_ERROR;

  value = (char *)ecalloc(1, sizeof(char *) * ULOC_FULLNAME_CAPACITY);
  valueLen = uloc_getCountry(localeId, value, ULOC_FULLNAME_CAPACITY, &status);

  SET_PROPERTY(PROPERTY_REGION)

  efree(value);
}

static void setScript(zend_object *object, char *localeId) {
  char *value = NULL;
  int valueLen;
  UErrorCode status = U_ZERO_ERROR;

  value = (char *)ecalloc(1, sizeof(char *) * ULOC_FULLNAME_CAPACITY);
  valueLen = uloc_getScript(localeId, value, ULOC_FULLNAME_CAPACITY, &status);

  SET_PROPERTY(PROPERTY_SCRIPT)

  efree(value);
}

PHP_METHOD(Ecma_Intl_Locale, __construct) {
  char *tag = NULL, *bcp47Locale = NULL, *icuLocale = NULL;
  size_t tagLen = 0, bcp47LocaleLen = 0;
  zval *options = NULL;
  UErrorCode status = U_ZERO_ERROR;

  ZEND_PARSE_PARAMETERS_START(1, 2)
  Z_PARAM_STRING(tag, tagLen)
  Z_PARAM_OPTIONAL
  Z_PARAM_OBJECT_OF_CLASS_OR_NULL(options, ecmaIntlCeLocaleOptions)
  ZEND_PARSE_PARAMETERS_END();

  if (tagLen == 0) {
    zend_throw_error(ecmaIntlCeRangeError, "invalid language tag");
  }

  zval *object = getThis();
  ecmaIntlLocaleObj *locale = Z_ECMA_LOCALE_P(object);

  bcp47Locale = (char *)ecalloc(1, sizeof(char *) * ULOC_FULLNAME_CAPACITY);
  icuLocale = (char *)ecalloc(1, sizeof(char *) * ULOC_FULLNAME_CAPACITY);

  if (options) {
    char *constructedLocale =
        (char *)ecalloc(1, sizeof(char *) * ULOC_FULLNAME_CAPACITY);
    if (ecmaIntlBuildLocale(constructedLocale, tag,
                            Z_ECMA_LOCALE_OPTIONS_P(options))) {
      bcp47LocaleLen =
          ecmaIntlToCanonicalBcp47LanguageTag(constructedLocale, bcp47Locale);
      uloc_canonicalize(constructedLocale, icuLocale, ULOC_FULLNAME_CAPACITY,
                        &status);
    }
    efree(constructedLocale);
  } else {
    bcp47LocaleLen = ecmaIntlToCanonicalBcp47LanguageTag(tag, bcp47Locale);
    uloc_canonicalize(tag, icuLocale, ULOC_FULLNAME_CAPACITY, &status);
  }

  if (bcp47LocaleLen) {
    locale->bcp47Locale = estrndup(bcp47Locale, bcp47LocaleLen);
    locale->bcp47LocaleLen = bcp47LocaleLen;

    setBaseName(&locale->std, icuLocale);
    setCalendar(&locale->std, icuLocale);
    setCalendars(&locale->std, icuLocale);
    setCaseFirst(&locale->std, icuLocale);
    setCollation(&locale->std, icuLocale);
    setHourCycle(&locale->std, icuLocale);
    setHourCycles(&locale->std, icuLocale);
    setLanguage(&locale->std, icuLocale);
    setNumberingSystem(&locale->std, icuLocale);
    setNumeric(&locale->std, icuLocale);
    setRegion(&locale->std, icuLocale);
    setScript(&locale->std, icuLocale);
  }

  efree(icuLocale);
  efree(bcp47Locale);
}

PHP_METHOD(Ecma_Intl_Locale, maximize) { ZEND_PARSE_PARAMETERS_NONE(); }

PHP_METHOD(Ecma_Intl_Locale, minimize) { ZEND_PARSE_PARAMETERS_NONE(); }

PHP_METHOD(Ecma_Intl_Locale, __toString) {
  ZEND_PARSE_PARAMETERS_NONE();

  zval *object = getThis();
  ecmaIntlLocaleObj *localeObj = Z_ECMA_LOCALE_P(object);

  RETURN_STRINGL(localeObj->bcp47Locale, localeObj->bcp47LocaleLen);
}

void ecmaIntlRegisterLocale() {
  ecmaIntlCeLocale = register_class_Ecma_Intl_Locale(zend_ce_stringable);
  ecmaIntlCeLocale->create_object = ecmaIntlLocaleObjCreate;

  memcpy(&ecmaIntlLocaleObjHandlers, &std_object_handlers,
         sizeof(zend_object_handlers));
  ecmaIntlLocaleObjHandlers.offset = XtOffsetOf(ecmaIntlLocaleObj, std);
  ecmaIntlLocaleObjHandlers.free_obj = ecmaIntlLocaleObjFree;
}
