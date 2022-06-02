--TEST--
Ecma\Intl\Locale with options
--EXTENSIONS--
ecma_intl
--FILE--
<?php
use Ecma\Intl\Locale;

$tests = [
    [
        'locale' => 'en-US',
        'options' => null,
    ],
    [
        'locale' => 'en-US',
        'options' => new Locale\Options(),
    ],
    [
        'locale' => 'en',
        'options' => new Locale\Options(
             region: 'GB',
        ),
    ],
    [
        'locale' => 'en-Latn-US',
        'options' => new Locale\Options(
            language: 'fr',
            region: 'CA',
            script: 'Cyrl',
        ),
    ],
    [
        'locale' => 'und',
        'options' => new Locale\Options(
            calendar: 'gregory',
            caseFirst: 'upper',
            collation: 'emoji',
            hourCycle: 'h23',
            language: 'en',
            numberingSystem: 'latn',
            numeric: true,
            region: 'US',
            script: 'Latn',
        ),
    ],
    [
        'locale' => 'und',
        'options' => new Locale\Options(
            calendar: 'buddhist',
        ),
    ],
    [
        'locale' => 'und',
        'options' => new Locale\Options(
            caseFirst: 'lower',
        ),
    ],
    [
        'locale' => 'und',
        'options' => new Locale\Options(
            caseFirst: 'false',
        ),
    ],
    [
        'locale' => 'und',
        'options' => new Locale\Options(
            collation: 'phonebk',
        ),
    ],
    [
        'locale' => 'und',
        'options' => new Locale\Options(
            hourCycle: 'h11',
        ),
    ],
    [
        'locale' => 'und',
        'options' => new Locale\Options(
            hourCycle: 'h12',
        ),
    ],
    [
        'locale' => 'und',
        'options' => new Locale\Options(
            hourCycle: 'h23',
        ),
    ],
    [
        'locale' => 'und',
        'options' => new Locale\Options(
            hourCycle: 'h24',
        ),
    ],
    [
        'locale' => 'und',
        'options' => new Locale\Options(
            language: 'fr',
        ),
    ],
    [
        'locale' => 'und',
        'options' => new Locale\Options(
            numberingSystem: 'thai',
        ),
    ],
    [
        'locale' => 'und',
        'options' => new Locale\Options(
            numeric: true,
        ),
    ],
    [
        'locale' => 'und',
        'options' => new Locale\Options(
            numeric: false,
        ),
    ],
    [
        'locale' => 'und',
        'options' => new Locale\Options(
            region: 'ES',
        ),
    ],
];

foreach ($tests as $test) {
    $locale = new Locale($test['locale'], $test['options']);
    echo $locale->toString() . "\n";
}
?>
--EXPECT--
en-US
en-US
en-GB
fr-Cyrl-CA
en-Latn-US-u-ca-gregory-co-emoji-hc-h23-kf-upper-kn-nu-latn
und-u-ca-buddhist
und-u-kf-lower
und-u-kf-false
und-u-co-phonebk
und-u-hc-h11
und-u-hc-h12
und-u-hc-h23
und-u-hc-h24
fr
und-u-nu-thai
und-u-kn
und-u-kn-false
und-ES
