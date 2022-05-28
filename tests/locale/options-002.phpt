--TEST--
Ecma\Intl\Locale\Options with all valid arguments passed in constructor
--EXTENSIONS--
ecma_intl
--FILE--
<?php
$options = new \Ecma\Intl\Locale\Options(
    calendar: 'gregory',
    caseFirst: 'upper',
    collation: 'emoji',
    hourCycle: 'h24',
    language: 'en',
    numberingSystem: 'latn',
    numeric: true,
    region: 'US',
    script: 'Latn',
);

foreach ($options as $property => $value) {
    echo $property . ' : ' . var_export($value, true) . "\n";
}
?>
--EXPECT--
calendar : 'gregory'
caseFirst : 'upper'
collation : 'emoji'
hourCycle : 'h24'
language : 'en'
numberingSystem : 'latn'
numeric : true
region : 'US'
script : 'Latn'
