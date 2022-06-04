--TEST--
Ecma\Intl\Locale with populated options
--EXTENSIONS--
ecma_intl
--FILE--
<?php
$locale = new \Ecma\Intl\Locale('ar', new \Ecma\Intl\Locale\Options(
    calendar: 'gregory',
    caseFirst: 'upper',
    collation: 'phonebk',
    hourCycle: 'h23',
    numberingSystem: 'traditio',
    numeric: true,
    region: 'CA',
    script: 'latn',
));
var_dump($locale);
?>
--EXPECT--
object(Ecma\Intl\Locale)#1 (16) {
  ["baseName"]=>
  string(10) "ar-Latn-CA"
  ["calendar"]=>
  string(7) "gregory"
  ["calendars"]=>
  array(1) {
    [0]=>
    string(7) "gregory"
  }
  ["caseFirst"]=>
  string(5) "upper"
  ["collation"]=>
  string(7) "phonebk"
  ["hourCycle"]=>
  string(3) "h23"
  ["hourCycles"]=>
  array(1) {
    [0]=>
    string(3) "h23"
  }
  ["language"]=>
  string(2) "ar"
  ["numberingSystem"]=>
  string(8) "traditio"
  ["numberingSystems"]=>
  array(1) {
    [0]=>
    string(4) "arab"
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
