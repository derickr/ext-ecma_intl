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

#ifndef ECMA_INTL_PHP_LOCALE_TEXT_INFO_H
#define ECMA_INTL_PHP_LOCALE_TEXT_INFO_H

typedef struct ecmaIntlLocaleTextInfoObj ecmaIntlLocaleTextInfoObj;

struct ecmaIntlLocaleTextInfoObj {
  zend_object std;
};

static inline ecmaIntlLocaleTextInfoObj *
ecmaIntlLocaleTextInfoObjFromObj(zend_object *obj) {
  return (ecmaIntlLocaleTextInfoObj *)((char *)(obj)-XtOffsetOf(
      ecmaIntlLocaleTextInfoObj, std));
}

#define Z_ECMA_LOCALE_TEXT_INFO_P(zv)                                          \
  ecmaIntlLocaleTextInfoObjFromObj(Z_OBJ_P(zv))

zend_object *ecmaIntlLocaleTextInfoObjCreate(zend_class_entry *classType);

#endif /* ECMA_INTL_PHP_LOCALE_TEXT_INFO_H */
