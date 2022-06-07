--TEST--
Ecma\Intl\Locale minimizes locales
--EXTENSIONS--
ecma_intl
--FILE--
<?php
use Ecma\Intl\Locale;

$tests = [
    'en-Latn-US',
    'de-Latn-DE',
    'sr-Cyrl-RS',
    'zh-Hant-TW',
];

foreach ($tests as $test) {
    $locale = new Locale($test);
    $newLocale = $locale->minimize();
    
    assert($locale !== $newLocale);
    
    echo $newLocale->toString() . "\n";
}

?>
--EXPECT--
en
de
sr
zh-TW
