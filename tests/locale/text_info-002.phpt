--TEST--
Ecma\Intl\Locale\WeekInfo reports expected values for various locales
--EXTENSIONS--
ecma_intl
--FILE--
<?php
use Ecma\Intl\Locale;

$tests = [
    'ar',
    'he',
    'fa',
    'en-GB',
    'ur',
];

foreach ($tests as $test) {
    $locale = new Locale($test);
    
    echo json_encode($locale->textInfo, JSON_PRETTY_PRINT);
    echo "\n\n";
}

?>
--EXPECT--
{
    "direction": "rtl"
}

{
    "direction": "rtl"
}

{
    "direction": "rtl"
}

{
    "direction": "ltr"
}

{
    "direction": "rtl"
}
