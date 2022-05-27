/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: bd299494e39fb716130c0bb925e14ec96a0385f7 */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_Ecma_Intl_getCanonicalLocales, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_MASK(0, locales, MAY_BE_ARRAY|MAY_BE_STRING, NULL)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_Ecma_Intl_getSupportedLocales, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_Ecma_Intl_supportedValuesOf, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
ZEND_END_ARG_INFO()


ZEND_FUNCTION(getCanonicalLocales);
ZEND_FUNCTION(getSupportedLocales);
ZEND_FUNCTION(supportedValuesOf);


static const zend_function_entry ext_functions[] = {
	ZEND_NS_FE("Ecma\\Intl", getCanonicalLocales, arginfo_Ecma_Intl_getCanonicalLocales)
	ZEND_NS_FE("Ecma\\Intl", getSupportedLocales, arginfo_Ecma_Intl_getSupportedLocales)
	ZEND_NS_FE("Ecma\\Intl", supportedValuesOf, arginfo_Ecma_Intl_supportedValuesOf)
	ZEND_FE_END
};
