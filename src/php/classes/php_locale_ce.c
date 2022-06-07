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

#include "php_exceptions_ce.h"
#include "php_locale_ce.h"
#include "php_locale_options_ce.h"

#include "src/ecma_intl_arginfo.h"
#include "src/php/handlers/php_locale_handlers.h"
#include "src/php/objects/php_locale.h"
#include "src/php/objects/php_locale_options.h"
#include "src/unicode/builder.h"

#include <unicode/uloc.h>
#include <zend_interfaces.h>

zend_class_entry *ecmaIntlClassLocale = NULL;

PHP_METHOD(Ecma_Intl_Locale, __construct) {
  char *tag = NULL;
  size_t tagLen = 0;
  zval *options = NULL;

  ZEND_PARSE_PARAMETERS_START(1, 2)
  Z_PARAM_STRING(tag, tagLen)
  Z_PARAM_OPTIONAL
  Z_PARAM_OBJECT_OF_CLASS_OR_NULL(options, ecmaIntlClassLocaleOptions)
  ZEND_PARSE_PARAMETERS_END();

  if (tagLen == 0) {
    zend_throw_error(ecmaIntlClassRangeError, "invalid language tag");
  }

  zval *object = getThis();
  ecmaIntlLocaleObj *locale = Z_ECMA_LOCALE_P(object);

  if (options) {
    char *constructedLocale =
        (char *)ecalloc(1, sizeof(char *) * ULOC_FULLNAME_CAPACITY);
    if (icuBuildLocale(constructedLocale, tag,
                       Z_ECMA_LOCALE_OPTIONS_P(options))) {
      localeInit(locale, constructedLocale);
    }
    efree(constructedLocale);
  } else {
    localeInit(locale, tag);
  }
}

PHP_METHOD(Ecma_Intl_Locale, maximize) {
  char *canonicalId, *maximizedLocaleId = NULL;
  UErrorCode status = U_ZERO_ERROR;
  ecmaIntlLocaleObj *locale, *newLocale;
  zval *object;
  zend_object *newObject;

  ZEND_PARSE_PARAMETERS_NONE();

  object = getThis();
  locale = Z_ECMA_LOCALE_P(object);

  canonicalId = (char *)ecalloc(1, sizeof(char *) * ULOC_FULLNAME_CAPACITY);
  maximizedLocaleId =
      (char *)ecalloc(1, sizeof(char *) * ULOC_FULLNAME_CAPACITY);

  uloc_canonicalize(locale->bcp47Locale, canonicalId, ULOC_FULLNAME_CAPACITY,
                    &status);

  uloc_addLikelySubtags(canonicalId, maximizedLocaleId, ULOC_FULLNAME_CAPACITY,
                        &status);

  newObject = ecmaIntlLocaleObjCreate(ecmaIntlClassLocale);
  newLocale = ecmaIntlLocaleObjFromObj(newObject);
  localeInit(newLocale, maximizedLocaleId);

  efree(maximizedLocaleId);
  efree(canonicalId);

  RETURN_OBJ(&newLocale->std);
}

PHP_METHOD(Ecma_Intl_Locale, minimize) {
  char *canonicalId, *minimizedLocaleId = NULL;
  UErrorCode status = U_ZERO_ERROR;
  ecmaIntlLocaleObj *locale, *newLocale;
  zval *object;
  zend_object *newObject;

  ZEND_PARSE_PARAMETERS_NONE();

  object = getThis();
  locale = Z_ECMA_LOCALE_P(object);

  canonicalId = (char *)ecalloc(1, sizeof(char *) * ULOC_FULLNAME_CAPACITY);
  minimizedLocaleId =
      (char *)ecalloc(1, sizeof(char *) * ULOC_FULLNAME_CAPACITY);

  uloc_canonicalize(locale->bcp47Locale, canonicalId, ULOC_FULLNAME_CAPACITY,
                    &status);

  uloc_minimizeSubtags(canonicalId, minimizedLocaleId, ULOC_FULLNAME_CAPACITY,
                       &status);

  newObject = ecmaIntlLocaleObjCreate(ecmaIntlClassLocale);
  newLocale = ecmaIntlLocaleObjFromObj(newObject);
  localeInit(newLocale, minimizedLocaleId);

  efree(minimizedLocaleId);
  efree(canonicalId);

  RETURN_OBJ(&newLocale->std);
}

PHP_METHOD(Ecma_Intl_Locale, __toString) {
  ZEND_PARSE_PARAMETERS_NONE();

  zval *object = getThis();
  ecmaIntlLocaleObj *localeObj = Z_ECMA_LOCALE_P(object);

  RETURN_STRINGL(localeObj->bcp47Locale, localeObj->bcp47LocaleLen);
}

void ecmaIntlRegisterClassLocale() {
  ecmaIntlClassLocale = register_class_Ecma_Intl_Locale(zend_ce_stringable);
  ecmaIntlClassLocale->create_object = ecmaIntlLocaleObjCreate;

  ecmaIntlRegisterLocaleHandlers();
}
