--TEST--
Ecma\Intl\Locale initialized properties with basic locale
--EXTENSIONS--
ecma_intl
--FILE--
<?php
$locale = new \Ecma\Intl\Locale('en');

echo json_encode($locale, JSON_PRETTY_PRINT);
echo "\n";
?>
--EXPECTF--
{
    "baseName": "en",
    "calendar": null,
    "calendars": [
        "gregory"
    ],
    "caseFirst": null,
    "collation": null,
    "collations": [
        "emoji",
        "eor"
    ],
    "hourCycle": null,
    "hourCycles": [
        "h12"
    ],
    "language": "en",
    "numberingSystem": null,
    "numberingSystems": [
        "latn"
    ],
    "numeric": false,
    "region": null,
    "script": null,
    "textInfo": {
        "direction": "ltr"
    },
    "timeZones": null,
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}
