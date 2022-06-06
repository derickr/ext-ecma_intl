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

echo json_encode($locale, JSON_PRETTY_PRINT);
echo "\n";
?>
--EXPECTF--
{
    "baseName": "ar-Latn-CA",
    "calendar": "dangi",
    "calendars": [
        "dangi"
    ],
    "caseFirst": "upper",
    "collation": "phonebk",
    "collations": [
        "phonebk"
    ],
    "hourCycle": "h11",
    "hourCycles": [
        "h11"
    ],
    "language": "ar",
    "numberingSystem": "traditio",
    "numberingSystems": [
        "traditio"
    ],
    "numeric": true,
    "region": "CA",
    "script": "Latn",
    "textInfo": {
        "direction": "rtl"
    },
    "timeZones": [
        "America\/Blanc-Sablon",
        "America\/Cambridge_Bay",
        "America\/Coral_Harbour",
        "America\/Creston",
        "America\/Dawson",
        "America\/Dawson_Creek",
        "America\/Edmonton",
        "America\/Fort_Nelson",
        "America\/Glace_Bay",
        "America\/Goose_Bay",
        "America\/Halifax",
        "America\/Inuvik",
        "America\/Iqaluit",
        "America\/Moncton",
        "America\/Montreal",
        "America\/Nipigon",
        "America\/Pangnirtung",
        "America\/Rainy_River",
        "America\/Rankin_Inlet",
        "America\/Regina",
        "America\/Resolute",
        "America\/St_Johns",
        "America\/Swift_Current",
        "America\/Thunder_Bay",
        "America\/Toronto",
        "America\/Vancouver",
        "America\/Whitehorse",
        "America\/Winnipeg",
        "America\/Yellowknife"
    ],
    "weekInfo": {
        "firstDay": 7,
        "minimalDays": 1,
        "weekend": [
            6,
            7
        ]
    }
}
