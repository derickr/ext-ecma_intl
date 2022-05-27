--TEST--
Check Ecma\Intl\RangeError is a child of \ValueError
--EXTENSIONS--
ecma_intl
--FILE--
<?php
echo \Ecma\Intl\RangeError::class . "\n";
echo get_parent_class(\Ecma\Intl\RangeError::class) . "\n";
var_dump(is_subclass_of(\Ecma\Intl\RangeError::class, \Ecma\Intl\IntlException::class));
?>
--EXPECT--
Ecma\Intl\RangeError
ValueError
bool(true)
