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
 * @throws \RangeException
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
 * @throws \RangeException An unsupported key was passed as a parameter.
 *
 * @psalm-param 'calendar'|'collation'|'currency'|'numberingSystem'|'timeZone'|'unit' $key
 */
function supportedValuesOf(string $key): array {}
