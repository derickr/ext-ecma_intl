--TEST--
Instantiate Ecma\Intl\IcuException
--EXTENSIONS--
ecma_intl
--FILE--
<?php
var_export(new \Ecma\Intl\IcuException('This is a test', 36));
?>
--EXPECTF--
Ecma\Intl\IcuException::__set_state(array(
   'message' => 'This is a test',
   'string' => '',
   'code' => 36,
   'file' => '%s/tests/exceptions/003.php',
   'line' => %d,
   'trace' => 
  array (
  ),
   'previous' => NULL,
))
