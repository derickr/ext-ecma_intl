--TEST--
Ecma\Intl\Locale initialized properties with basic locale
--EXTENSIONS--
ecma_intl
--XFAIL--
Pending normalization of calendar, collation, and numbering system names
--FILE--
<?php
$locale = new \Ecma\Intl\Locale('en');
var_dump($locale);
?>
--EXPECT--
object(Ecma\Intl\Locale)#1 (16) {
  ["baseName"]=>
  string(2) "en"
  ["calendar"]=>
  NULL
  ["calendars"]=>
  array(1) {
    [0]=>
    string(8) "gregory"
  }
  ["caseFirst"]=>
  NULL
  ["collation"]=>
  NULL
  ["hourCycle"]=>
  NULL
  ["hourCycles"]=>
  array(1) {
    [0]=>
    string(3) "h12"
  }
  ["language"]=>
  string(2) "en"
  ["numberingSystem"]=>
  NULL
  ["numberingSystems"]=>
  array(0) {
  }
  ["numeric"]=>
  bool(false)
  ["region"]=>
  NULL
  ["script"]=>
  NULL
  ["textInfo"]=>
  NULL
  ["timeZones"]=>
  array(0) {
  }
  ["weekInfo"]=>
  NULL
}
