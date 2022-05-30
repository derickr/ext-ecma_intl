--TEST--
Ecma\Intl\getCanonicalLocales() with array
--EXTENSIONS--
ecma_intl
--FILE--
<?php
var_dump(\Ecma\Intl\getCanonicalLocales(['en-US']));
var_dump(\Ecma\Intl\getCanonicalLocales(['en-US', 'de-DE']));
var_dump(\Ecma\Intl\getCanonicalLocales(['en-US', 'de-DE', 'es-MX', 'fr-FR']));
var_dump(\Ecma\Intl\getCanonicalLocales(['_US', 'und-US', '_Latn', 'und-latn', 'zh-hakka', 'zh-cmn-CH-u-co-pinyin']));
?>
--EXPECT--
array(1) {
  [0]=>
  string(5) "en-US"
}
array(2) {
  [0]=>
  string(5) "en-US"
  [1]=>
  string(5) "de-DE"
}
array(4) {
  [0]=>
  string(5) "en-US"
  [1]=>
  string(5) "de-DE"
  [2]=>
  string(5) "es-MX"
  [3]=>
  string(5) "fr-FR"
}
array(6) {
  [0]=>
  string(6) "und-US"
  [1]=>
  string(6) "und-US"
  [2]=>
  string(8) "und-Latn"
  [3]=>
  string(8) "und-Latn"
  [4]=>
  string(3) "hak"
  [5]=>
  string(18) "cmn-CH-u-co-pinyin"
}
