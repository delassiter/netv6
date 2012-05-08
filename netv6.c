#include "php_netv6.h"
zend_module_entry netv6_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
  STANDARD_MODULE_HEADER,
#endif
  PHP_NETV6_EXTNAME,
  NULL, /* Functions */
  PHP_MINIT(netv6), /* MINIT */
  NULL, /* MSHUTDOWN */
  NULL, /* RINIT */
  NULL, /* RSHUTDOWN */
  PHP_MINFO(netv6), /* MINFO */
#if ZEND_MODULE_API_NO >= 20010901
  PHP_NETV6_EXTVER,
#endif
  STANDARD_MODULE_PROPERTIES
};
#ifdef COMPILE_DL_NETV6
ZEND_GET_MODULE(netv6)
#endif

PHP_MINIT_FUNCTION(netv6)
{
    return SUCCESS;
}

PHP_MINFO_FUNCTION(netv6)
{
    php_info_print_table_start();
    php_info_print_table_row(2, "NetV6 Module", "enabled");
    php_info_print_table_row(2, "version", PHP_NETV6_EXTVER);
    php_info_print_table_end();
}
