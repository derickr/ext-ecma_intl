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
#include <php.h>
#include <unicode/localebuilder.h>
#include <unicode/locid.h>
#include <unicode/region.h>

#include "locale_builder_bridge.h"
#include "options.h"
#include "src/exceptions.h"

#ifdef __cplusplus
extern "C" {
#endif

#define OPTION_FAILURE (-1)
#define OPTION_NOOP 0
#define OPTION_SUCCESS 1

#define CASE_UPPER "upper"
#define CASE_LOWER "lower"
#define CASE_FALSE "false"

#define HOUR_H11 "h11"
#define HOUR_H12 "h12"
#define HOUR_H23 "h23"
#define HOUR_H24 "h24"

#define READ_PROPERTY(name) \
	zend_read_property(ecma_intl_ce_Locale_Options, &options->std, name, sizeof(name) - 1, false, nullptr)

#define CHECK_AND_SET_PROPERTY(property) \
	if (locale_set_##property(&builder, property) == OPTION_FAILURE) { \
        zend_throw_error(ecma_intl_ce_RangeError, "%s is not a well-formed %s value", #property, #property); \
        return false; \
	}

#define CHECK_AND_SET_PROPERTY_KEYWORD(property, key) \
	if (locale_set_keyword(&builder, key, property) == OPTION_FAILURE) { \
        zend_throw_error(ecma_intl_ce_RangeError, "%s is not a well-formed %s value", #property, #property); \
        return false; \
	}

#define CHECK_AND_SET_PROPERTY_KEYWORD_WITH_MESSAGE(property, key, error_message) \
	if (locale_set_keyword(&builder, key, property) == OPTION_FAILURE) { \
        zend_throw_error(ecma_intl_ce_RangeError, error_message); \
        return false; \
	}

#define CHECK_CASE_FIRST(value) \
	if (strcmp(value, CASE_UPPER) != 0 \
		&& strcmp(value, CASE_LOWER) != 0 \
		&& strcmp(value, CASE_FALSE) != 0 \
	) { \
        return OPTION_FAILURE; \
    }

#define CHECK_HOUR_CYCLE(value) \
	if (strcmp(value, HOUR_H11) != 0 \
		&& strcmp(value, HOUR_H12) != 0 \
		&& strcmp(value, HOUR_H23) != 0 \
		&& strcmp(value, HOUR_H24) != 0 \
	) { \
        return OPTION_FAILURE; \
    }

#define CHECK_NULL(option) if (ZVAL_IS_NULL(option)) return OPTION_NOOP;
#define CHECK_EMPTY(value) if (strcmp(value, "") == 0) return OPTION_FAILURE;
#define CHECK_FAILURE(status) if (U_FAILURE(status)) return OPTION_FAILURE;

static int locale_set_language(icu::LocaleBuilder *builder, zval *language);
static int locale_set_region(icu::LocaleBuilder *builder, zval *region);
static int locale_set_script(icu::LocaleBuilder *builder, zval *script);
static int locale_set_keyword(icu::LocaleBuilder *builder, const char *key, zval *value);

bool ecma_intl_build_locale(char *constructed_locale, const char *language_tag, ecma_intl_locale_options_obj *options)
{
	UErrorCode status = U_ZERO_ERROR;
	zval *calendar, *case_first, *collation, *hour_cycle, *language,
		*numbering_system, *numeric, *region, *script;
	icu::Locale locale, new_locale;
	icu::LocaleBuilder builder;

	locale = icu::Locale::forLanguageTag(language_tag, status);

	if (strcmp(language_tag, "") == 0 || U_FAILURE(status)) {
		zend_throw_error(ecma_intl_ce_RangeError,"invalid language tag");
		return false;
	}

	builder = icu::LocaleBuilder();
	builder.setLocale(locale);

	calendar = READ_PROPERTY(OPTIONS_PROP_CALENDAR);
	case_first = READ_PROPERTY(OPTIONS_PROP_CASE_FIRST);
	collation = READ_PROPERTY(OPTIONS_PROP_COLLATION);
	hour_cycle = READ_PROPERTY(OPTIONS_PROP_HOUR_CYCLE);
	language = READ_PROPERTY(OPTIONS_PROP_LANGUAGE);
	numbering_system = READ_PROPERTY(OPTIONS_PROP_NUMBERING_SYSTEM);
	numeric = READ_PROPERTY(OPTIONS_PROP_NUMERIC);
	region = READ_PROPERTY(OPTIONS_PROP_REGION);
	script = READ_PROPERTY(OPTIONS_PROP_SCRIPT);

	CHECK_AND_SET_PROPERTY_KEYWORD(calendar, "ca")
	CHECK_AND_SET_PROPERTY_KEYWORD_WITH_MESSAGE(case_first, "kf", "caseFirst must be either \"upper\", \"lower\", or \"false\"")
	CHECK_AND_SET_PROPERTY_KEYWORD(collation, "co")
	CHECK_AND_SET_PROPERTY_KEYWORD_WITH_MESSAGE(hour_cycle, "hc", "hourCycle must be \"h11\", \"h12\", \"h23\", or \"h24\"")
	CHECK_AND_SET_PROPERTY(language)
	CHECK_AND_SET_PROPERTY_KEYWORD_WITH_MESSAGE(numbering_system, "nu", "numberingSystem is not a well-formed numbering system value")
	CHECK_AND_SET_PROPERTY_KEYWORD(numeric, "kn")
	CHECK_AND_SET_PROPERTY(region)
	CHECK_AND_SET_PROPERTY(script)

	new_locale = builder.build(status);

	if (U_FAILURE(status)) {
		zend_throw_error(ecma_intl_ce_IcuException,"%s", u_errorName(status));
		return false;
	}

	std::string constructed = new_locale.toLanguageTag<std::string>(status);

	if (U_FAILURE(status)) {
		zend_throw_error(ecma_intl_ce_IcuException,"%s", u_errorName(status));
		return false;
	}

	std::memcpy(constructed_locale, constructed.c_str(), constructed.size() + 1);

	return true;
}

int locale_set_language(icu::LocaleBuilder *builder, zval *language)
{
	CHECK_NULL(language)
	CHECK_EMPTY(Z_STRVAL_P(language))

	UErrorCode status = U_ZERO_ERROR;
	icu::Locale locale = icu::LocaleBuilder().setLanguage(Z_STRVAL_P(language)).build(status);

	CHECK_FAILURE(status)

	builder->setLanguage(locale.getLanguage());

	return OPTION_SUCCESS;
}

int locale_set_region(icu::LocaleBuilder *builder, zval *region)
{
	CHECK_NULL(region)
	CHECK_EMPTY(Z_STRVAL_P(region))

	UErrorCode status = U_ZERO_ERROR;
	const icu::Region *region_obj = icu::Region::getInstance(Z_STRVAL_P(region), status);

	CHECK_FAILURE(status)

	builder->setRegion(region_obj->getRegionCode());

	return OPTION_SUCCESS;
}

int locale_set_script(icu::LocaleBuilder *builder, zval *script)
{
	CHECK_NULL(script)
	CHECK_EMPTY(Z_STRVAL_P(script))

	UErrorCode status = U_ZERO_ERROR;
	icu::Locale locale = icu::LocaleBuilder().setScript(Z_STRVAL_P(script)).build(status);

	CHECK_FAILURE(status)

	builder->setScript(locale.getScript());

	return OPTION_SUCCESS;
}

int locale_set_keyword(icu::LocaleBuilder *builder, const char *key, zval *value)
{
	CHECK_NULL(value)

	const char *value_str;

	if (Z_TYPE_P(value) == IS_TRUE || Z_TYPE_P(value) == IS_FALSE) {
		value_str = Z_TYPE_P(value) == IS_TRUE ? "true" : "false";
	} else {
		value_str = Z_STRVAL_P(value);
	}

	CHECK_EMPTY(value_str)

	if (strcmp(key, "kf") == 0) {
		CHECK_CASE_FIRST(value_str)
	}

	if (strcmp(key, "hc") == 0) {
		CHECK_HOUR_CYCLE(value_str)
	}

	UErrorCode status = U_ZERO_ERROR;
	icu::Locale locale = icu::LocaleBuilder()
		.setLanguageTag("und")
		.setUnicodeLocaleKeyword(key, value_str)
		.build(status);

	CHECK_FAILURE(status)

	builder->setUnicodeLocaleKeyword(
		key,
		locale.getUnicodeKeywordValue<std::string>(key, status)
	);

	return OPTION_SUCCESS;
}

#ifdef __cplusplus
}
#endif