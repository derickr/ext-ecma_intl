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

#include <unicode/uloc.h>
#include <zend_interfaces.h>

#include "locale.h"
#include "locale_arginfo.h"
#include "options.h"
#include "src/functions.h"

zend_class_entry *ecma_intl_ce_Locale = NULL;

static zend_object_handlers ecma_intl_locale_obj_handlers;
static zend_object *ecma_intl_locale_obj_create(zend_class_entry *class_type);
static void ecma_intl_locale_obj_free(zend_object *object);

static zend_object *ecma_intl_locale_obj_create(zend_class_entry *class_type)
{
	ecma_intl_locale_obj *intern;

	intern = zend_object_alloc(sizeof(ecma_intl_locale_obj), class_type);

	intern->original_locale = NULL;
	intern->canonical_bcp47_locale = NULL;

	zend_object_std_init(&intern->std, class_type);
	object_properties_init(&intern->std, class_type);

	intern->std.handlers = &ecma_intl_locale_obj_handlers;

	return &intern->std;
}

void ecma_intl_locale_obj_free(zend_object *object)
{
	ecma_intl_locale_obj *locale_obj = ecma_intl_locale_obj_from_obj(object);

	zend_object_std_dtor(&locale_obj->std);

	if (locale_obj->original_locale) {
		efree(locale_obj->original_locale);
		locale_obj->original_locale = NULL;
	}

	if (locale_obj->canonical_bcp47_locale) {
		efree(locale_obj->canonical_bcp47_locale);
		locale_obj->canonical_bcp47_locale = NULL;
	}
}

PHP_METHOD(Ecma_Intl_Locale, __construct)
{
	char *language_tag = NULL, *bcp47_tag = NULL, *base_name = NULL;
	size_t language_tag_len = 0, bcp47_tag_len = 0, base_name_len = 0;
	zval *options_obj;
	UErrorCode status = U_ZERO_ERROR;

	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_STRING(language_tag, language_tag_len)
		Z_PARAM_OPTIONAL
		Z_PARAM_OBJECT_OF_CLASS_OR_NULL(options_obj, ecma_intl_ce_Locale_Options)
	ZEND_PARSE_PARAMETERS_END();

	zval *object = getThis();
	ecma_intl_locale_obj *locale_obj = Z_ECMA_LOCALE_P(object);

	locale_obj->original_locale = estrndup(language_tag, language_tag_len);
	locale_obj->original_locale_len = language_tag_len;

	bcp47_tag = (char *) emalloc(sizeof(char *) * ULOC_FULLNAME_CAPACITY);
	bcp47_tag_len = ecma_intl_toCanonicalBcp47LanguageTag(language_tag, bcp47_tag);

	locale_obj->canonical_bcp47_locale = estrndup(bcp47_tag, bcp47_tag_len);
	locale_obj->canonical_bcp47_locale_len = bcp47_tag_len;

	base_name = (char *) emalloc(sizeof(char *) * ULOC_FULLNAME_CAPACITY);
	base_name_len = uloc_getBaseName(bcp47_tag, base_name, ULOC_FULLNAME_CAPACITY, &status);

	zend_update_property_stringl(
		ecma_intl_ce_Locale,
		&locale_obj->std,
		"baseName",
		sizeof("baseName") - 1,
		base_name,
		base_name_len
	);

	efree(bcp47_tag);
	efree(base_name);
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

	RETURN_STRING(locale_obj->canonical_bcp47_locale);
}

void ecma_intl_register_Locale()
{
	ecma_intl_ce_Locale = register_class_Ecma_Intl_Locale(zend_ce_stringable);
	ecma_intl_ce_Locale->create_object = ecma_intl_locale_obj_create;

	memcpy(&ecma_intl_locale_obj_handlers, &std_object_handlers, sizeof(zend_object_handlers));
	ecma_intl_locale_obj_handlers.offset = XtOffsetOf(ecma_intl_locale_obj, std);
	ecma_intl_locale_obj_handlers.free_obj = ecma_intl_locale_obj_free;
}
