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

namespace Ecma\Intl
{
    /**
     * Returns an array of the $locales in their BCP-47 canonical forms
     *
     * @link https://tc39.es/ecma402/#sec-intl.getcanonicallocales ECMA-402 definition for Intl.getCanonicalLocales()
     * @link https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Intl/getCanonicalLocales MDN documentation for Intl.getCanonicalLocales()
     * @link https://www.rfc-editor.org/info/bcp47 BCP 47
     *
     * @param string[]|string $locales
     *
     * @return string[]
     *
     * @throws RangeError when the provided locale or locales is invalid
     * @throws \ValueError when the locales array contains items that aren't of type string
     */
    function getCanonicalLocales(array|string $locales): array {}

    /**
     * Returns an array of all locales supported by this implementation
     *
     * Please note this function is not a part of the Ecma Intl standard.
     *
     * @return string[]
     */
    function getSupportedLocales(): array {}

    /**
     * Returns an array of supported values for a given option
     *
     * @link https://tc39.es/proposal-intl-enumeration/#sec-intl.supportedvaluesof Intl.supportedValuesOf as defined in Ecma Intl Enumeration API Specification, Stage 3 Draft
     * @link https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Intl/supportedValuesOf MDN documentation for Intl.supportedValuesOf()
     *
     * @return string[]
     *
     * @throws RangeError when providing an unsupported key
     *
     * @psalm-param 'calendar'|'collation'|'currency'|'numberingSystem'|'timeZone'|'unit' $key
     */
    function supportedValuesOf(string $key): array {}

    interface IntlException {}

    /**
     * The error this exception indicates originated from the underlying ICU library
     */
    class IcuException extends \RuntimeException implements IntlException {}

    /**
     * ECMA-402 uses range errors to indicate when a passed value is invalid or out-of-bounds
     */
    class RangeError extends \ValueError implements IntlException {}

    class Locale implements \Stringable
    {
        public readonly string $baseName;

        public readonly ?string $calendar;

        /**
         * Returns an array of one or more calendar identifiers that are supported by the locale
         *
         * @link https://tc39.es/proposal-intl-locale-info/#sec-Intl.Locale.prototype.calendars Intl Locale Info Proposal
         * @link https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Intl/Locale/calendars MDN web docs
         *
         * @var string[]
         */
        public readonly array $calendars;

        public readonly ?string $caseFirst;

        public readonly ?string $collation;

        public readonly ?string $hourCycle;

        /**
         * Returns an array of one or more hour cycle identifiers supported by the locale
         *
         * @link https://tc39.es/proposal-intl-locale-info/#sec-Intl.Locale.prototype.hourCycles Intl Locale Info Proposal
         * @link https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Intl/Locale/hourCycles MDN web docs
         *
         * @var string[]
         */
        public readonly array $hourCycles;

        public readonly ?string $language;

        public readonly ?string $numberingSystem;

        public readonly array $numberingSystems = [];

        public readonly bool $numeric;

        public readonly ?string $region;

        public readonly ?string $script;

        public readonly ?string $textInfo = null;

        public readonly array $timeZones = [];

        /**
         * @link https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Intl/Locale/weekInfo MDN web docs
         */
        public readonly ?Locale\WeekInfo $weekInfo = null;

        public function __construct(string $tag, ?Locale\Options $options = null) {}

        public function maximize(): Locale {}

        public function minimize(): Locale {}

        /**
         * @implementation-alias Ecma\Intl\Locale::__toString
         */
        public function toString(): string {}

        public function __toString(): string {}
    }
}

namespace Ecma\Intl\Locale
{
    class Options
    {
        public ?string $calendar = null;

        public ?string $caseFirst = null;

        public ?string $collation = null;

        public ?string $hourCycle = null;

        public ?string $language = null;

        public ?string $numberingSystem = null;

        public ?bool $numeric = null;

        public ?string $region = null;

        public ?string $script = null;

        public function __construct(
            ?string $calendar = null,
            ?string $caseFirst = null,
            ?string $collation = null,
            ?string $hourCycle = null,
            ?string $language = null,
            ?string $numberingSystem = null,
            ?bool $numeric = null,
            ?string $region = null,
            ?string $script = null,
        ) {}
    }

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
}
