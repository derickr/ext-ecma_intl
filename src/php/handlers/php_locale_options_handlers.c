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

#include "php_locale_options_handlers.h"
#include "src/php/objects/php_locale_options.h"

zend_object_handlers ecmaIntlLocaleOptionsObjHandlers;

static void ecmaIntlLocaleOptionsObjFree(zend_object *object) {
  ecmaIntlLocaleOptionsObj *optionsObj =
      ecmaIntlLocaleOptionsObjFromObj(object);

  zend_object_std_dtor(&optionsObj->std);
}

void ecmaIntlRegisterLocaleOptionsHandlers() {
  memcpy(&ecmaIntlLocaleOptionsObjHandlers, zend_get_std_object_handlers(),
         sizeof(zend_object_handlers));

  ecmaIntlLocaleOptionsObjHandlers.offset =
      XtOffsetOf(ecmaIntlLocaleOptionsObj, std);
  ecmaIntlLocaleOptionsObjHandlers.free_obj = ecmaIntlLocaleOptionsObjFree;
}
