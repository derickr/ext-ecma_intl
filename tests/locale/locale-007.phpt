--TEST--
Ecma\Intl\Locale prints out different time zones for various regions
--EXTENSIONS--
ecma_intl
--FILE--
<?php
use Ecma\Intl\Locale;

$tests = [
    'he',
    'en-GB',
    'hi-IN',
];

foreach ($tests as $test) {
    $locale = new Locale($test);
    
    echo json_encode($locale->timeZones, JSON_PRETTY_PRINT);
    echo "\n\n";
}

?>
--EXPECT--
null

[
    "Europe\/London"
]

[
    "Asia\/Calcutta"
]
