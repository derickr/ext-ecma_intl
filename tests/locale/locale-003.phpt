--TEST--
Ecma\Intl\Locale throws exceptions for invalid language tags
--EXTENSIONS--
ecma_intl
--FILE--
<?php
$tests = [
    '',
    'de-de_euro',
    '123',
    'en-latn-x',
    'zh-cmn-CH',
    'i-test',
    'ja-jp-jp',
    'boguslang',
    'und-varzero-var1-vartwo',
    'de-1901-1901',
    'de-DE-1901-1901',
    'hant-cmn-cn',
    'zh-cmn-TW',
    'en-gb-oed',
];

foreach ($tests as $test) {
    try {
        new \Ecma\Intl\Locale($test);
        echo "test failed: $test\n";
    } catch (\Ecma\Intl\RangeError $error) {
        echo $error->getMessage() . "\n";
    }
}
?>
--EXPECTF--
invalid language tag
invalid language tag
invalid language tag
invalid language tag
invalid language tag
invalid language tag
invalid language tag
invalid language tag
invalid language tag
invalid language tag
invalid language tag
invalid language tag
invalid language tag
invalid language tag
