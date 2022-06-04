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

#ifndef ECMA_INTL_PHP_LOCALE_H
#define ECMA_INTL_PHP_LOCALE_H

typedef struct ecmaIntlLocaleObj ecmaIntlLocaleObj;

struct ecmaIntlLocaleObj {
  char *bcp47Locale;
  zend_ulong bcp47LocaleLen;
  zend_object std;
};

static inline ecmaIntlLocaleObj *ecmaIntlLocaleObjFromObj(zend_object *obj) {
  return (
      ecmaIntlLocaleObj *)((char *)(obj)-XtOffsetOf(ecmaIntlLocaleObj, std));
}

#define Z_ECMA_LOCALE_P(zv) ecmaIntlLocaleObjFromObj(Z_OBJ_P(zv))

zend_object *ecmaIntlLocaleObjCreate(zend_class_entry *classType);

void localeSetBaseName(zend_object *object, char *localeId);
void localeSetCalendar(zend_object *object, char *localeId);
void localeSetCalendars(zend_object *object, char *localeId);
void localeSetCaseFirst(zend_object *object, char *localeId);
void localeSetCollation(zend_object *object, char *localeId);
void localeSetHourCycle(zend_object *object, char *localeId);
void localeSetHourCycles(zend_object *object, char *localeId);
void localeSetLanguage(zend_object *object, char *localeId);
void localeSetNumberingSystem(zend_object *object, char *localeId);
void localeSetNumeric(zend_object *object, char *localeId);
void localeSetRegion(zend_object *object, char *localeId);
void localeSetScript(zend_object *object, char *localeId);

#endif /* ECMA_INTL_PHP_LOCALE_H */
