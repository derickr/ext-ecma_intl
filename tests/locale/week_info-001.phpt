--TEST--
Ecma\Intl\Locale\WeekInfo cannot be instantiated by user
--EXTENSIONS--
ecma_intl
--FILE--
<?php
new \Ecma\Intl\Locale\WeekInfo();
?>
--EXPECTF--
Fatal error: Uncaught Error: Call to private Ecma\Intl\Locale\WeekInfo::__construct() from global scope in %s/tests/locale/week_info-001.php:%d
Stack trace:
#0 {main}
  thrown in %s/tests/locale/week_info-001.php on line %d
