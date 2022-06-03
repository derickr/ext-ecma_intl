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

#ifndef ECMA_INTL_MEASURE_UNIT_BRIDGE_H
#define ECMA_INTL_MEASURE_UNIT_BRIDGE_H

#include <unicode/errorcode.h>
#include <unicode/uenum.h>

#ifdef __cplusplus
extern "C" {
#endif

UEnumeration *ecma_intl_getMeasurementUnits(const char **units,
                                            const UErrorCode *errorCode);

#ifdef __cplusplus
}
#endif

#endif /* ECMA_INTL_MEASURE_UNIT_BRIDGE_H */
