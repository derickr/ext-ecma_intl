--TEST--
Ecma\Intl\Locale initialized properties with basic locale
--EXTENSIONS--
ecma_intl
--FILE--
<?php
$locale = new \Ecma\Intl\Locale('en');
var_dump($locale);
?>
--EXPECTF--
object(Ecma\Intl\Locale)#%d (17) {
  ["baseName"]=>
  string(2) "en"
  ["calendar"]=>
  NULL
  ["calendars"]=>
  array(1) {
    [0]=>
    string(7) "gregory"
  }
  ["caseFirst"]=>
  NULL
  ["collation"]=>
  NULL
  ["collations"]=>
  array(2) {
    [0]=>
    string(5) "emoji"
    [1]=>
    string(3) "eor"
  }
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
  array(1) {
    [0]=>
    string(4) "latn"
  }
  ["numeric"]=>
  bool(false)
  ["region"]=>
  NULL
  ["script"]=>
  NULL
  ["textInfo"]=>
  object(Ecma\Intl\Locale\TextInfo)#%d (1) {
    ["direction"]=>
    enum(Ecma\Intl\Locale\TextDirection::LeftToRight)
  }
  ["timeZones"]=>
  NULL
  ["weekInfo"]=>
  NULL
}
