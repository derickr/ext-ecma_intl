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

#include "locale_options.h"
#include "locale_options_arginfo.h"

#include <zend_interfaces.h>

#define UPDATE_STRING_PROPERTY(property, var, len)                             \
  zend_update_property_stringl(ecmaIntlCeLocaleOptions, &options->std,         \
                               property, sizeof(property) - 1, var, len)

#define UPDATE_BOOL_PROPERTY(property, var)                                    \
  zend_update_property_bool(ecmaIntlCeLocaleOptions, &options->std, property,  \
                            sizeof(property) - 1, var)

zend_class_entry *ecmaIntlCeLocaleOptions = NULL;

static zend_object_handlers ecmaIntlLocaleOptionsObjHandlers;
static zend_object *ecmaIntlLocaleOptionsObjNew(zend_class_entry *classType);
static void ecmaIntlLocaleOptionsObjFree(zend_object *object);

static zend_object *ecmaIntlLocaleOptionsObjNew(zend_class_entry *classType) {
  ecmaIntlLocaleOptionsObj *optionsObj =
      zend_object_alloc(sizeof(ecmaIntlLocaleOptionsObj), classType);
  zend_object_std_init(&optionsObj->std, classType);
  object_properties_init(&optionsObj->std, classType);
  optionsObj->std.handlers = &ecmaIntlLocaleOptionsObjHandlers;

  return &optionsObj->std;
}

void ecmaIntlLocaleOptionsObjFree(zend_object *object) {
  ecmaIntlLocaleOptionsObj *optionsObj =
      ecmaIntlLocaleOptionsObjFromObj(object);

  zend_object_std_dtor(&optionsObj->std);
}

PHP_METHOD(Ecma_Intl_Locale_Options, __construct) {
  char *calendar = NULL, *caseFirst = NULL, *collation = NULL,
       *hourCycle = NULL, *language = NULL, *numberingSystem = NULL,
       *region = NULL, *script = NULL;

  size_t calendarLen, caseFirstLen, collationLen, hourCycleLen, languageLen,
      numberingSystemLen, regionLen, scriptLen;

  bool numeric = 0, numericNull = 1;

  ZEND_PARSE_PARAMETERS_START(0, 9)
  Z_PARAM_OPTIONAL
  Z_PARAM_STRING_OR_NULL(calendar, calendarLen)
  Z_PARAM_STRING_OR_NULL(caseFirst, caseFirstLen)
  Z_PARAM_STRING_OR_NULL(collation, collationLen)
  Z_PARAM_STRING_OR_NULL(hourCycle, hourCycleLen)
  Z_PARAM_STRING_OR_NULL(language, languageLen)
  Z_PARAM_STRING_OR_NULL(numberingSystem, numberingSystemLen)
  Z_PARAM_BOOL_OR_NULL(numeric, numericNull)
  Z_PARAM_STRING_OR_NULL(region, regionLen)
  Z_PARAM_STRING_OR_NULL(script, scriptLen)
  ZEND_PARSE_PARAMETERS_END();

  zval *object = getThis();
  ecmaIntlLocaleOptionsObj *options = Z_ECMA_LOCALE_OPTIONS_P(object);

  if (calendar) {
    UPDATE_STRING_PROPERTY(PROPERTY_CALENDAR, calendar, calendarLen);
  }

  if (caseFirst) {
    UPDATE_STRING_PROPERTY(PROPERTY_CASE_FIRST, caseFirst, caseFirstLen);
  }

  if (collation) {
    UPDATE_STRING_PROPERTY(PROPERTY_COLLATION, collation, collationLen);
  }

  if (hourCycle) {
    UPDATE_STRING_PROPERTY(PROPERTY_HOUR_CYCLE, hourCycle, hourCycleLen);
  }

  if (language) {
    UPDATE_STRING_PROPERTY(PROPERTY_LANGUAGE, language, languageLen);
  }

  if (numberingSystem) {
    UPDATE_STRING_PROPERTY(PROPERTY_NUMBERING_SYSTEM, numberingSystem,
                           numberingSystemLen);
  }

  if (numericNull == 0) {
    UPDATE_BOOL_PROPERTY(PROPERTY_NUMERIC, numeric);
  }

  if (region) {
    UPDATE_STRING_PROPERTY(PROPERTY_REGION, region, regionLen);
  }

  if (script) {
    UPDATE_STRING_PROPERTY(PROPERTY_SCRIPT, script, scriptLen);
  }
}

void ecmaIntlRegisterLocaleOptions() {
  ecmaIntlCeLocaleOptions = register_class_Ecma_Intl_Locale_Options();
  ecmaIntlCeLocaleOptions->create_object = ecmaIntlLocaleOptionsObjNew;

  memcpy(&ecmaIntlLocaleOptionsObjHandlers, &std_object_handlers,
         sizeof(zend_object_handlers));
  ecmaIntlLocaleOptionsObjHandlers.offset =
      XtOffsetOf(ecmaIntlLocaleOptionsObj, std);
  ecmaIntlLocaleOptionsObjHandlers.free_obj = ecmaIntlLocaleOptionsObjFree;
}
