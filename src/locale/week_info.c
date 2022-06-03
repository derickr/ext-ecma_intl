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

#include "week_info.h"
#include "week_info_arginfo.h"

#include <zend_interfaces.h>

zend_class_entry *ecma_intl_ce_Locale_WeekInfo = NULL;

static zend_object_handlers ecma_intl_locale_week_info_obj_handlers;

static zend_object *
ecma_intl_locale_week_info_obj_new(zend_class_entry *class_type) {
  ecma_intl_locale_week_info_obj *intern =
      zend_object_alloc(sizeof(ecma_intl_locale_week_info_obj), class_type);
  zend_object_std_init(&intern->std, class_type);
  object_properties_init(&intern->std, class_type);
  intern->std.handlers = &ecma_intl_locale_week_info_obj_handlers;

  return &intern->std;
}

PHP_METHOD(Ecma_Intl_Locale_WeekInfo, __construct) {
  ZEND_PARSE_PARAMETERS_NONE();
}

void ecma_intl_register_Locale_WeekInfo() {
  ecma_intl_ce_Locale_WeekInfo = register_class_Ecma_Intl_Locale_WeekInfo();
  ecma_intl_ce_Locale_WeekInfo->create_object =
      ecma_intl_locale_week_info_obj_new;

  memcpy(&ecma_intl_locale_week_info_obj_handlers, &std_object_handlers,
         sizeof(zend_object_handlers));
}
