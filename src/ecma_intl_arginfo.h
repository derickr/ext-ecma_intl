/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 261b73c19c283167ce7f72670617b4003aae0cc4 */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_Ecma_Intl_getCanonicalLocales, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_MASK(0, locales, MAY_BE_ARRAY|MAY_BE_STRING, NULL)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_Ecma_Intl_getSupportedLocales, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_Ecma_Intl_supportedValuesOf, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Ecma_Intl_Locale___construct, 0, 0, 1)
	ZEND_ARG_TYPE_INFO(0, tag, IS_STRING, 0)
	ZEND_ARG_OBJ_INFO_WITH_DEFAULT_VALUE(0, options, Ecma\\Intl\\Locale\\Options, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Ecma_Intl_Locale_maximize, 0, 0, Ecma\\Intl\\Locale, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Ecma_Intl_Locale_minimize arginfo_class_Ecma_Intl_Locale_maximize

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Ecma_Intl_Locale_toString, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Ecma_Intl_Locale___toString arginfo_class_Ecma_Intl_Locale_toString

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Ecma_Intl_Locale_Options___construct, 0, 0, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, calendar, IS_STRING, 1, "null")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, caseFirst, IS_STRING, 1, "null")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, collation, IS_STRING, 1, "null")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, hourCycle, IS_STRING, 1, "null")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, language, IS_STRING, 1, "null")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, numberingSystem, IS_STRING, 1, "null")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, numeric, _IS_BOOL, 1, "null")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, region, IS_STRING, 1, "null")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, script, IS_STRING, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Ecma_Intl_Locale_WeekInfo___construct, 0, 0, 0)
ZEND_END_ARG_INFO()


ZEND_FUNCTION(getCanonicalLocales);
ZEND_FUNCTION(getSupportedLocales);
ZEND_FUNCTION(supportedValuesOf);
ZEND_METHOD(Ecma_Intl_Locale, __construct);
ZEND_METHOD(Ecma_Intl_Locale, maximize);
ZEND_METHOD(Ecma_Intl_Locale, minimize);
ZEND_METHOD(Ecma_Intl_Locale, __toString);
ZEND_METHOD(Ecma_Intl_Locale_Options, __construct);
ZEND_METHOD(Ecma_Intl_Locale_WeekInfo, __construct);


static const zend_function_entry ext_functions[] = {
	ZEND_NS_FE("Ecma\\Intl", getCanonicalLocales, arginfo_Ecma_Intl_getCanonicalLocales)
	ZEND_NS_FE("Ecma\\Intl", getSupportedLocales, arginfo_Ecma_Intl_getSupportedLocales)
	ZEND_NS_FE("Ecma\\Intl", supportedValuesOf, arginfo_Ecma_Intl_supportedValuesOf)
	ZEND_FE_END
};


static const zend_function_entry class_Ecma_Intl_IntlException_methods[] = {
	ZEND_FE_END
};


static const zend_function_entry class_Ecma_Intl_IcuException_methods[] = {
	ZEND_FE_END
};


static const zend_function_entry class_Ecma_Intl_RangeError_methods[] = {
	ZEND_FE_END
};


