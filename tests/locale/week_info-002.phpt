--TEST--
Ecma\Intl\Locale\WeekInfo reports expected values for various locales
--EXTENSIONS--
ecma_intl
--FILE--
<?php
use Ecma\Intl\Locale;

$tests = [
    'he',
    'af',
    'en-GB',
    'hi-IN',
];

foreach ($tests as $test) {
    $locale = new Locale($test);
    
    echo json_encode($locale->weekInfo, JSON_PRETTY_PRINT);
    echo "\n\n";
}

?>
--EXPECT--
{
    "firstDay": 7,
    "minimalDays": 1,
    "weekend": [
        5,
        6
    ]
}

{
    "firstDay": 7,
    "minimalDays": 1,
    "weekend": [
        6,
        7
    ]
}

{
    "firstDay": 1,
    "minimalDays": 4,
    "weekend": [
        6,
        7
    ]
}

{
    "firstDay": 7,
    "minimalDays": 1,
    "weekend": [
        7
    ]
}
