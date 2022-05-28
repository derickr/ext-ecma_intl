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

#include "locale.h"
#include "locale_arginfo.h"
#include "options.h"

zend_class_entry *ecma_intl_ce_Locale = NULL;

static zend_object_handlers ecma_intl_locale_obj_handlers;
static zend_object *ecma_intl_locale_obj_new(zend_class_entry *class_type);

static zend_object *ecma_intl_locale_obj_new(zend_class_entry *class_type)
{
	ecma_intl_locale_obj *intern = zend_object_alloc(sizeof(ecma_intl_locale_obj), class_type);
	zend_object_std_init(&intern->std, class_type);
	object_properties_init(&intern->std, class_type);
	intern->std.handlers = &ecma_intl_locale_obj_handlers;

	return &intern->std;
}

PHP_METHOD(Ecma_Intl_Locale, __construct)
{
	char *language_tag = NULL;
	size_t language_tag_len = 0;
	zval *options_obj = NULL;
	ecma_intl_locale_obj *locale_obj;

	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_STRING(language_tag, language_tag_len)
		Z_PARAM_OPTIONAL
		Z_PARAM_OBJECT_OF_CLASS_OR_NULL(options_obj, ecma_intl_ce_Locale_Options)
	ZEND_PARSE_PARAMETERS_END();

	zval *object = getThis();
	locale_obj = Z_ECMA_LOCALE_P(object);

	zend_update_property_stringl(
		ecma_intl_ce_Locale,
		&locale_obj->std,
		"baseName",
		sizeof("baseName") - 1,
		language_tag,
		language_tag_len
	);
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
}

PHP_METHOD(Ecma_Intl_Locale, toString)
{
	ZEND_PARSE_PARAMETERS_NONE();
}

void ecma_intl_register_Locale()
{
	ecma_intl_ce_Locale = register_class_Ecma_Intl_Locale(zend_ce_stringable);
	ecma_intl_ce_Locale->create_object = ecma_intl_locale_obj_new;

	memcpy(&ecma_intl_locale_obj_handlers, &std_object_handlers, sizeof(zend_object_handlers));
}