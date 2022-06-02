--TEST--
Ecma\Intl\supportedValuesOf('collation')
--EXTENSIONS--
ecma_intl
--FILE--
<?php
$collations = \Ecma\Intl\supportedValuesOf('collation');

if (count($collations) > 0) {
    printf("Has support for %d collations.\n", count($collations));
} else {
    echo "Does not support any collations.\n";
}

var_dump($collations);

$tests = [
    'dict',
    'gb2312',
    'phonebk',
    'trad',
];

foreach ($tests as $test) {
    if (in_array($test, $collations)) {
        printf("Found %s in collation data.\n", $test);
    } else {
        printf("Could not find %s in collation data.\n", $test);
    }
}
?>
--EXPECTF--
Has support for %d collations.
Found dict in collation data.
Found gb2312 in collation data.
Found phonebk in collation data.
Found trad in collation data.
