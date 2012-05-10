#include "php_netv6.h"
#include "netv6_exception.h"

zend_class_entry *php_netv6_sc_entry;
zend_class_entry *php_netv6_exception_class_entry;

PHP_METHOD(NetV6, getHostByName)
{
    const char * hostname = NULL;
    struct addrinfo *result;
    int hostname_len = 0;
    int type;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sl", &hostname, &hostname_len, &type) == FAILURE) {
        return;
    }

    int error;
  
    error = getIpByName(hostname, type, &result);
    if (error != 0) {
        char message[255];
        mapError(error, &message);
        throwException(message, error, php_netv6_exception_class_entry);
        return;
    }

    char ip[INET6_ADDRSTRLEN];
    getIpAsString(result, type, &ip);
    freeaddrinfo(result);

    RETVAL_STRING(ip, 1); 
    return;
}

int getIpByName(const char *hostname, long type, struct addrinfo **res)
{
    int error;
    struct addrinfo hints;
    memset(&hints, 0, sizeof hints);
    if (type == 2) {
        hints.ai_family = AF_INET6;
    } else {
        hints.ai_family = AF_INET;
    }
    hints.ai_socktype = SOCK_STREAM;

    error = getaddrinfo(hostname, NULL, &hints, res);

    return error;
}

int getIpAsString(struct addrinfo *res, long type, char *dest)
{
    char ip[INET6_ADDRSTRLEN];
    if (type == 2) {
        struct sockaddr_in6* saddr;
        void *addr;
        saddr = (struct socketaddr_in6 *)res->ai_addr;
        addr = &(saddr->sin6_addr);
        inet_ntop(res->ai_family, addr, ip, sizeof ip);
    } else {
        struct sockaddr_in* saddr;
        void *addr;
        saddr = (struct socketaddr_in *)res->ai_addr;
        addr = &(saddr->sin_addr);
        inet_ntop(res->ai_family, addr, ip, sizeof ip);
    }
    strcpy(dest, ip);
    return 0;
}

PHP_METHOD(NetV6, getHostByNameL)
{

}

zend_function_entry php_netv6_methods[] = {
    PHP_ME(NetV6, getHostByName, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(NetV6, getHostByNameL, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    {NULL, NULL, NULL}
};

const zend_function_entry php_netv6_exception_methods[] = {
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
    zend_class_entry ce, cex;
    INIT_CLASS_ENTRY(ce, "NetV6", php_netv6_methods);
    php_netv6_sc_entry = zend_register_internal_class(&ce TSRMLS_CC);
    php_netv6_register_constants(php_netv6_sc_entry);

    INIT_CLASS_ENTRY(cex, "NetV6Exception", php_netv6_exception_methods);
    php_netv6_exception_class_entry = zend_register_internal_class_ex(&cex, zend_exception_get_default(TSRMLS_C), NULL TSRMLS_CC);

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
