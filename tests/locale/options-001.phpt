--TEST--
Ecma\Intl\Locale\Options with nothing passed in constructor
--EXTENSIONS--
ecma_intl
--FILE--
<?php
$options = new \Ecma\Intl\Locale\Options();

foreach ($options as $property => $value) {
    echo $property . ' : ' . var_export($value, true) . "\n";
}
?>
--EXPECT--
calendar : NULL
caseFirst : NULL
collation : NULL
hourCycle : NULL
language : NULL
numberingSystem : NULL
numeric : NULL
region : NULL
script : NULL
