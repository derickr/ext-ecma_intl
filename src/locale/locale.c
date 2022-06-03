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
#include <unicode/uloc.h>
#include <zend_interfaces.h>

#include "../common.h"
#include "locale.h"
#include "locale_arginfo.h"
#include "locale_builder_bridge.h"
#include "options.h"
#include "src/exceptions.h"
#include "src/functions.h"

#define SET_PROPERTY(name) \
	if (value_len == 0) {     \
		zend_update_property_null(ecma_intl_ce_Locale, object, name, sizeof(name) - 1); \
	} else { \
		zend_update_property_stringl(ecma_intl_ce_Locale, object, name, sizeof(name) - 1, value, value_len); \
	}

zend_class_entry *ecma_intl_ce_Locale = NULL;

static zend_object_handlers ecma_intl_locale_obj_handlers;
static zend_object *ecma_intl_locale_obj_create(zend_class_entry *class_type);
static void ecma_intl_locale_obj_free(zend_object *object);

static void set_base_name(zend_object *object, char *locale_id);
static void set_calendar(zend_object *object, char *locale_id);
static void set_calendars(zend_object *object, char *locale_id);
static void set_case_first(zend_object *object, char *locale_id);
static void set_collation(zend_object *object, char *locale_id);
static void set_hour_cycle(zend_object *object, char *locale_id);
static void set_language(zend_object *object, char *locale_id);
static void set_numbering_system(zend_object *object, char *locale_id);
static void set_numeric(zend_object *object, char *locale_id);
static void set_region(zend_object *object, char *locale_id);
static void set_script(zend_object *object, char *locale_id);

static zend_object *ecma_intl_locale_obj_create(zend_class_entry *class_type)
{
	ecma_intl_locale_obj *locale_obj;

	locale_obj = zend_object_alloc(sizeof(ecma_intl_locale_obj), class_type);
	locale_obj->bcp47_locale = NULL;

	zend_object_std_init(&locale_obj->std, class_type);
	object_properties_init(&locale_obj->std, class_type);

	locale_obj->std.handlers = &ecma_intl_locale_obj_handlers;

	return &locale_obj->std;
}

static void ecma_intl_locale_obj_free(zend_object *object)
{
	ecma_intl_locale_obj *locale_obj = ecma_intl_locale_obj_from_obj(object);

	zend_object_std_dtor(&locale_obj->std);

	if (locale_obj->bcp47_locale) {
		efree(locale_obj->bcp47_locale);
		locale_obj->bcp47_locale = NULL;
	}
}

static void set_base_name(zend_object *object, char *locale_id)
{
	char *base_name = NULL, *value = NULL;
	int value_len = 0;
	UErrorCode status = U_ZERO_ERROR;

	base_name = (char *) ecalloc(1, sizeof(char *) * ULOC_FULLNAME_CAPACITY);
	uloc_getBaseName(locale_id, base_name, ULOC_FULLNAME_CAPACITY, &status);

	// The base name is in ICU format, so we need to convert it to BCP 47 format.
	value = (char *) ecalloc(1, sizeof(char *) * ULOC_FULLNAME_CAPACITY);
	value_len = ecma_intl_toCanonicalBcp47LanguageTag(base_name, value);

	SET_PROPERTY(PROPERTY_BASE_NAME)

	efree(base_name);
	efree(value);
}

static void set_calendar(zend_object *object, char *locale_id)
{
	char *value = NULL;
	int value_len = 0;
	UErrorCode status = U_ZERO_ERROR;

	value = (char *) emalloc(sizeof(char *) * ULOC_FULLNAME_CAPACITY);
	value_len = uloc_getKeywordValue(locale_id, KEYWORD_ICU_CALENDAR, value, ULOC_FULLNAME_CAPACITY, &status);

	SET_PROPERTY(PROPERTY_CALENDAR)

	efree(value);
}

static void set_calendars(zend_object *object, char *locale_id)
{
	UEnumeration *values = NULL;
	UErrorCode status = U_ZERO_ERROR;
	int count, length, i;
	const char *identifier;
	zval calendars;

	values = ucal_getKeywordValuesForLocale(KEYWORD_ICU_CALENDAR, locale_id, 1, &status);

	if (U_FAILURE(status)) {
		zend_throw_error(ecma_intl_ce_IcuException,"%s", u_errorName(status));
	} else {
		count = uenum_count(values, &status);
		uenum_reset(values, &status);

		array_init_size(&calendars, count);

		for (i = 0; i < count; i++) {
			identifier = uenum_next(values, &length, &status);
			add_next_index_stringl(&calendars, identifier, length);
		}

		zend_update_property(ecma_intl_ce_Locale, object, PROPERTY_CALENDARS, sizeof(PROPERTY_CALENDARS) - 1, &calendars);

		zend_array_release(Z_ARRVAL(calendars));
	}

	uenum_close(values);
}

