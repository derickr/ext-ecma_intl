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

#include <ext/spl/spl_exceptions.h>

#include "exceptions.h"
#include "exceptions_arginfo.h"

zend_class_entry *ecma_intl_ce_IntlException = NULL;
zend_class_entry *ecma_intl_ce_IcuException = NULL;
zend_class_entry *ecma_intl_ce_RangeError = NULL;

void ecma_intl_register_exceptions()
{
	ecma_intl_ce_IntlException = register_class_Ecma_Intl_IntlException();

	ecma_intl_ce_IcuException = register_class_Ecma_Intl_IcuException(
		spl_ce_RuntimeException,
		ecma_intl_ce_IntlException
	);

	ecma_intl_ce_RangeError = register_class_Ecma_Intl_RangeError(
		zend_ce_value_error,
		ecma_intl_ce_IntlException
	);
}
