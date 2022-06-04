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

#include <Zend/zend_exceptions.h>
#include <ext/spl/spl_exceptions.h>

#include "php_exceptions_ce.h"
#include "src/ecma_intl_arginfo.h"

zend_class_entry *ecmaIntlClassIntlException = NULL;
zend_class_entry *ecmaIntlClassIcuException = NULL;
zend_class_entry *ecmaIntlClassRangeError = NULL;

void ecmaIntlRegisterClassExceptions() {
  ecmaIntlClassIntlException = register_class_Ecma_Intl_IntlException();

  ecmaIntlClassIcuException = register_class_Ecma_Intl_IcuException(
      spl_ce_RuntimeException, ecmaIntlClassIntlException);

  ecmaIntlClassRangeError = register_class_Ecma_Intl_RangeError(
      zend_ce_value_error, ecmaIntlClassIntlException);
}
