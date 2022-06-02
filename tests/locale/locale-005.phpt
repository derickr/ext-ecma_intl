--TEST--
Ecma\Intl\Locale throws exceptions for invalid values
--EXTENSIONS--
ecma_intl
--FILE--
<?php
use Ecma\Intl\Locale;

$tests = [
    [
        'locale' => 'invalid tag',
        'options' => null,
    ],
    [
        'locale' => 'invalid tag',
        'options' => new Locale\Options(),
    ],
    [
        'locale' => '',
        'options' => null,
    ],
    [
        'locale' => '',
        'options' => new Locale\Options(),
    ],
    [
        'locale' => 'en',
        'options' => new Locale\Options(
            calendar: 'invalid calendar',
        ),
    ],
    [
        'locale' => 'und',
        'options' => new Locale\Options(
            calendar: '',
        ),
    ],
    [
        'locale' => 'en',
        'options' => new Locale\Options(
            caseFirst: 'invalid',
        ),
    ],
    [
        'locale' => 'und',
        'options' => new Locale\Options(
            caseFirst: '',
        ),
    ],
    [
        'locale' => 'en',
        'options' => new Locale\Options(
            collation: 'invalid collation',
        ),
    ],
    [
        'locale' => 'und',
        'options' => new Locale\Options(
            collation: '',
        ),
    ],
    [
        'locale' => 'en',
        'options' => new Locale\Options(
            hourCycle: 'invalid',
        ),
    ],
    [
        'locale' => 'und',
        'options' => new Locale\Options(
            hourCycle: '',
        ),
    ],
    [
        'locale' => 'en',
        'options' => new Locale\Options(
            language: 'invalid language',
        ),
    ],
    [
        'locale' => 'und',
        'options' => new Locale\Options(
            language: '',
        ),
    ],
    [
        'locale' => 'en',
        'options' => new Locale\Options(
            numberingSystem: 'invalid system',
        ),
    ],
    [
        'locale' => 'und',
        'options' => new Locale\Options(
            numberingSystem: '',
        ),
    ],
    [
        'locale' => 'en',
        'options' => new Locale\Options(
             region: 'Great Britain',
        ),
    ],
    [
        'locale' => 'und',
        'options' => new Locale\Options(
            region: '',
        ),
    ],
    [
        'locale' => 'en',
        'options' => new Locale\Options(
            script: 'invalid',
        ),
    ],
    [
        'locale' => 'und',
        'options' => new Locale\Options(
            script: '',
        ),
    ],
];

foreach ($tests as $test) {
    try {
        new Locale($test['locale'], $test['options']);
    } catch (\Throwable $t) {
        echo $t::class . ': ' . $t->getMessage() . "\n";
        continue;
    }

    echo "Did not catch exception for test with value: \n";
    var_dump($test);
}
?>
--EXPECT--
Ecma\Intl\RangeError: invalid language tag
Ecma\Intl\RangeError: invalid language tag
Ecma\Intl\RangeError: invalid language tag
Ecma\Intl\RangeError: invalid language tag
Ecma\Intl\RangeError: calendar is not a well-formed calendar value
Ecma\Intl\RangeError: calendar is not a well-formed calendar value
Ecma\Intl\RangeError: caseFirst must be either "upper", "lower", or "false"
Ecma\Intl\RangeError: caseFirst must be either "upper", "lower", or "false"
Ecma\Intl\RangeError: collation is not a well-formed collation value
Ecma\Intl\RangeError: collation is not a well-formed collation value
Ecma\Intl\RangeError: hourCycle must be "h11", "h12", "h23", or "h24"
Ecma\Intl\RangeError: hourCycle must be "h11", "h12", "h23", or "h24"
Ecma\Intl\RangeError: language is not a well-formed language value
Ecma\Intl\RangeError: language is not a well-formed language value
Ecma\Intl\RangeError: numberingSystem is not a well-formed numbering system value
Ecma\Intl\RangeError: numberingSystem is not a well-formed numbering system value
Ecma\Intl\RangeError: region is not a well-formed region value
Ecma\Intl\RangeError: region is not a well-formed region value
Ecma\Intl\RangeError: script is not a well-formed script value
Ecma\Intl\RangeError: script is not a well-formed script value