static void set_case_first(zend_object *object, char *locale_id)
{
	char *value = NULL;
	int value_len = 0;
	UErrorCode status = U_ZERO_ERROR;

	value = (char *) ecalloc(1, sizeof(char *) * ULOC_FULLNAME_CAPACITY);
	value_len = uloc_getKeywordValue(locale_id, KEYWORD_ICU_CASE_FIRST, value, ULOC_FULLNAME_CAPACITY, &status);

	SET_PROPERTY(PROPERTY_CASE_FIRST)

	efree(value);
}

static void set_collation(zend_object *object, char *locale_id)
{
	char *value = NULL;
	int value_len = 0;
	UErrorCode status = U_ZERO_ERROR;

	value = (char *) ecalloc(1, sizeof(char *) * ULOC_FULLNAME_CAPACITY);
	value_len = uloc_getKeywordValue(locale_id, KEYWORD_ICU_COLLATION, value, ULOC_FULLNAME_CAPACITY, &status);

	SET_PROPERTY(PROPERTY_COLLATION)

	efree(value);
}

static void set_hour_cycle(zend_object *object, char *locale_id)
{
	char *value = NULL;
	int value_len = 0;
	UErrorCode status = U_ZERO_ERROR;

	value = (char *) ecalloc(1, sizeof(char *) * ULOC_FULLNAME_CAPACITY);
	value_len = uloc_getKeywordValue(locale_id, KEYWORD_ICU_HOUR_CYCLE, value, ULOC_FULLNAME_CAPACITY, &status);

	SET_PROPERTY(PROPERTY_HOUR_CYCLE)

	efree(value);
}

static void set_language(zend_object *object, char *locale_id)
{
	char *value = NULL;
	int value_len = 0;
	UErrorCode status = U_ZERO_ERROR;

	value = (char *) ecalloc(1, sizeof(char *) * ULOC_FULLNAME_CAPACITY);
	value_len = uloc_getLanguage(locale_id, value, ULOC_FULLNAME_CAPACITY, &status);

	SET_PROPERTY(PROPERTY_LANGUAGE)

	efree(value);
}

static void set_numbering_system(zend_object *object, char *locale_id)
{
	char *value = NULL;
	int value_len = 0;
	UErrorCode status = U_ZERO_ERROR;

	value = (char *) ecalloc(1, sizeof(char *) * ULOC_FULLNAME_CAPACITY);
	value_len = uloc_getKeywordValue(locale_id, KEYWORD_ICU_NUMBERING_SYSTEM, value, ULOC_FULLNAME_CAPACITY, &status);

	SET_PROPERTY(PROPERTY_NUMBERING_SYSTEM)

	efree(value);
}

static void set_numeric(zend_object *object, char *locale_id)
{
	char *value = NULL;
	UErrorCode status = U_ZERO_ERROR;

	value = (char *) ecalloc(1, sizeof(char *) * ULOC_FULLNAME_CAPACITY);
	uloc_getKeywordValue(locale_id, KEYWORD_ICU_NUMERIC, value, ULOC_FULLNAME_CAPACITY, &status);

	if (strcmp(value, "yes") == 0) {
		zend_update_property_bool(ecma_intl_ce_Locale, object, PROPERTY_NUMERIC, sizeof(PROPERTY_NUMERIC) - 1, 1);
	} else {
		zend_update_property_bool(ecma_intl_ce_Locale, object, PROPERTY_NUMERIC, sizeof(PROPERTY_NUMERIC) - 1, 0);
	}

	efree(value);
}

static void set_region(zend_object *object, char *locale_id)
{
	char *value = NULL;
	int value_len = 0;
	UErrorCode status = U_ZERO_ERROR;

	value = (char *) ecalloc(1, sizeof(char *) * ULOC_FULLNAME_CAPACITY);
	value_len = uloc_getCountry(locale_id, value, ULOC_FULLNAME_CAPACITY, &status);

	SET_PROPERTY(PROPERTY_REGION)

	efree(value);
}

