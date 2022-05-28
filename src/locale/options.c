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

#include <zend_interfaces.h>

#include "options.h"
#include "options_arginfo.h"

zend_class_entry *ecma_intl_ce_Locale_Options = NULL;

static zend_object_handlers ecma_intl_locale_options_obj_handlers;

static zend_object *ecma_intl_locale_options_obj_new(zend_class_entry *class_type)
{
	ecma_intl_locale_options_obj *intern = zend_object_alloc(sizeof(ecma_intl_locale_options_obj), class_type);
	zend_object_std_init(&intern->std, class_type);
	object_properties_init(&intern->std, class_type);
	intern->std.handlers = &ecma_intl_locale_options_obj_handlers;

	return &intern->std;
}

PHP_METHOD(Ecma_Intl_Locale_Options, __construct)
{
	char *calendar = NULL, *caseFirst = NULL, *collation = NULL,
		*hourCycle = NULL, *language = NULL, *numberingSystem = NULL,
		*region = NULL, *script = NULL;

	size_t calendar_len, caseFirst_len, collation_len, hourCycle_len,
		 language_len, numberingSystem_len, region_len, script_len;

	bool numeric = 0, numeric_null = 1;

	ecma_intl_locale_options_obj *options;

	ZEND_PARSE_PARAMETERS_START(0, 9)
		Z_PARAM_OPTIONAL
		Z_PARAM_STRING_OR_NULL(calendar, calendar_len)
		Z_PARAM_STRING_OR_NULL(caseFirst, caseFirst_len)
		Z_PARAM_STRING_OR_NULL(collation, collation_len)
		Z_PARAM_STRING_OR_NULL(hourCycle, hourCycle_len)
		Z_PARAM_STRING_OR_NULL(language, language_len)
		Z_PARAM_STRING_OR_NULL(numberingSystem, numberingSystem_len)
		Z_PARAM_BOOL_OR_NULL(numeric, numeric_null)
		Z_PARAM_STRING_OR_NULL(region, region_len)
		Z_PARAM_STRING_OR_NULL(script, script_len)
	ZEND_PARSE_PARAMETERS_END();

	zval *object = getThis();
	options = Z_ECMA_LOCALE_OPTIONS_P(object);

	if (calendar) {
		zend_update_property_stringl(
			ecma_intl_ce_Locale_Options,
			&options->std,
			"calendar",
			sizeof("calendar") - 1,
			calendar,
			calendar_len
		);
	}

	if (caseFirst) {
		zend_update_property_stringl(
			ecma_intl_ce_Locale_Options,
			&options->std,
			"caseFirst",
			sizeof("caseFirst") - 1,
			caseFirst,
			caseFirst_len
		);
	}

	if (collation) {
		zend_update_property_stringl(
			ecma_intl_ce_Locale_Options,
			&options->std,
			"collation",
			sizeof("collation") - 1,
			collation,
			collation_len
		);
	}

	if (hourCycle) {
		zend_update_property_stringl(
			ecma_intl_ce_Locale_Options,
			&options->std,
			"hourCycle",
			sizeof("hourCycle") - 1,
			hourCycle,
			hourCycle_len
		);
	}

	if (language) {
		zend_update_property_stringl(
			ecma_intl_ce_Locale_Options,
			&options->std,
			"language",
			sizeof("language") - 1,
			language,
			language_len
		);
	}

	if (numberingSystem) {
		zend_update_property_stringl(
			ecma_intl_ce_Locale_Options,
			&options->std,
			"numberingSystem",
			sizeof("numberingSystem") - 1,
			numberingSystem,
			numberingSystem_len
		);
	}

	if (numeric_null == 0) {
		zend_update_property_bool(
			ecma_intl_ce_Locale_Options,
			&options->std,
			"numeric",
			sizeof("numeric") - 1,
			numeric
		);
	}

	if (region) {
		zend_update_property_stringl(
			ecma_intl_ce_Locale_Options,
			&options->std,
			"region",
			sizeof("region") - 1,
			region,
			region_len
		);
	}

	if (script) {
		zend_update_property_stringl(
			ecma_intl_ce_Locale_Options,
			&options->std,
			"script",
			sizeof("script") - 1,
			script,
			script_len
		);
	}
}

void ecma_intl_register_Locale_Options()
{
	ecma_intl_ce_Locale_Options = register_class_Ecma_Intl_Locale_Options();
	ecma_intl_ce_Locale_Options->create_object = ecma_intl_locale_options_obj_new;

	memcpy(&ecma_intl_locale_options_obj_handlers, &std_object_handlers, sizeof(zend_object_handlers));
}
