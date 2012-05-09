#include "php_netv6.h"

zend_class_entry *php_netv6_sc_entry;

PHP_METHOD(NetV6, getHostByName)
{
    struct addrinfo hints, *result;
    int error;
    struct sockaddr_in6* saddr;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET6;
    hints.ai_socktype = SOCK_STREAM;

    error = getaddrinfo("ipv6.google.com", NULL, NULL, &result);
    if (error) {
        php_printf("Hello");
    }

    // Error handling
    char ip[INET6_ADDRSTRLEN];
    void *addr;

    saddr = (struct socketaddr_in6 *)result->ai_addr;
    addr = &(saddr->sin6_addr);
    inet_ntop(result->ai_family, addr, ip, sizeof ip);
    php_printf("ai_addr hostname ->  %s\n", ip);

    freeaddrinfo(result);
}

PHP_METHOD(NetV6, getHostByNameL)
{

}

zend_function_entry php_netv6_methods[] = {
    PHP_ME(NetV6, getHostByName, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(NetV6, getHostByNameL, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    {NULL, NULL, NULL}
};

void php_netv6_register_constants(zend_class_entry *ce)
{
    zval *constval;
    
    constval = pemalloc(sizeof(zval), 1);
    INIT_PZVAL(constval);
    ZVAL_LONG(constval, 1);
    zend_hash_add(&ce->constants_table, "IPV4", sizeof("IPV4"), (void*)&constval, sizeof(zval*), NULL);

    constval = pemalloc(sizeof(zval), 1);
    INIT_PZVAL(constval);
    ZVAL_LONG(constval, 2);
    zend_hash_add(&ce->constants_table, "IPV6", sizeof("IPV6"), (void*)&constval, sizeof(zval*), NULL);
}

PHP_MINIT_FUNCTION(netv6)
{
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "NetV6", php_netv6_methods);
    php_netv6_sc_entry = zend_register_internal_class(&ce TSRMLS_CC);
    php_netv6_register_constants(php_netv6_sc_entry);

    return SUCCESS;
}

PHP_MINFO_FUNCTION(netv6)
{
    php_info_print_table_start();
    php_info_print_table_row(2, "NetV6 Module", "enabled");
    php_info_print_table_row(2, "version", PHP_NETV6_EXTVER);
    php_info_print_table_end();
}

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
