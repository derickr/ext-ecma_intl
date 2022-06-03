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

#ifndef ECMA_INTL_LOCALE_OPTIONS_H
#define ECMA_INTL_LOCALE_OPTIONS_H

#include "../common.h"

typedef struct ecmaIntlLocaleOptionsObj ecmaIntlLocaleOptionsObj;

struct ecmaIntlLocaleOptionsObj {
  zend_object std;
};

static inline ecmaIntlLocaleOptionsObj *
ecmaIntlLocaleOptionsObjFromObj(zend_object *obj) {
  return (ecmaIntlLocaleOptionsObj *)((char *)(obj)-XtOffsetOf(
      ecmaIntlLocaleOptionsObj, std));
}

#define Z_ECMA_LOCALE_OPTIONS_P(zv) ecmaIntlLocaleOptionsObjFromObj(Z_OBJ_P(zv))

extern zend_class_entry *ecmaIntlCeLocaleOptions;

void ecmaIntlRegisterLocaleOptions(void);

#endif /* ECMA_INTL_LOCALE_OPTIONS_H */