static const zend_function_entry class_Ecma_Intl_Locale_methods[] = {
	ZEND_ME(Ecma_Intl_Locale, __construct, arginfo_class_Ecma_Intl_Locale___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(Ecma_Intl_Locale, maximize, arginfo_class_Ecma_Intl_Locale_maximize, ZEND_ACC_PUBLIC)
	ZEND_ME(Ecma_Intl_Locale, minimize, arginfo_class_Ecma_Intl_Locale_minimize, ZEND_ACC_PUBLIC)
	ZEND_MALIAS(Ecma_Intl_Locale, toString, __toString, arginfo_class_Ecma_Intl_Locale_toString, ZEND_ACC_PUBLIC)
	ZEND_ME(Ecma_Intl_Locale, __toString, arginfo_class_Ecma_Intl_Locale___toString, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_Ecma_Intl_Locale_Options_methods[] = {
	ZEND_ME(Ecma_Intl_Locale_Options, __construct, arginfo_class_Ecma_Intl_Locale_Options___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_Ecma_Intl_Locale_WeekInfo_methods[] = {
	ZEND_ME(Ecma_Intl_Locale_WeekInfo, __construct, arginfo_class_Ecma_Intl_Locale_WeekInfo___construct, ZEND_ACC_PRIVATE)
	ZEND_FE_END
};

static zend_class_entry *register_class_Ecma_Intl_IntlException(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Ecma\\Intl", "IntlException", class_Ecma_Intl_IntlException_methods);
	class_entry = zend_register_internal_interface(&ce);

	return class_entry;
}

static zend_class_entry *register_class_Ecma_Intl_IcuException(zend_class_entry *class_entry_RuntimeException, zend_class_entry *class_entry_Ecma_Intl_IntlException)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Ecma\\Intl", "IcuException", class_Ecma_Intl_IcuException_methods);
	class_entry = zend_register_internal_class_ex(&ce, class_entry_RuntimeException);
	zend_class_implements(class_entry, 1, class_entry_Ecma_Intl_IntlException);

	return class_entry;
}

static zend_class_entry *register_class_Ecma_Intl_RangeError(zend_class_entry *class_entry_ValueError, zend_class_entry *class_entry_Ecma_Intl_IntlException)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Ecma\\Intl", "RangeError", class_Ecma_Intl_RangeError_methods);
	class_entry = zend_register_internal_class_ex(&ce, class_entry_ValueError);
	zend_class_implements(class_entry, 1, class_entry_Ecma_Intl_IntlException);

	return class_entry;
}

static zend_class_entry *register_class_Ecma_Intl_Locale(zend_class_entry *class_entry_Stringable)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Ecma\\Intl", "Locale", class_Ecma_Intl_Locale_methods);
	class_entry = zend_register_internal_class_ex(&ce, NULL);
	zend_class_implements(class_entry, 1, class_entry_Stringable);

	zval property_baseName_default_value;
	ZVAL_UNDEF(&property_baseName_default_value);
	zend_string *property_baseName_name = zend_string_init("baseName", sizeof("baseName") - 1, 1);
	zend_declare_typed_property(class_entry, property_baseName_name, &property_baseName_default_value, ZEND_ACC_PUBLIC|ZEND_ACC_READONLY, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_STRING));
	zend_string_release(property_baseName_name);

	zval property_calendar_default_value;
	ZVAL_UNDEF(&property_calendar_default_value);
	zend_string *property_calendar_name = zend_string_init("calendar", sizeof("calendar") - 1, 1);
	zend_declare_typed_property(class_entry, property_calendar_name, &property_calendar_default_value, ZEND_ACC_PUBLIC|ZEND_ACC_READONLY, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_STRING|MAY_BE_NULL));
	zend_string_release(property_calendar_name);

	zval property_calendars_default_value;
	ZVAL_UNDEF(&property_calendars_default_value);
	zend_string *property_calendars_name = zend_string_init("calendars", sizeof("calendars") - 1, 1);
	zend_declare_typed_property(class_entry, property_calendars_name, &property_calendars_default_value, ZEND_ACC_PUBLIC|ZEND_ACC_READONLY, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_ARRAY));
	zend_string_release(property_calendars_name);

	zval property_caseFirst_default_value;
	ZVAL_UNDEF(&property_caseFirst_default_value);
	zend_string *property_caseFirst_name = zend_string_init("caseFirst", sizeof("caseFirst") - 1, 1);
	zend_declare_typed_property(class_entry, property_caseFirst_name, &property_caseFirst_default_value, ZEND_ACC_PUBLIC|ZEND_ACC_READONLY, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_STRING|MAY_BE_NULL));
	zend_string_release(property_caseFirst_name);

	zval property_collation_default_value;
	ZVAL_UNDEF(&property_collation_default_value);
	zend_string *property_collation_name = zend_string_init("collation", sizeof("collation") - 1, 1);
	zend_declare_typed_property(class_entry, property_collation_name, &property_collation_default_value, ZEND_ACC_PUBLIC|ZEND_ACC_READONLY, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_STRING|MAY_BE_NULL));
	zend_string_release(property_collation_name);

	zval property_collations_default_value;
	ZVAL_UNDEF(&property_collations_default_value);
	zend_string *property_collations_name = zend_string_init("collations", sizeof("collations") - 1, 1);
	zend_declare_typed_property(class_entry, property_collations_name, &property_collations_default_value, ZEND_ACC_PUBLIC|ZEND_ACC_READONLY, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_ARRAY));
	zend_string_release(property_collations_name);

	zval property_hourCycle_default_value;
	ZVAL_UNDEF(&property_hourCycle_default_value);
	zend_string *property_hourCycle_name = zend_string_init("hourCycle", sizeof("hourCycle") - 1, 1);
	zend_declare_typed_property(class_entry, property_hourCycle_name, &property_hourCycle_default_value, ZEND_ACC_PUBLIC|ZEND_ACC_READONLY, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_STRING|MAY_BE_NULL));
	zend_string_release(property_hourCycle_name);

	zval property_hourCycles_default_value;
	ZVAL_UNDEF(&property_hourCycles_default_value);
	zend_string *property_hourCycles_name = zend_string_init("hourCycles", sizeof("hourCycles") - 1, 1);
	zend_declare_typed_property(class_entry, property_hourCycles_name, &property_hourCycles_default_value, ZEND_ACC_PUBLIC|ZEND_ACC_READONLY, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_ARRAY));
	zend_string_release(property_hourCycles_name);

	zval property_language_default_value;
	ZVAL_UNDEF(&property_language_default_value);
	zend_string *property_language_name = zend_string_init("language", sizeof("language") - 1, 1);
	zend_declare_typed_property(class_entry, property_language_name, &property_language_default_value, ZEND_ACC_PUBLIC|ZEND_ACC_READONLY, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_STRING|MAY_BE_NULL));
	zend_string_release(property_language_name);

	zval property_numberingSystem_default_value;
	ZVAL_UNDEF(&property_numberingSystem_default_value);
	zend_string *property_numberingSystem_name = zend_string_init("numberingSystem", sizeof("numberingSystem") - 1, 1);
	zend_declare_typed_property(class_entry, property_numberingSystem_name, &property_numberingSystem_default_value, ZEND_ACC_PUBLIC|ZEND_ACC_READONLY, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_STRING|MAY_BE_NULL));
	zend_string_release(property_numberingSystem_name);

	zval property_numberingSystems_default_value;
	ZVAL_UNDEF(&property_numberingSystems_default_value);
	zend_string *property_numberingSystems_name = zend_string_init("numberingSystems", sizeof("numberingSystems") - 1, 1);
	zend_declare_typed_property(class_entry, property_numberingSystems_name, &property_numberingSystems_default_value, ZEND_ACC_PUBLIC|ZEND_ACC_READONLY, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_ARRAY));
	zend_string_release(property_numberingSystems_name);

	zval property_numeric_default_value;
	ZVAL_UNDEF(&property_numeric_default_value);
	zend_string *property_numeric_name = zend_string_init("numeric", sizeof("numeric") - 1, 1);
	zend_declare_typed_property(class_entry, property_numeric_name, &property_numeric_default_value, ZEND_ACC_PUBLIC|ZEND_ACC_READONLY, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_BOOL));
	zend_string_release(property_numeric_name);

	zval property_region_default_value;
	ZVAL_UNDEF(&property_region_default_value);
	zend_string *property_region_name = zend_string_init("region", sizeof("region") - 1, 1);
	zend_declare_typed_property(class_entry, property_region_name, &property_region_default_value, ZEND_ACC_PUBLIC|ZEND_ACC_READONLY, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_STRING|MAY_BE_NULL));
	zend_string_release(property_region_name);

	zval property_script_default_value;
	ZVAL_UNDEF(&property_script_default_value);
	zend_string *property_script_name = zend_string_init("script", sizeof("script") - 1, 1);
	zend_declare_typed_property(class_entry, property_script_name, &property_script_default_value, ZEND_ACC_PUBLIC|ZEND_ACC_READONLY, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_STRING|MAY_BE_NULL));
	zend_string_release(property_script_name);

	zval property_textInfo_default_value;
	ZVAL_NULL(&property_textInfo_default_value);
	zend_string *property_textInfo_name = zend_string_init("textInfo", sizeof("textInfo") - 1, 1);
	zend_declare_typed_property(class_entry, property_textInfo_name, &property_textInfo_default_value, ZEND_ACC_PUBLIC|ZEND_ACC_READONLY, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_STRING|MAY_BE_NULL));
	zend_string_release(property_textInfo_name);

	zval property_timeZones_default_value;
	ZVAL_UNDEF(&property_timeZones_default_value);
	zend_string *property_timeZones_name = zend_string_init("timeZones", sizeof("timeZones") - 1, 1);
	zend_declare_typed_property(class_entry, property_timeZones_name, &property_timeZones_default_value, ZEND_ACC_PUBLIC|ZEND_ACC_READONLY, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_ARRAY|MAY_BE_NULL));
	zend_string_release(property_timeZones_name);

	zend_string *property_weekInfo_class_Ecma_Intl_Locale_WeekInfo = zend_string_init("Ecma\\Intl\\Locale\\WeekInfo", sizeof("Ecma\\Intl\\Locale\\WeekInfo")-1, 1);
	zval property_weekInfo_default_value;
	ZVAL_NULL(&property_weekInfo_default_value);
	zend_string *property_weekInfo_name = zend_string_init("weekInfo", sizeof("weekInfo") - 1, 1);
	zend_declare_typed_property(class_entry, property_weekInfo_name, &property_weekInfo_default_value, ZEND_ACC_PUBLIC|ZEND_ACC_READONLY, NULL, (zend_type) ZEND_TYPE_INIT_CLASS(property_weekInfo_class_Ecma_Intl_Locale_WeekInfo, 0, MAY_BE_NULL));
	zend_string_release(property_weekInfo_name);

	return class_entry;
}

