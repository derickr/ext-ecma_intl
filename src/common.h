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

#ifndef ECMA_INTL_COMMON_H
#define ECMA_INTL_COMMON_H

#include <php.h>

#include "exceptions.h"

#define CASE_FIRST_FALSE "false"
#define CASE_FIRST_LOWER "lower"
#define CASE_FIRST_UPPER "upper"

#define ECMA_INTL_FAILURE (-1)
#define ECMA_INTL_NOOP 0
#define ECMA_INTL_SUCCESS 1

#define HOUR_H11 "h11"
#define HOUR_H12 "h12"
#define HOUR_H23 "h23"
#define HOUR_H24 "h24"

#define KEYWORD_BCP_47_CALENDAR "ca"
#define KEYWORD_BCP_47_CASE_FIRST "kf"
#define KEYWORD_BCP_47_COLLATION "co"
#define KEYWORD_BCP_47_HOUR_CYCLE "hc"
#define KEYWORD_BCP_47_NUMBERING_SYSTEM "nu"
#define KEYWORD_BCP_47_NUMERIC "kn"

#define KEYWORD_ICU_CALENDAR "calendar"
#define KEYWORD_ICU_CASE_FIRST "colcasefirst"
#define KEYWORD_ICU_COLLATION "collation"
#define KEYWORD_ICU_HOUR_CYCLE "hours"
#define KEYWORD_ICU_NUMBERING_SYSTEM "numbers"
#define KEYWORD_ICU_NUMERIC "colnumeric"

#define LANGUAGE_UNDETERMINED "und"

#define NUMERIC_YES "true"
#define NUMERIC_NO "false"

#define PROPERTY_BASE_NAME "baseName"
#define PROPERTY_CALENDAR "calendar"
#define PROPERTY_CALENDARS "calendars"
#define PROPERTY_CASE_FIRST "caseFirst"
#define PROPERTY_COLLATION "collation"
#define PROPERTY_HOUR_CYCLE "hourCycle"
#define PROPERTY_HOUR_CYCLES "hourCycles"
#define PROPERTY_LANGUAGE "language"
#define PROPERTY_NUMBERING_SYSTEM "numberingSystem"
#define PROPERTY_NUMBERING_SYSTEMS "numberingSystems"
#define PROPERTY_NUMERIC "numeric"
#define PROPERTY_REGION "region"
#define PROPERTY_SCRIPT "script"
#define PROPERTY_TEXT_INFO "textInfo"
#define PROPERTY_TIME_ZONES "timeZones"
#define PROPERTY_WEEK_INFO "weekInfo"

#endif /* ECMA_INTL_COMMON_H */
