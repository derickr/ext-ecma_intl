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

#ifndef ECMA_INTL_EXCEPTIONS_H
#define ECMA_INTL_EXCEPTIONS_H

#include <php.h>

#include <Zend/zend_exceptions.h>
#include <ext/spl/spl_exceptions.h>

void ecma_intl_register_exceptions(void);

extern zend_class_entry *ecma_intl_ce_IntlException;
extern zend_class_entry *ecma_intl_ce_IcuException;
extern zend_class_entry *ecma_intl_ce_RangeError;

#endif /* ECMA_INTL_EXCEPTIONS_H */
