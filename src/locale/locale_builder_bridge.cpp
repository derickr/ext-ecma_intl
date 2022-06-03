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

#include <cstring>
#include <unicode/localebuilder.h>
#include <unicode/locid.h>
#include <unicode/region.h>

#include "locale_builder_bridge.h"

#ifdef __cplusplus
extern "C" {
#endif

#define READ_PROPERTY(name)                                                    \
  zend_read_property(ecmaIntlCeLocaleOptions, &options->std, name,             \
                     sizeof(name) - 1, false, nullptr)

#define CHECK_AND_SET_PROPERTY(functionPart, property)                         \
  if (localeSet##functionPart(&builder, property) == ECMA_INTL_FAILURE) {      \
    zend_throw_error(ecmaIntlCeRangeError, "%s is not a well-formed %s value", \
                     #property, #property);                                    \
    return false;                                                              \
  }

#define CHECK_AND_SET_PROPERTY_KEYWORD(property, key)                          \
  if (localeSetKeyword(&builder, key, property) == ECMA_INTL_FAILURE) {        \
    zend_throw_error(ecmaIntlCeRangeError, "%s is not a well-formed %s value", \
                     #property, #property);                                    \
    return false;                                                              \
  }

#define CHECK_AND_SET_PROPERTY_KEYWORD_WITH_MESSAGE(property, key,             \
                                                    error_message)             \
  if (localeSetKeyword(&builder, key, property) == ECMA_INTL_FAILURE) {        \
    zend_throw_error(ecmaIntlCeRangeError, error_message);                     \
    return false;                                                              \
  }

#define CHECK_CASE_FIRST(value)                                                \
  if (strcmp(value, CASE_FIRST_UPPER) != 0 &&                                  \
      strcmp(value, CASE_FIRST_LOWER) != 0 &&                                  \
      strcmp(value, CASE_FIRST_FALSE) != 0) {                                  \
    return ECMA_INTL_FAILURE;                                                  \
  }

#define CHECK_HOUR_CYCLE(value)                                                \
  if (strcmp(value, HOUR_H11) != 0 && strcmp(value, HOUR_H12) != 0 &&          \
      strcmp(value, HOUR_H23) != 0 && strcmp(value, HOUR_H24) != 0) {          \
    return ECMA_INTL_FAILURE;                                                  \
  }

#define CHECK_NULL(option)                                                     \
  if (ZVAL_IS_NULL(option))                                                    \
    return ECMA_INTL_NOOP;
#define CHECK_EMPTY(value)                                                     \
  if (strcmp(value, "") == 0)                                                  \
    return ECMA_INTL_FAILURE;
#define CHECK_FAILURE(status)                                                  \
  if (U_FAILURE(status))                                                       \
    return ECMA_INTL_FAILURE;

static int localeSetLanguage(icu::LocaleBuilder *builder, zval *language);
static int localeSetRegion(icu::LocaleBuilder *builder, zval *region);
static int localeSetScript(icu::LocaleBuilder *builder, zval *script);
static int localeSetKeyword(icu::LocaleBuilder *builder, const char *key,
                            zval *value);

bool ecmaIntlBuildLocale(char *constructedLocale, const char *languageTag,
                         ecmaIntlLocaleOptionsObj *options) {
  UErrorCode status = U_ZERO_ERROR;
  zval *calendar, *caseFirst, *collation, *hourCycle, *language,
      *numberingSystem, *numeric, *region, *script;
  icu::Locale locale, newLocale;
  icu::LocaleBuilder builder;

  locale = icu::Locale::forLanguageTag(languageTag, status);

  if (strcmp(languageTag, "") == 0 || U_FAILURE(status)) {
    zend_throw_error(ecmaIntlCeRangeError, "invalid language tag");
    return false;
  }

  builder = icu::LocaleBuilder();
  builder.setLocale(locale);

  calendar = READ_PROPERTY(PROPERTY_CALENDAR);
  caseFirst = READ_PROPERTY(PROPERTY_CASE_FIRST);
  collation = READ_PROPERTY(PROPERTY_COLLATION);
  hourCycle = READ_PROPERTY(PROPERTY_HOUR_CYCLE);
  language = READ_PROPERTY(PROPERTY_LANGUAGE);
  numberingSystem = READ_PROPERTY(PROPERTY_NUMBERING_SYSTEM);
  numeric = READ_PROPERTY(PROPERTY_NUMERIC);
  region = READ_PROPERTY(PROPERTY_REGION);
  script = READ_PROPERTY(PROPERTY_SCRIPT);

  CHECK_AND_SET_PROPERTY_KEYWORD(calendar, KEYWORD_BCP_47_CALENDAR)
  CHECK_AND_SET_PROPERTY_KEYWORD_WITH_MESSAGE(
      caseFirst, KEYWORD_BCP_47_CASE_FIRST,
      "caseFirst must be either \"upper\", \"lower\", or \"false\"")
  CHECK_AND_SET_PROPERTY_KEYWORD(collation, KEYWORD_BCP_47_COLLATION)
  CHECK_AND_SET_PROPERTY_KEYWORD_WITH_MESSAGE(
      hourCycle, KEYWORD_BCP_47_HOUR_CYCLE,
      "hourCycle must be \"h11\", \"h12\", \"h23\", or \"h24\"")
  CHECK_AND_SET_PROPERTY(Language, language)
  CHECK_AND_SET_PROPERTY_KEYWORD_WITH_MESSAGE(
      numberingSystem, KEYWORD_BCP_47_NUMBERING_SYSTEM,
      "numberingSystem is not a well-formed numbering system value")
  CHECK_AND_SET_PROPERTY_KEYWORD(numeric, KEYWORD_BCP_47_NUMERIC)
  CHECK_AND_SET_PROPERTY(Region, region)
  CHECK_AND_SET_PROPERTY(Script, script)

  newLocale = builder.build(status);

  if (U_FAILURE(status)) {
    zend_throw_error(ecmaIntlCeIcuException, "%s", u_errorName(status));
    return false;
  }

  std::string constructed = newLocale.toLanguageTag<std::string>(status);

  if (U_FAILURE(status)) {
    zend_throw_error(ecmaIntlCeIcuException, "%s", u_errorName(status));
    return false;
  }

  std::memcpy(constructedLocale, constructed.c_str(), constructed.size() + 1);

  return true;
}

int localeSetLanguage(icu::LocaleBuilder *builder, zval *language) {
  CHECK_NULL(language)
  CHECK_EMPTY(Z_STRVAL_P(language))

  UErrorCode status = U_ZERO_ERROR;
  icu::Locale locale =
      icu::LocaleBuilder().setLanguage(Z_STRVAL_P(language)).build(status);

  CHECK_FAILURE(status)

  builder->setLanguage(locale.getLanguage());

  return ECMA_INTL_SUCCESS;
}

int localeSetRegion(icu::LocaleBuilder *builder, zval *region) {
  CHECK_NULL(region)
  CHECK_EMPTY(Z_STRVAL_P(region))

  UErrorCode status = U_ZERO_ERROR;
  const icu::Region *regionObj =
      icu::Region::getInstance(Z_STRVAL_P(region), status);

  CHECK_FAILURE(status)

  builder->setRegion(regionObj->getRegionCode());

  return ECMA_INTL_SUCCESS;
}

int localeSetScript(icu::LocaleBuilder *builder, zval *script) {
  CHECK_NULL(script)
  CHECK_EMPTY(Z_STRVAL_P(script))

  UErrorCode status = U_ZERO_ERROR;
  icu::Locale locale =
      icu::LocaleBuilder().setScript(Z_STRVAL_P(script)).build(status);

  CHECK_FAILURE(status)

  builder->setScript(locale.getScript());

  return ECMA_INTL_SUCCESS;
}

int localeSetKeyword(icu::LocaleBuilder *builder, const char *key,
                     zval *value) {
  CHECK_NULL(value)

  const char *valueStr;

  if (Z_TYPE_P(value) == IS_TRUE || Z_TYPE_P(value) == IS_FALSE) {
    valueStr = Z_TYPE_P(value) == IS_TRUE ? NUMERIC_YES : NUMERIC_NO;
  } else {
    valueStr = Z_STRVAL_P(value);
  }

  CHECK_EMPTY(valueStr)

  if (strcmp(key, KEYWORD_BCP_47_CASE_FIRST) == 0) {
    CHECK_CASE_FIRST(valueStr)
  }

  if (strcmp(key, KEYWORD_BCP_47_HOUR_CYCLE) == 0) {
    CHECK_HOUR_CYCLE(valueStr)
  }

  UErrorCode status = U_ZERO_ERROR;
  icu::Locale locale = icu::LocaleBuilder()
                           .setLanguageTag(LANGUAGE_UNDETERMINED)
                           .setUnicodeLocaleKeyword(key, valueStr)
                           .build(status);

  CHECK_FAILURE(status)

  builder->setUnicodeLocaleKeyword(
      key, locale.getUnicodeKeywordValue<std::string>(key, status));

  return ECMA_INTL_SUCCESS;
}

#ifdef __cplusplus
}
#endif
