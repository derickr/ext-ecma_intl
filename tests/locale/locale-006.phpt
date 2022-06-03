--TEST--
Ecma\Intl\Locale with populated options
--EXTENSIONS--
ecma_intl
--XFAIL--
Pending normalization of calendar, collation, and numbering system names
--FILE--
<?php
$locale = new \Ecma\Intl\Locale('en', new \Ecma\Intl\Locale\Options(
    calendar: 'gregory',
    caseFirst: 'upper',
    collation: 'standard',
    hourCycle: 'h23',
    numberingSystem: 'thai',
    numeric: true,
    region: 'CA',
    script: 'latn',
));
var_dump($locale);
?>
--EXPECT--
object(Ecma\Intl\Locale)#1 (16) {
  ["baseName"]=>
  string(10) "en-Latn-CA"
  ["calendar"]=>
  string(8) "gregory"
  ["calendars"]=>
  array(1) {
    [0]=>
    string(8) "gregory"
  }
  ["caseFirst"]=>
  string(5) "upper"
  ["collation"]=>
  string(8) "standard"
  ["hourCycle"]=>
  string(3) "h23"
  ["hourCycles"]=>
  array(1) {
    [0]=>
    string(3) "h23"
  }
  ["language"]=>
  string(2) "en"
  ["numberingSystem"]=>
  string(4) "thai"
  ["numberingSystems"]=>
  array(0) {
  }
  ["numeric"]=>
  bool(true)
  ["region"]=>
  string(2) "CA"
  ["script"]=>
  string(4) "Latn"
  ["textInfo"]=>
  NULL
  ["timeZones"]=>
  array(0) {
  }
  ["weekInfo"]=>
  NULL
}
