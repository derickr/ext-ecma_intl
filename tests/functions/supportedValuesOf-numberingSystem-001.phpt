--TEST--
Ecma\Intl\supportedValuesOf('numberingSystem')
--EXTENSIONS--
ecma_intl
--XFAIL--
Pending normalization of numbering system names
--FILE--
<?php
$numberingSystems = \Ecma\Intl\supportedValuesOf('numberingSystem');

if (count($numberingSystems) > 0) {
    printf("Has support for %d numbering systems.\n", count($numberingSystems));
} else {
    echo "Does not support any numbering systems.\n";
}

$tests = [
    'traditio',
];

foreach ($tests as $test) {
    if (in_array($test, $numberingSystems)) {
        printf("Found %s in numbering system data.\n", $test);
    } else {
        printf("Could not find %s in numbering system data.\n", $test);
    }
}
?>
--EXPECTF--
Has support for %d numbering systems.
Found traditio in numbering system data.
