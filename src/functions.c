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

#include <php.h>
#include <unicode/ucal.h>
#include <unicode/ucol.h>
#include <unicode/ucurr.h>
#include <unicode/uloc.h>
#include <unicode/unumsys.h>
#include <unicode/utypes.h>

#include "exceptions.h"
#include "functions.h"
#include "measure_unit_bridge.h"

#define CATEGORY_CALENDAR "calendar"
#define CATEGORY_COLLATION "collation"
#define CATEGORY_CURRENCY "currency"
#define CATEGORY_NUMBERING_SYSTEM "numberingSystem"
#define CATEGORY_TIME_ZONE "timeZone"
#define CATEGORY_UNIT "unit"

#define UNIT_TOTAL_CAPACITY 200

int ecma_intl_toCanonicalBcp47LanguageTag(const char *locale_id, char *language_tag)
{
	int language_tag_len;
	UErrorCode status = U_ZERO_ERROR;

	language_tag_len = uloc_toLanguageTag(locale_id, language_tag, ULOC_FULLNAME_CAPACITY, true, &status);

	if (strcmp(locale_id, "") == 0 || U_FAILURE(status)) {
		zend_throw_error(ecma_intl_ce_RangeError,
						 "Invalid language tag: \"%s\"",
						 locale_id);

		return 0;
	}

	return language_tag_len;
}

static zend_always_inline int php_array_string_case_compare(Bucket *f, Bucket *s)
{
	return string_case_compare_function(&f->val, &s->val);
}

PHP_FUNCTION(getCanonicalLocales)
{
	HashTable *locale_array;
	zval *locale_from_array, locale_from_string;
	zend_string *locale_string;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ARRAY_HT_OR_STR(locale_array, locale_string)
	ZEND_PARSE_PARAMETERS_END();

	if (locale_array == NULL) {
		ALLOC_HASHTABLE(locale_array);
		zend_hash_init(locale_array, 1, NULL, ZVAL_PTR_DTOR, 0);
		ZVAL_STR(&locale_from_string, locale_string);
		zend_hash_index_update(locale_array, 0, &locale_from_string);
		zend_string_release(locale_string);
		zval_ptr_dtor(&locale_from_string);
	}

	array_init_size(return_value, zend_hash_num_elements(locale_array));

	if (zend_hash_num_elements(locale_array) == 0) {
		if (locale_string) {
			zend_hash_destroy(locale_array);
			FREE_HASHTABLE(locale_array);
		}
		return;
	}

	ZEND_HASH_FOREACH_VAL(locale_array, locale_from_array)
		if (Z_TYPE_P(locale_from_array) != IS_STRING) {
			zend_throw_error(zend_ce_value_error,
							 "The $locales argument must be type string or an array of type string");
			RETURN_THROWS();
		}
		char languageTag[ULOC_FULLNAME_CAPACITY];
		if (ecma_intl_toCanonicalBcp47LanguageTag(Z_STRVAL_P(locale_from_array), languageTag)) {
			add_next_index_string(return_value, languageTag);
		}
	ZEND_HASH_FOREACH_END();

	if (locale_string) {
		zend_hash_destroy(locale_array);
		FREE_HASHTABLE(locale_array);
	}

	if (EG(exception)) {
		RETURN_THROWS();
	}
}

PHP_FUNCTION(getSupportedLocales)
{
	ZEND_PARSE_PARAMETERS_NONE();

	int count = uloc_countAvailable();

	array_init_size(return_value, count);

	for (int i = 0; i < count; i++) {
		const char *locale;
		char languageTag[ULOC_FULLNAME_CAPACITY];
		locale = uloc_getAvailable(i);
		if (ecma_intl_toCanonicalBcp47LanguageTag(locale, languageTag)) {
			add_next_index_string(return_value, languageTag);
		}
	}
}

PHP_FUNCTION(supportedValuesOf)
{
	zend_string *key;
	UEnumeration *values = NULL;
	UErrorCode status = U_ZERO_ERROR;

	int count, length, i;
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
		units = (const char **) emalloc(sizeof(char *) * UNIT_TOTAL_CAPACITY);
		values = ecma_intl_getMeasurementUnits(units, &status);
	} else {
		zend_throw_error(ecma_intl_ce_RangeError,
						 "Unknown key for Ecma\\Intl\\supportedValuesOf()");
		RETURN_THROWS();
	}

	if (U_FAILURE(status)) {
		zend_throw_error(ecma_intl_ce_IcuException,"%s", u_errorName(status));
		RETURN_THROWS();
	}

	count = uenum_count(values, &status);
	uenum_reset(values, &status);

	array_init_size(return_value, count);

	for (i = 0; i < count; i++) {
		identifier = uenum_next(values, &length, &status);
		add_next_index_stringl(return_value, identifier, length);
	}

	uenum_close(values);

	if (units) {
		efree(units);
	}

	zend_hash_sort(Z_ARRVAL_P(return_value), php_array_string_case_compare, 1);
}
