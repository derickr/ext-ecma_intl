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
