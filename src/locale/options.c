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

#include "../common.h"
#include "options.h"
#include "options_arginfo.h"

#define UPDATE_STRING_PROPERTY(property, var, len) \
	zend_update_property_stringl(ecma_intl_ce_Locale_Options, &options->std, property, sizeof(property) - 1, var, len)

#define UPDATE_BOOL_PROPERTY(property, var) \
	zend_update_property_bool(ecma_intl_ce_Locale_Options, &options->std, property, sizeof(property) - 1, var)

zend_class_entry *ecma_intl_ce_Locale_Options = NULL;

static zend_object_handlers ecma_intl_locale_options_obj_handlers;
static zend_object *ecma_intl_locale_options_obj_new(zend_class_entry *class_type);
static void ecma_intl_locale_options_obj_free(zend_object *object);

static zend_object *ecma_intl_locale_options_obj_new(zend_class_entry *class_type)
{
	ecma_intl_locale_options_obj *intern = zend_object_alloc(sizeof(ecma_intl_locale_options_obj), class_type);
	zend_object_std_init(&intern->std, class_type);
	object_properties_init(&intern->std, class_type);
	intern->std.handlers = &ecma_intl_locale_options_obj_handlers;

	return &intern->std;
}

void ecma_intl_locale_options_obj_free(zend_object *object)
{
	ecma_intl_locale_options_obj *options_obj = ecma_intl_locale_options_obj_from_obj(object);

	zend_object_std_dtor(&options_obj->std);
}

PHP_METHOD(Ecma_Intl_Locale_Options, __construct)
{
	char *calendar = NULL, *case_first = NULL, *collation = NULL,
		*hour_cycle = NULL, *language = NULL, *numbering_system = NULL,
		*region = NULL, *script = NULL;

	size_t calendar_len, case_first_len, collation_len, hour_cycle_len,
		 language_len, numbering_system_len, region_len, script_len;

	bool numeric = 0, numeric_null = 1;

	ZEND_PARSE_PARAMETERS_START(0, 9)
		Z_PARAM_OPTIONAL
		Z_PARAM_STRING_OR_NULL(calendar, calendar_len)
		Z_PARAM_STRING_OR_NULL(case_first, case_first_len)
		Z_PARAM_STRING_OR_NULL(collation, collation_len)
		Z_PARAM_STRING_OR_NULL(hour_cycle, hour_cycle_len)
		Z_PARAM_STRING_OR_NULL(language, language_len)
		Z_PARAM_STRING_OR_NULL(numbering_system, numbering_system_len)
		Z_PARAM_BOOL_OR_NULL(numeric, numeric_null)
		Z_PARAM_STRING_OR_NULL(region, region_len)
		Z_PARAM_STRING_OR_NULL(script, script_len)
	ZEND_PARSE_PARAMETERS_END();

	zval *object = getThis();
	ecma_intl_locale_options_obj *options = Z_ECMA_LOCALE_OPTIONS_P(object);

	if (calendar) {
		UPDATE_STRING_PROPERTY(PROPERTY_CALENDAR, calendar, calendar_len);
	}

	if (case_first) {
		UPDATE_STRING_PROPERTY(PROPERTY_CASE_FIRST, case_first, case_first_len);
	}

	if (collation) {
		UPDATE_STRING_PROPERTY(PROPERTY_COLLATION, collation, collation_len);
	}

	if (hour_cycle) {
		UPDATE_STRING_PROPERTY(PROPERTY_HOUR_CYCLE, hour_cycle, hour_cycle_len);
	}

	if (language) {
		UPDATE_STRING_PROPERTY(PROPERTY_LANGUAGE, language, language_len);
	}

	if (numbering_system) {
		UPDATE_STRING_PROPERTY(PROPERTY_NUMBERING_SYSTEM, numbering_system, numbering_system_len);
	}

	if (numeric_null == 0) {
		UPDATE_BOOL_PROPERTY(PROPERTY_NUMERIC, numeric);
	}

	if (region) {
		UPDATE_STRING_PROPERTY(PROPERTY_REGION, region, region_len);
	}

	if (script) {
		UPDATE_STRING_PROPERTY(PROPERTY_SCRIPT, script, script_len);
	}
}

void ecma_intl_register_Locale_Options()
{
	ecma_intl_ce_Locale_Options = register_class_Ecma_Intl_Locale_Options();
	ecma_intl_ce_Locale_Options->create_object = ecma_intl_locale_options_obj_new;

	memcpy(&ecma_intl_locale_options_obj_handlers, &std_object_handlers, sizeof(zend_object_handlers));
	ecma_intl_locale_options_obj_handlers.offset = XtOffsetOf(ecma_intl_locale_options_obj, std);
	ecma_intl_locale_options_obj_handlers.free_obj = ecma_intl_locale_options_obj_free;
}
