--TEST--
Ecma\Intl\Locale\WeekDay is a backed enum
--EXTENSIONS--
ecma_intl
--FILE--
<?php
use Ecma\Intl\Locale\WeekDay;

echo WeekDay::Monday->value . "\n";
echo WeekDay::Tuesday->value . "\n";
echo WeekDay::Wednesday->value . "\n";
echo WeekDay::Thursday->value . "\n";
echo WeekDay::Friday->value . "\n";
echo WeekDay::Saturday->value . "\n";
echo WeekDay::Sunday->value . "\n";
?>
--EXPECT--
1
2
3
4
5
6
7
