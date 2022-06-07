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
#include "php_locale_week_info.h"
#include "src/php/classes/php_exceptions_ce.h"
#include "src/php/classes/php_locale_ce.h"
#include "src/php/classes/php_locale_text_direction_ce.h"
#include "src/php/classes/php_locale_text_info_ce.h"
#include "src/php/classes/php_locale_week_day_ce.h"
#include "src/php/classes/php_locale_week_info_ce.h"
#include "src/php/handlers/php_locale_handlers.h"
#include "src/php/objects/php_locale_text_info.h"
#include "src/unicode/bcp47.h"
#include "src/unicode/calendar.h"

#include <unicode/ucal.h>
#include <unicode/ucol.h>
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

#define CHECK_ERROR(status)                                                    \
  if (U_FAILURE(status)) {                                                     \
    zend_throw_error(ecmaIntlClassIcuException, "%s", u_errorName(status));    \
  }

static zend_object *getWeekDayCaseForDayOfWeek(UCalendarDaysOfWeek dayOfWeek);

zend_object *ecmaIntlLocaleObjCreate(zend_class_entry *classType) {
  ecmaIntlLocaleObj *localeObj;

  localeObj = zend_object_alloc(sizeof(ecmaIntlLocaleObj), classType);
  localeObj->bcp47Locale = NULL;

  zend_object_std_init(&localeObj->std, classType);
  object_properties_init(&localeObj->std, classType);

  localeObj->std.handlers = &ecmaIntlLocaleObjHandlers;

  return &localeObj->std;
}

void localeInit(ecmaIntlLocaleObj *locale, char *languageTag) {
  char *bcp47Locale = NULL, *icuLocale = NULL;
  size_t bcp47LocaleLen = 0;
  UErrorCode status = U_ZERO_ERROR;

  bcp47Locale = (char *)ecalloc(1, sizeof(char *) * ULOC_FULLNAME_CAPACITY);
  icuLocale = (char *)ecalloc(1, sizeof(char *) * ULOC_FULLNAME_CAPACITY);

  bcp47LocaleLen = icuToBcp47LanguageTag(languageTag, bcp47Locale);
  uloc_canonicalize(languageTag, icuLocale, ULOC_FULLNAME_CAPACITY, &status);

  CHECK_ERROR(status) else if (bcp47LocaleLen) {
    locale->bcp47Locale = estrndup(bcp47Locale, bcp47LocaleLen);
    locale->bcp47LocaleLen = bcp47LocaleLen;

    localeSetBaseName(&locale->std, icuLocale);
    localeSetCalendar(&locale->std, icuLocale);
    localeSetCalendars(&locale->std, icuLocale);
    localeSetCaseFirst(&locale->std, icuLocale);
    localeSetCollation(&locale->std, icuLocale);
    localeSetCollations(&locale->std, icuLocale);
    localeSetHourCycle(&locale->std, icuLocale);
    localeSetHourCycles(&locale->std, icuLocale);
    localeSetLanguage(&locale->std, icuLocale);
    localeSetNumberingSystem(&locale->std, icuLocale);
    localeSetNumberingSystems(&locale->std, icuLocale);
    localeSetNumeric(&locale->std, icuLocale);
    localeSetRegion(&locale->std, icuLocale);
    localeSetScript(&locale->std, icuLocale);
    localeSetTextInfo(&locale->std, icuLocale);
    localeSetTimeZones(&locale->std, icuLocale);
    localeSetWeekInfo(&locale->std, icuLocale);
  }

  efree(icuLocale);
  efree(bcp47Locale);
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

  value = (char *)emalloc(sizeof(char *) * ULOC_KEYWORD_AND_VALUES_CAPACITY);
  valueLen = uloc_getKeywordValue(localeId, KEYWORD_ICU_CALENDAR, value,
                                  ULOC_KEYWORD_AND_VALUES_CAPACITY, &status);

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
  char *preferred;
  const char *calendar;
  int preferredLen, calendarLen;
  zval calendars;

  array_init(&calendars);

  preferred =
      (char *)emalloc(sizeof(char *) * ULOC_KEYWORD_AND_VALUES_CAPACITY);
  preferredLen =
      uloc_getKeywordValue(localeId, KEYWORD_ICU_CALENDAR, preferred,
                           ULOC_KEYWORD_AND_VALUES_CAPACITY, &status);

  CHECK_ERROR(status) else if (preferredLen > 0) {
    add_next_index_string(
        &calendars, uloc_toUnicodeLocaleType(KEYWORD_ICU_CALENDAR, preferred));
  }
  else {
    values = ucal_getKeywordValuesForLocale(KEYWORD_ICU_CALENDAR, localeId, 1,
                                            &status);

    CHECK_ERROR(status) else {
      while ((calendar = uenum_next(values, &calendarLen, &status)) &&
             U_SUCCESS(status)) {
        add_next_index_string(&calendars, uloc_toUnicodeLocaleType(
                                              KEYWORD_ICU_CALENDAR, calendar));
      }

      CHECK_ERROR(status)
    }

    uenum_close(values);
  }

  zend_update_property(ecmaIntlClassLocale, object, PROPERTY_CALENDARS,
                       sizeof(PROPERTY_CALENDARS) - 1, &calendars);

  efree(preferred);
  zend_array_release(Z_ARRVAL(calendars));
}

