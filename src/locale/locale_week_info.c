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

#include "locale_week_info.h"
#include "locale_week_info_arginfo.h"

#include <zend_interfaces.h>

zend_class_entry *ecmaIntlCeLocaleWeekInfo = NULL;

static zend_object_handlers ecmaIntlLocaleWeekInfoObjHandlers;

static zend_object *ecmaIntlLocaleWeekInfoObjNew(zend_class_entry *classType) {
  ecmaIntlLocaleWeekInfoObj *weekInfoObj =
      zend_object_alloc(sizeof(ecmaIntlLocaleWeekInfoObj), classType);
  zend_object_std_init(&weekInfoObj->std, classType);
  object_properties_init(&weekInfoObj->std, classType);
  weekInfoObj->std.handlers = &ecmaIntlLocaleWeekInfoObjHandlers;

  return &weekInfoObj->std;
}

PHP_METHOD(Ecma_Intl_Locale_WeekInfo, __construct) {
  ZEND_PARSE_PARAMETERS_NONE();
}

void ecmaIntlRegisterLocaleWeekInfo() {
  ecmaIntlCeLocaleWeekInfo = register_class_Ecma_Intl_Locale_WeekInfo();
  ecmaIntlCeLocaleWeekInfo->create_object = ecmaIntlLocaleWeekInfoObjNew;

  memcpy(&ecmaIntlLocaleWeekInfoObjHandlers, &std_object_handlers,
         sizeof(zend_object_handlers));
}
