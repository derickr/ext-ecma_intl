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
Invalid language tag: ""
Invalid language tag: "de-de_euro"
Invalid language tag: "123"
Invalid language tag: "en-latn-x"
Invalid language tag: "zh-cmn-CH"
Invalid language tag: "i-test"
Invalid language tag: "ja-jp-jp"
Invalid language tag: "boguslang"
Invalid language tag: "und-varzero-var1-vartwo"
Invalid language tag: "de-1901-1901"
Invalid language tag: "de-DE-1901-1901"
Invalid language tag: "hant-cmn-cn"
Invalid language tag: "zh-cmn-TW"
Invalid language tag: "en-gb-oed"
