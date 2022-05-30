--TEST--
Ecma\Intl\Locale initialized properties with basic locale
--EXTENSIONS--
ecma_intl
--FILE--
<?php
$locale = new \Ecma\Intl\Locale('en');

foreach ($locale as $property => $value) {
    echo $property . ' : ' . var_export($value, true) . "\n";
}
?>
--EXPECT--
baseName : 'en'
calendar : NULL
calendars : array (
)
caseFirst : NULL
collation : NULL
hourCycle : NULL
hourCycles : array (
)
language : NULL
numberingSystem : NULL
numberingSystems : array (
)
numeric : false
region : NULL
script : NULL
textInfo : NULL
timeZones : array (
)
weekInfo : NULL