void localeSetCaseFirst(zend_object *object, char *localeId) {
  char *value = NULL;
  int valueLen;
  UErrorCode status = U_ZERO_ERROR;

  value = (char *)ecalloc(1, sizeof(char *) * ULOC_KEYWORD_AND_VALUES_CAPACITY);
  valueLen = uloc_getKeywordValue(localeId, KEYWORD_ICU_CASE_FIRST, value,
                                  ULOC_KEYWORD_AND_VALUES_CAPACITY, &status);

  SET_PROPERTY(PROPERTY_CASE_FIRST)

  efree(value);
}

void localeSetCollation(zend_object *object, char *localeId) {
  char *value = NULL;
  int valueLen;
  UErrorCode status = U_ZERO_ERROR;

  value = (char *)ecalloc(1, sizeof(char *) * ULOC_KEYWORD_AND_VALUES_CAPACITY);
  valueLen = uloc_getKeywordValue(localeId, KEYWORD_ICU_COLLATION, value,
                                  ULOC_KEYWORD_AND_VALUES_CAPACITY, &status);

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

void localeSetCollations(zend_object *object, char *localeId) {
  UEnumeration *values = NULL;
  UErrorCode status = U_ZERO_ERROR;
  char *preferred;
  const char *collation;
  int preferredLen, collationLen;
  zval collations;

  array_init(&collations);

  preferred =
      (char *)emalloc(sizeof(char *) * ULOC_KEYWORD_AND_VALUES_CAPACITY);
  preferredLen =
      uloc_getKeywordValue(localeId, KEYWORD_ICU_COLLATION, preferred,
                           ULOC_KEYWORD_AND_VALUES_CAPACITY, &status);

  CHECK_ERROR(status) else if (preferredLen > 0) {
    add_next_index_string(&collations, uloc_toUnicodeLocaleType(
                                           KEYWORD_ICU_COLLATION, preferred));
  }
  else {
    values = ucol_getKeywordValuesForLocale(KEYWORD_ICU_COLLATION, localeId, 1,
                                            &status);

    CHECK_ERROR(status) else {
      while ((collation = uenum_next(values, &collationLen, &status)) &&
             U_SUCCESS(status)) {
        /* 1.1.3 step 4, The values "standard" and "search" must be excluded
         * from list. */
        if (strcmp(collation, "standard") == 0 ||
            strcmp(collation, "search") == 0) {
          continue;
        }

        add_next_index_string(
            &collations,
            uloc_toUnicodeLocaleType(KEYWORD_ICU_COLLATION, collation));
      }

      CHECK_ERROR(status)
    }

    uenum_close(values);
  }

  zend_update_property(ecmaIntlClassLocale, object, PROPERTY_COLLATIONS,
                       sizeof(PROPERTY_COLLATIONS) - 1, &collations);

  efree(preferred);
  zend_array_release(Z_ARRVAL(collations));
}

void localeSetHourCycle(zend_object *object, char *localeId) {
  char *value = NULL;
  int valueLen;
  UErrorCode status = U_ZERO_ERROR;

  value = (char *)ecalloc(1, sizeof(char *) * ULOC_KEYWORD_AND_VALUES_CAPACITY);
  valueLen = uloc_getKeywordValue(localeId, KEYWORD_ICU_HOUR_CYCLE, value,
                                  ULOC_KEYWORD_AND_VALUES_CAPACITY, &status);

  SET_PROPERTY(PROPERTY_HOUR_CYCLE)

  efree(value);
}

void localeSetHourCycles(zend_object *object, char *localeId) {
  UDateTimePatternGenerator *patternGenerator;
  UDateFormatHourCycle hourCycle;
  UErrorCode status = U_ZERO_ERROR;
  zval hourCycles;
  char *preferred;
  int preferredLen;

  array_init(&hourCycles);

  preferred =
      (char *)emalloc(sizeof(char *) * ULOC_KEYWORD_AND_VALUES_CAPACITY);
  preferredLen =
      uloc_getKeywordValue(localeId, KEYWORD_ICU_HOUR_CYCLE, preferred,
                           ULOC_KEYWORD_AND_VALUES_CAPACITY, &status);

  CHECK_ERROR(status) else if (preferredLen > 0) {
    add_next_index_string(&hourCycles, preferred);
  }
  else {
    patternGenerator = udatpg_open(localeId, &status);

    CHECK_ERROR(status) else {
      hourCycle = udatpg_getDefaultHourCycle(patternGenerator, &status);

      CHECK_ERROR(status) else {
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
    }

    udatpg_close(patternGenerator);
  }

  zend_update_property(ecmaIntlClassLocale, object, PROPERTY_HOUR_CYCLES,
                       sizeof(PROPERTY_HOUR_CYCLES) - 1, &hourCycles);

  efree(preferred);
  zend_array_release(Z_ARRVAL(hourCycles));
}

void localeSetLanguage(zend_object *object, char *localeId) {
  char *value = NULL;
  int valueLen;
  UErrorCode status = U_ZERO_ERROR;

  value = (char *)ecalloc(1, sizeof(char *) * ULOC_LANG_CAPACITY);
  valueLen = uloc_getLanguage(localeId, value, ULOC_LANG_CAPACITY, &status);

  SET_PROPERTY(PROPERTY_LANGUAGE)

  efree(value);
}

void localeSetNumberingSystem(zend_object *object, char *localeId) {
  char *value = NULL;
  int valueLen;
  UErrorCode status = U_ZERO_ERROR;

  value = (char *)ecalloc(1, sizeof(char *) * ULOC_KEYWORD_AND_VALUES_CAPACITY);
  valueLen = uloc_getKeywordValue(localeId, KEYWORD_ICU_NUMBERING_SYSTEM, value,
                                  ULOC_KEYWORD_AND_VALUES_CAPACITY, &status);

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
  char *preferred;
  int preferredLen;

  array_init_size(&numberingSystems, 1);

  preferred =
      (char *)emalloc(sizeof(char *) * ULOC_KEYWORD_AND_VALUES_CAPACITY);
  preferredLen =
      uloc_getKeywordValue(localeId, KEYWORD_ICU_NUMBERING_SYSTEM, preferred,
                           ULOC_KEYWORD_AND_VALUES_CAPACITY, &status);

  CHECK_ERROR(status) else if (preferredLen > 0) {
    add_next_index_string(
        &numberingSystems,
        uloc_toUnicodeLocaleType(KEYWORD_ICU_NUMBERING_SYSTEM, preferred));
  }
  else {
    numberingSystem = unumsys_open(localeId, &status);

    CHECK_ERROR(status) else {
      add_next_index_string(
          &numberingSystems,
          uloc_toUnicodeLocaleType(KEYWORD_ICU_NUMBERING_SYSTEM,
                                   unumsys_getName(numberingSystem)));
    }

    unumsys_close(numberingSystem);
  }

  zend_update_property(ecmaIntlClassLocale, object, PROPERTY_NUMBERING_SYSTEMS,
                       sizeof(PROPERTY_NUMBERING_SYSTEMS) - 1,
                       &numberingSystems);

  efree(preferred);
  zend_array_release(Z_ARRVAL(numberingSystems));
}

void localeSetNumeric(zend_object *object, char *localeId) {
  char *value = NULL;
  UErrorCode status = U_ZERO_ERROR;

  value = (char *)ecalloc(1, sizeof(char *) * ULOC_KEYWORD_AND_VALUES_CAPACITY);
  uloc_getKeywordValue(localeId, KEYWORD_ICU_NUMERIC, value,
                       ULOC_KEYWORD_AND_VALUES_CAPACITY, &status);

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

  value = (char *)ecalloc(1, sizeof(char *) * ULOC_COUNTRY_CAPACITY);
  valueLen = uloc_getCountry(localeId, value, ULOC_COUNTRY_CAPACITY, &status);

  SET_PROPERTY(PROPERTY_REGION)

  efree(value);
}

void localeSetScript(zend_object *object, char *localeId) {
  char *value = NULL;
  int valueLen;
  UErrorCode status = U_ZERO_ERROR;

  value = (char *)ecalloc(1, sizeof(char *) * ULOC_SCRIPT_CAPACITY);
  valueLen = uloc_getScript(localeId, value, ULOC_SCRIPT_CAPACITY, &status);

  SET_PROPERTY(PROPERTY_SCRIPT)

  efree(value);
}

void localeSetTextInfo(zend_object *object, char *localeId) {
  ULayoutType layout;
  UErrorCode status = U_ZERO_ERROR;
  zend_object *textInfoObj, *textDirectionCase = NULL;
  zval textInfo, textDirection;

  layout = uloc_getCharacterOrientation(localeId, &status);

  CHECK_ERROR(status) else {
    switch (layout) {
    case ULOC_LAYOUT_BTT:
      textDirectionCase = zend_enum_get_case_cstr(
          ecmaIntlEnumLocaleTextDirection, TEXT_DIRECTION_CASE_BTT);
      break;
    case ULOC_LAYOUT_LTR:
      textDirectionCase = zend_enum_get_case_cstr(
          ecmaIntlEnumLocaleTextDirection, TEXT_DIRECTION_CASE_LTR);
      break;
    case ULOC_LAYOUT_RTL:
      textDirectionCase = zend_enum_get_case_cstr(
          ecmaIntlEnumLocaleTextDirection, TEXT_DIRECTION_CASE_RTL);
      break;
    case ULOC_LAYOUT_TTB:
      textDirectionCase = zend_enum_get_case_cstr(
          ecmaIntlEnumLocaleTextDirection, TEXT_DIRECTION_CASE_TTB);
      break;
    case ULOC_LAYOUT_UNKNOWN:
    default:
      /* do nothing */
      break;
    }
  }

  if (textDirectionCase) {
    textInfoObj = ecmaIntlLocaleTextInfoObjCreate(ecmaIntlClassLocaleTextInfo);

    ZVAL_OBJ(&textDirection, textDirectionCase);
    zend_update_property(ecmaIntlClassLocaleTextInfo, textInfoObj,
                         PROPERTY_DIRECTION, sizeof(PROPERTY_DIRECTION) - 1,
                         &textDirection);

    ZVAL_OBJ(&textInfo, textInfoObj);
    zend_update_property(ecmaIntlClassLocale, object, PROPERTY_TEXT_INFO,
                         sizeof(PROPERTY_TEXT_INFO) - 1, &textInfo);

    zend_object_release(textInfoObj);
  } else {
    zend_update_property_null(ecmaIntlClassLocale, object, PROPERTY_TEXT_INFO,
                              sizeof(PROPERTY_TEXT_INFO) - 1);
  }
}

void localeSetTimeZones(zend_object *object, char *localeId) {
  char *region = NULL;
  const char *timeZone;
  int regionLen = 0, timeZoneLen, count;
  UErrorCode status = U_ZERO_ERROR;
  UEnumeration *values = NULL;
  zval timeZones;

  region = (char *)ecalloc(1, sizeof(char *) * ULOC_COUNTRY_CAPACITY);
  regionLen = uloc_getCountry(localeId, region, ULOC_COUNTRY_CAPACITY, &status);

  CHECK_ERROR(status) else if (regionLen > 0) {
    values = ucal_openTimeZoneIDEnumeration(UCAL_ZONE_TYPE_CANONICAL, region,
                                            NULL, &status);

    CHECK_ERROR(status) else {
      count = uenum_count(values, &status);
      uenum_reset(values, &status);

      array_init_size(&timeZones, count);

      while ((timeZone = uenum_next(values, &timeZoneLen, &status)) &&
             U_SUCCESS(status)) {
        add_next_index_stringl(&timeZones, timeZone, timeZoneLen);
      }

      CHECK_ERROR(status)

      zend_update_property(ecmaIntlClassLocale, object, PROPERTY_TIME_ZONES,
                           sizeof(PROPERTY_TIME_ZONES) - 1, &timeZones);

      zend_array_release(Z_ARRVAL(timeZones));
    }
  }

  if (regionLen == 0) {
    zend_update_property_null(ecmaIntlClassLocale, object, PROPERTY_TIME_ZONES,
                              sizeof(PROPERTY_TIME_ZONES) - 1);
  }

  efree(region);
}

void localeSetWeekInfo(zend_object *object, char *localeId) {
  UCalendar *calendar;
  UErrorCode status = U_ZERO_ERROR;
  zend_object *weekInfoObj, *firstDayOfWeekCase, *weekendDayCase;
  zval weekInfo, firstDayOfWeek, weekend, weekendDay;

  calendar = ucal_open(NULL, 0, localeId, UCAL_DEFAULT, &status);

  CHECK_ERROR(status) else if (calendar) {
    weekInfoObj = ecmaIntlLocaleWeekInfoObjCreate(ecmaIntlClassLocaleWeekInfo);
    ZVAL_OBJ(&weekInfo, weekInfoObj);

    firstDayOfWeekCase = getWeekDayCaseForDayOfWeek(
        ucal_getAttribute(calendar, UCAL_FIRST_DAY_OF_WEEK));
    ZVAL_OBJ(&firstDayOfWeek, firstDayOfWeekCase);

    zend_update_property(ecmaIntlClassLocaleWeekInfo, weekInfoObj,
                         PROPERTY_FIRST_DAY, sizeof(PROPERTY_FIRST_DAY) - 1,
                         &firstDayOfWeek);

    zend_update_property_long(
        ecmaIntlClassLocaleWeekInfo, weekInfoObj, PROPERTY_MINIMAL_DAYS,
        sizeof(PROPERTY_MINIMAL_DAYS) - 1,
        ucal_getAttribute(calendar, UCAL_MINIMAL_DAYS_IN_FIRST_WEEK));

    array_init(&weekend);
    for (int day = UCAL_MONDAY; day <= (UCAL_SATURDAY + 1); ++day) {
      /* This is a bit of a hack to force Sunday to come last, since this array
       * should be ordered in ascending order, and ECMA-402 defines weekday
       * values as integers 1 (Monday) - 7 (Sunday), while Unicode starts with
       * Sunday. See Table 1 in section 1.1.8 of the Intl Locale Info Proposal.
       */
      int currentDay = day;
      if (day > UCAL_SATURDAY) {
        currentDay = UCAL_SUNDAY;
      }

      UCalendarWeekdayType type =
          getCanonicalDayOfWeekType(calendar, currentDay);
      switch (type) {
      case UCAL_WEEKDAY:
        break;
      case UCAL_WEEKEND:
        weekendDayCase = getWeekDayCaseForDayOfWeek(currentDay);
        ZVAL_OBJ_COPY(&weekendDay, weekendDayCase);
        add_next_index_zval(&weekend, &weekendDay);
        break;
      default:
        break;
      }
    }

    zend_update_property(ecmaIntlClassLocaleWeekInfo, weekInfoObj,
                         PROPERTY_WEEKEND, sizeof(PROPERTY_WEEKEND) - 1,
                         &weekend);

    zend_update_property(ecmaIntlClassLocale, object, PROPERTY_WEEK_INFO,
                         sizeof(PROPERTY_WEEK_INFO) - 1, &weekInfo);

    zend_array_release(Z_ARRVAL(weekend));
    zend_object_release(weekInfoObj);
  }
  else {
    zend_update_property_null(ecmaIntlClassLocale, object, PROPERTY_WEEK_INFO,
                              sizeof(PROPERTY_WEEK_INFO) - 1);
  }
}

static zend_object *getWeekDayCaseForDayOfWeek(UCalendarDaysOfWeek dayOfWeek) {
  switch (dayOfWeek) {
  case UCAL_MONDAY:
    return zend_enum_get_case_cstr(ecmaIntlEnumLocaleWeekDay,
                                   WEEK_DAY_CASE_MONDAY);
  case UCAL_TUESDAY:
    return zend_enum_get_case_cstr(ecmaIntlEnumLocaleWeekDay,
                                   WEEK_DAY_CASE_TUESDAY);
  case UCAL_WEDNESDAY:
    return zend_enum_get_case_cstr(ecmaIntlEnumLocaleWeekDay,
                                   WEEK_DAY_CASE_WEDNESDAY);
  case UCAL_THURSDAY:
    return zend_enum_get_case_cstr(ecmaIntlEnumLocaleWeekDay,
                                   WEEK_DAY_CASE_THURSDAY);
  case UCAL_FRIDAY:
    return zend_enum_get_case_cstr(ecmaIntlEnumLocaleWeekDay,
                                   WEEK_DAY_CASE_FRIDAY);
  case UCAL_SATURDAY:
    return zend_enum_get_case_cstr(ecmaIntlEnumLocaleWeekDay,
                                   WEEK_DAY_CASE_SATURDAY);
  case UCAL_SUNDAY:
    return zend_enum_get_case_cstr(ecmaIntlEnumLocaleWeekDay,
                                   WEEK_DAY_CASE_SUNDAY);
  default:
    return NULL;
  }
}
