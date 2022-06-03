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

#ifndef ECMA_INTL_LOCALE_H
#define ECMA_INTL_LOCALE_H

#include <php.h>

typedef struct _ecma_intl_locale_obj ecma_intl_locale_obj;

struct _ecma_intl_locale_obj {
  char *bcp47_locale;
  zend_ulong bcp47_locale_len;
  zend_object std;
};

static inline ecma_intl_locale_obj *
ecma_intl_locale_obj_from_obj(zend_object *obj) {
  return (ecma_intl_locale_obj *)((char *)(obj)-XtOffsetOf(ecma_intl_locale_obj,
                                                           std));
}

#define Z_ECMA_LOCALE_P(zv) ecma_intl_locale_obj_from_obj(Z_OBJ_P(zv))

extern zend_class_entry *ecma_intl_ce_Locale;

void ecma_intl_register_Locale(void);

#endif /* ECMA_INTL_LOCALE_H */
