--TEST--
Check Ecma\Intl\IcuException is a child of \RuntimeException
--EXTENSIONS--
ecma_intl
--FILE--
<?php
echo \Ecma\Intl\IcuException::class . "\n";
echo get_parent_class(\Ecma\Intl\IcuException::class) . "\n";
var_dump(is_subclass_of(\Ecma\Intl\IcuException::class, \Ecma\Intl\IntlException::class));
?>
--EXPECT--
Ecma\Intl\IcuException
RuntimeException
bool(true)
