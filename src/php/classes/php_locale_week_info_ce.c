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

#include "php_locale_week_info_ce.h"
#include "src/ecma_intl_arginfo.h"
#include "src/php/handlers/php_locale_week_info_handlers.h"
#include "src/php/objects/php_locale_week_info.h"

zend_class_entry *ecmaIntlClassLocaleWeekInfo = NULL;

PHP_METHOD(Ecma_Intl_Locale_WeekInfo, __construct) {
  ZEND_PARSE_PARAMETERS_NONE();
}

void ecmaIntlRegisterClassLocaleWeekInfo() {
  ecmaIntlClassLocaleWeekInfo = register_class_Ecma_Intl_Locale_WeekInfo();
  ecmaIntlClassLocaleWeekInfo->create_object = ecmaIntlLocaleWeekInfoObjCreate;

  ecmaIntlRegisterLocaleWeekInfoHandlers();
}
