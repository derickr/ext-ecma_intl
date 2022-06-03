<?php

/**
 * ecma_intl extension for PHP
 * Internationalization Support, Ecma-style (ECMA-402)
 *
 * Copyright (c) Ben Ramsey <ben@benramsey.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
 * implied. See the License for the specific language governing
 * permissions and limitations under the License.
 *
 * @generate-class-entries
 */

namespace Ecma\Intl\Locale;

/**
 * WeekInfo indicates information about days of the week for the associated
 * locale, for calendar purposes.
 *
 * @link https://tc39.es/proposal-intl-locale-info/#sec-week-info-of-locale Intl Locale Info Proposal
 */
final class WeekInfo
{
    /**
     * For the associated locale, this number indicates which day of the week
     * is considered the first day, for calendar purposes.
     */
    public readonly int $firstDay;

    /**
     * For the associated locale, this is a list of numbers that indicate which
     * days of the week are considered part of the weekend, for calendar purposes.
     *
     * @var int[]
     */
    public readonly array $weekend;

    /**
     * For the associated locale, this number indicates the minimum number of
     * days required for the first week of a month or year, for calendar purposes.
     */
    public readonly int $minimalDays;

    /**
     * Instances of this object may only be obtained from the `Locale::$weekInfo`
     * property.
     */
    private function __construct() {}
}
