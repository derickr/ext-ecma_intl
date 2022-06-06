--TEST--
Ecma\Intl\Locale\TextDirection is a backed enum
--EXTENSIONS--
ecma_intl
--FILE--
<?php
use Ecma\Intl\Locale\TextDirection;

echo TextDirection::LeftToRight->value . "\n";
echo TextDirection::RightToLeft->value . "\n";
echo TextDirection::TopToBottom->value . "\n";
echo TextDirection::BottomToTop->value . "\n";
?>
--EXPECT--
ltr
rtl
ttb
btt