static zend_class_entry *register_class_Ecma_Intl_Locale_Options(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Ecma\\Intl\\Locale", "Options", class_Ecma_Intl_Locale_Options_methods);
	class_entry = zend_register_internal_class_ex(&ce, NULL);

	zval property_calendar_default_value;
	ZVAL_NULL(&property_calendar_default_value);
	zend_string *property_calendar_name = zend_string_init("calendar", sizeof("calendar") - 1, 1);
	zend_declare_typed_property(class_entry, property_calendar_name, &property_calendar_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_STRING|MAY_BE_NULL));
	zend_string_release(property_calendar_name);

	zval property_caseFirst_default_value;
	ZVAL_NULL(&property_caseFirst_default_value);
	zend_string *property_caseFirst_name = zend_string_init("caseFirst", sizeof("caseFirst") - 1, 1);
	zend_declare_typed_property(class_entry, property_caseFirst_name, &property_caseFirst_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_STRING|MAY_BE_NULL));
	zend_string_release(property_caseFirst_name);

	zval property_collation_default_value;
	ZVAL_NULL(&property_collation_default_value);
	zend_string *property_collation_name = zend_string_init("collation", sizeof("collation") - 1, 1);
	zend_declare_typed_property(class_entry, property_collation_name, &property_collation_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_STRING|MAY_BE_NULL));
	zend_string_release(property_collation_name);

	zval property_hourCycle_default_value;
	ZVAL_NULL(&property_hourCycle_default_value);
	zend_string *property_hourCycle_name = zend_string_init("hourCycle", sizeof("hourCycle") - 1, 1);
	zend_declare_typed_property(class_entry, property_hourCycle_name, &property_hourCycle_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_STRING|MAY_BE_NULL));
	zend_string_release(property_hourCycle_name);

	zval property_language_default_value;
	ZVAL_NULL(&property_language_default_value);
	zend_string *property_language_name = zend_string_init("language", sizeof("language") - 1, 1);
	zend_declare_typed_property(class_entry, property_language_name, &property_language_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_STRING|MAY_BE_NULL));
	zend_string_release(property_language_name);

	zval property_numberingSystem_default_value;
	ZVAL_NULL(&property_numberingSystem_default_value);
	zend_string *property_numberingSystem_name = zend_string_init("numberingSystem", sizeof("numberingSystem") - 1, 1);
	zend_declare_typed_property(class_entry, property_numberingSystem_name, &property_numberingSystem_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_STRING|MAY_BE_NULL));
	zend_string_release(property_numberingSystem_name);

	zval property_numeric_default_value;
	ZVAL_NULL(&property_numeric_default_value);
	zend_string *property_numeric_name = zend_string_init("numeric", sizeof("numeric") - 1, 1);
	zend_declare_typed_property(class_entry, property_numeric_name, &property_numeric_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_BOOL|MAY_BE_NULL));
	zend_string_release(property_numeric_name);

	zval property_region_default_value;
	ZVAL_NULL(&property_region_default_value);
	zend_string *property_region_name = zend_string_init("region", sizeof("region") - 1, 1);
	zend_declare_typed_property(class_entry, property_region_name, &property_region_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_STRING|MAY_BE_NULL));
	zend_string_release(property_region_name);

	zval property_script_default_value;
	ZVAL_NULL(&property_script_default_value);
	zend_string *property_script_name = zend_string_init("script", sizeof("script") - 1, 1);
	zend_declare_typed_property(class_entry, property_script_name, &property_script_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_STRING|MAY_BE_NULL));
	zend_string_release(property_script_name);

	return class_entry;
}

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
