--TEST--
Ecma\Intl\Locale with a full set of preferred options
--EXTENSIONS--
ecma_intl
--FILE--
<?php
$locale = new \Ecma\Intl\Locale('ar', new \Ecma\Intl\Locale\Options(
    calendar: 'dangi',
    caseFirst: 'upper',
    collation: 'phonebk',
    hourCycle: 'h11',
    numberingSystem: 'traditio',
    numeric: true,
    region: 'CA',
    script: 'latn',
));
var_dump($locale);
?>
--EXPECT--
object(Ecma\Intl\Locale)#1 (17) {
  ["baseName"]=>
  string(10) "ar-Latn-CA"
  ["calendar"]=>
  string(5) "dangi"
  ["calendars"]=>
  array(1) {
    [0]=>
    string(5) "dangi"
  }
  ["caseFirst"]=>
  string(5) "upper"
  ["collation"]=>
  string(7) "phonebk"
  ["collations"]=>
  array(1) {
    [0]=>
    string(7) "phonebk"
  }
  ["hourCycle"]=>
  string(3) "h11"
  ["hourCycles"]=>
  array(1) {
    [0]=>
    string(3) "h11"
  }
  ["language"]=>
  string(2) "ar"
  ["numberingSystem"]=>
  string(8) "traditio"
  ["numberingSystems"]=>
  array(1) {
    [0]=>
    string(8) "traditio"
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
  array(29) {
    [0]=>
    string(20) "America/Blanc-Sablon"
    [1]=>
    string(21) "America/Cambridge_Bay"
    [2]=>
    string(21) "America/Coral_Harbour"
    [3]=>
    string(15) "America/Creston"
    [4]=>
    string(14) "America/Dawson"
    [5]=>
    string(20) "America/Dawson_Creek"
    [6]=>
    string(16) "America/Edmonton"
    [7]=>
    string(19) "America/Fort_Nelson"
    [8]=>
    string(17) "America/Glace_Bay"
    [9]=>
    string(17) "America/Goose_Bay"
    [10]=>
    string(15) "America/Halifax"
    [11]=>
    string(14) "America/Inuvik"
    [12]=>
    string(15) "America/Iqaluit"
    [13]=>
    string(15) "America/Moncton"
    [14]=>
    string(16) "America/Montreal"
    [15]=>
    string(15) "America/Nipigon"
    [16]=>
    string(19) "America/Pangnirtung"
    [17]=>
    string(19) "America/Rainy_River"
    [18]=>
    string(20) "America/Rankin_Inlet"
    [19]=>
    string(14) "America/Regina"
    [20]=>
    string(16) "America/Resolute"
    [21]=>
    string(16) "America/St_Johns"
    [22]=>
    string(21) "America/Swift_Current"
    [23]=>
    string(19) "America/Thunder_Bay"
    [24]=>
    string(15) "America/Toronto"
    [25]=>
    string(17) "America/Vancouver"
    [26]=>
    string(18) "America/Whitehorse"
    [27]=>
    string(16) "America/Winnipeg"
    [28]=>
    string(19) "America/Yellowknife"
  }
  ["weekInfo"]=>
  NULL
}
