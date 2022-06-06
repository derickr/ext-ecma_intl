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

#include "src/common.h"

#include "php_locale_week_info.h"
#include "src/php/handlers/php_locale_week_info_handlers.h"

zend_object *ecmaIntlLocaleWeekInfoObjCreate(zend_class_entry *classType) {
  ecmaIntlLocaleWeekInfoObj *weekInfoObj =
      zend_object_alloc(sizeof(ecmaIntlLocaleWeekInfoObj), classType);
  zend_object_std_init(&weekInfoObj->std, classType);
  object_properties_init(&weekInfoObj->std, classType);
  weekInfoObj->std.handlers = &ecmaIntlLocaleWeekInfoObjHandlers;

  return &weekInfoObj->std;
}