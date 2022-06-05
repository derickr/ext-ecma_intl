--TEST--
Ecma\Intl\Locale\TextInfo cannot be instantiated by user
--EXTENSIONS--
ecma_intl
--FILE--
<?php
new \Ecma\Intl\Locale\TextInfo();
?>
--EXPECTF--
Fatal error: Uncaught Error: Call to private Ecma\Intl\Locale\TextInfo::__construct() from global scope in %s/tests/locale/text_info-001.php:%d
Stack trace:
#0 {main}
  thrown in %s/tests/locale/text_info-001.php on line %d
