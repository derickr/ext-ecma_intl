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

#include "calendar.h"
#include "src/php/classes/php_exceptions_ce.h"

UCalendarWeekdayType getCanonicalDayOfWeekType(UCalendar *calendar, int day) {
  UErrorCode status = U_ZERO_ERROR;
  UCalendarWeekdayType type;

  type = ucal_getDayOfWeekType(calendar, day, &status);

  if (U_FAILURE(status)) {
    zend_throw_error(ecmaIntlClassIcuException, "foo");
  }

  switch (type) {
  /* UCAL_WEEKEND_ONSET is a day that starts as a weekday and transitions to the
   * weekend. It means this is a weekday. */
  case UCAL_WEEKEND_ONSET:
  case UCAL_WEEKDAY:
    return UCAL_WEEKDAY;

  /* UCAL_WEEKEND_CEASE is a day that starts as the weekend and transitions to a
   * weekday. It means this is a weekend. */
  case UCAL_WEEKEND_CEASE:
  case UCAL_WEEKEND:
  default:
    return UCAL_WEEKEND;
  }
}