static void set_script(zend_object *object, char *locale_id)
{
	char *value = NULL;
	int value_len = 0;
	UErrorCode status = U_ZERO_ERROR;

	value = (char *) ecalloc(1, sizeof(char *) * ULOC_FULLNAME_CAPACITY);
	value_len = uloc_getScript(locale_id, value, ULOC_FULLNAME_CAPACITY, &status);

	SET_PROPERTY(PROPERTY_SCRIPT)

	efree(value);
}

PHP_METHOD(Ecma_Intl_Locale, __construct)
{
	char *tag = NULL, *bcp47_locale = NULL, *icu_locale = NULL;
	size_t tag_len = 0, bcp47_locale_len = 0;
	zval *options = NULL;
	UErrorCode status = U_ZERO_ERROR;

	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_STRING(tag, tag_len)
		Z_PARAM_OPTIONAL
		Z_PARAM_OBJECT_OF_CLASS_OR_NULL(options, ecma_intl_ce_Locale_Options)
	ZEND_PARSE_PARAMETERS_END();

	if (tag_len == 0) {
		zend_throw_error(ecma_intl_ce_RangeError,"invalid language tag");
	}

	zval *object = getThis();
	ecma_intl_locale_obj *locale = Z_ECMA_LOCALE_P(object);

	bcp47_locale = (char *) ecalloc(1, sizeof(char *) * ULOC_FULLNAME_CAPACITY);
	icu_locale = (char *) ecalloc(1, sizeof(char *) * ULOC_FULLNAME_CAPACITY);

	if (options) {
		char *constructed_locale = (char *) ecalloc(1, sizeof(char *) * ULOC_FULLNAME_CAPACITY);
		if (ecma_intl_build_locale(constructed_locale, tag, Z_ECMA_LOCALE_OPTIONS_P(options))) {
			bcp47_locale_len = ecma_intl_toCanonicalBcp47LanguageTag(constructed_locale, bcp47_locale);
			uloc_canonicalize(constructed_locale, icu_locale, ULOC_FULLNAME_CAPACITY, &status);
		}
		efree(constructed_locale);
	} else {
		bcp47_locale_len = ecma_intl_toCanonicalBcp47LanguageTag(tag, bcp47_locale);
		uloc_canonicalize(tag, icu_locale, ULOC_FULLNAME_CAPACITY, &status);
	}

	if (bcp47_locale_len) {
		locale->bcp47_locale = estrndup(bcp47_locale, bcp47_locale_len);
		locale->bcp47_locale_len = bcp47_locale_len;

		set_base_name(&locale->std, icu_locale);
		set_calendar(&locale->std, icu_locale);
		set_calendars(&locale->std, icu_locale);
		set_case_first(&locale->std, icu_locale);
		set_collation(&locale->std, icu_locale);
		set_hour_cycle(&locale->std, icu_locale);
		set_language(&locale->std, icu_locale);
		set_numbering_system(&locale->std, icu_locale);
		set_numeric(&locale->std, icu_locale);
		set_region(&locale->std, icu_locale);
		set_script(&locale->std, icu_locale);
	}

	efree(icu_locale);
	efree(bcp47_locale);
}

PHP_METHOD(Ecma_Intl_Locale, maximize)
{
	ZEND_PARSE_PARAMETERS_NONE();
}

PHP_METHOD(Ecma_Intl_Locale, minimize)
{
	ZEND_PARSE_PARAMETERS_NONE();
}

PHP_METHOD(Ecma_Intl_Locale, __toString)
{
	ZEND_PARSE_PARAMETERS_NONE();

	zval *object = getThis();
	ecma_intl_locale_obj *locale_obj = Z_ECMA_LOCALE_P(object);

	RETURN_STRINGL(locale_obj->bcp47_locale, locale_obj->bcp47_locale_len);
}

void ecma_intl_register_Locale()
{
	ecma_intl_ce_Locale = register_class_Ecma_Intl_Locale(zend_ce_stringable);
	ecma_intl_ce_Locale->create_object = ecma_intl_locale_obj_create;

	memcpy(&ecma_intl_locale_obj_handlers, &std_object_handlers, sizeof(zend_object_handlers));
	ecma_intl_locale_obj_handlers.offset = XtOffsetOf(ecma_intl_locale_obj, std);
	ecma_intl_locale_obj_handlers.free_obj = ecma_intl_locale_obj_free;
}
