--TEST--
Ecma\Intl\Locale maximizes locales
--EXTENSIONS--
ecma_intl
--FILE--
<?php
use Ecma\Intl\Locale;

$tests = [
    'en',
    'de',
    'sr',
    'zh_Hans',
];

foreach ($tests as $test) {
    $locale = new Locale($test);
    $newLocale = $locale->maximize();
    
    assert($locale !== $newLocale);
    
    echo $newLocale->toString() . "\n";
}

?>
--EXPECT--
en-Latn-US
de-Latn-DE
sr-Cyrl-RS
zh-Hans-CN
