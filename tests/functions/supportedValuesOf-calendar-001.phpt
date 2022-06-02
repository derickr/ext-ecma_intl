--TEST--
Ecma\Intl\supportedValuesOf('calendar')
--EXTENSIONS--
ecma_intl
--FILE--
<?php
$calendars = \Ecma\Intl\supportedValuesOf('calendar');

if (count($calendars) > 0) {
    printf("Has support for %d calendars.\n", count($calendars));
} else {
    echo "Does not support any calendars.\n";
}

$tests = [
    'gregory',
    'ethioaa',
];

foreach ($tests as $test) {
    if (in_array($test, $calendars)) {
        printf("Found %s in calendar data.\n", $test);
    } else {
        printf("Could not find %s in calendar data.\n", $test);
    }
}
?>
--EXPECTF--
Has support for %d calendars.
Found gregory in calendar data.
Found ethioaa in calendar data.
