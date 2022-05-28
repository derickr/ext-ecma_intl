/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: d92faa6a92a942bfb4da311afd0b6a89a8b0c990 */

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Ecma_Intl_Locale_WeekInfo___construct, 0, 0, 0)
ZEND_END_ARG_INFO()


ZEND_METHOD(Ecma_Intl_Locale_WeekInfo, __construct);


static const zend_function_entry class_Ecma_Intl_Locale_WeekInfo_methods[] = {
	ZEND_ME(Ecma_Intl_Locale_WeekInfo, __construct, arginfo_class_Ecma_Intl_Locale_WeekInfo___construct, ZEND_ACC_PRIVATE)
	ZEND_FE_END
};

static zend_class_entry *register_class_Ecma_Intl_Locale_WeekInfo(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Ecma\\Intl\\Locale", "WeekInfo", class_Ecma_Intl_Locale_WeekInfo_methods);
	class_entry = zend_register_internal_class_ex(&ce, NULL);
	class_entry->ce_flags |= ZEND_ACC_FINAL;

	zval property_firstDay_default_value;
	ZVAL_UNDEF(&property_firstDay_default_value);
	zend_string *property_firstDay_name = zend_string_init("firstDay", sizeof("firstDay") - 1, 1);
	zend_declare_typed_property(class_entry, property_firstDay_name, &property_firstDay_default_value, ZEND_ACC_PUBLIC|ZEND_ACC_READONLY, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_firstDay_name);

	zval property_weekend_default_value;
	ZVAL_UNDEF(&property_weekend_default_value);
	zend_string *property_weekend_name = zend_string_init("weekend", sizeof("weekend") - 1, 1);
	zend_declare_typed_property(class_entry, property_weekend_name, &property_weekend_default_value, ZEND_ACC_PUBLIC|ZEND_ACC_READONLY, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_ARRAY));
	zend_string_release(property_weekend_name);

	zval property_minimalDays_default_value;
	ZVAL_UNDEF(&property_minimalDays_default_value);
	zend_string *property_minimalDays_name = zend_string_init("minimalDays", sizeof("minimalDays") - 1, 1);
	zend_declare_typed_property(class_entry, property_minimalDays_name, &property_minimalDays_default_value, ZEND_ACC_PUBLIC|ZEND_ACC_READONLY, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_minimalDays_name);

	return class_entry;
}
