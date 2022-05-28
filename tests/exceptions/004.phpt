--TEST--
Instantiate Ecma\Intl\RangeError
--EXTENSIONS--
ecma_intl
--FILE--
<?php
var_export(new \Ecma\Intl\RangeError('A test message', 42));
?>
--EXPECTF--
Ecma\Intl\RangeError::__set_state(array(
   'message' => 'A test message',
   'string' => '',
   'code' => 42,
   'file' => '%s/tests/exceptions/004.php',
   'line' => %d,
   'trace' => 
  array (
  ),
   'previous' => NULL,
))
