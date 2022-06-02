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

namespace Ecma\Intl;

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
    public readonly array $hourCycles = [];

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
