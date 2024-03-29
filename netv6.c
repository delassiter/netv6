/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2012 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Dennis Lassiter dennis@lassiter.de Copyright (c) 2012        |
  +----------------------------------------------------------------------+
*/

#include "php_netv6.h"
#include "netv6_exception.h"
#include "netv6_lookup.h"

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

    int retry = 1;

    // If type == DUAL = get IPv6 and fallback to IPv4
    if (type == 4) {
        type = 2;
        error = getIpByName(hostname, 2, &result);
        if (error != 0) {
             type = 1;
        } else {
             retry = 0;
        }
    }

    if (retry == 1) {
        error = getIpByName(hostname, type, &result);
        if (error != 0) {
            char message[255];
            mapError(error, &message);
            throwException(message, error, php_netv6_exception_class_entry);
            return;
        }
    }


    char ip[INET6_ADDRSTRLEN];
    getIpAsString(result, type, &ip);
    freeaddrinfo(result);

    RETVAL_STRING(ip, 1); 
    return;
}

PHP_METHOD(NetV6, getHostByNameL)
{
    const char * hostname = NULL;
    struct addrinfo *result;
    struct addrinfo *res;
    int hostname_len = 0;
    int type;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sl", &hostname, &hostname_len, &type) == FAILURE) {
        return;
    }

    int error;
    int foundIpV6 = 0;
    array_init(return_value);

    // If type == DUAL = get IPv6 and IPv4
    if (type == 4) {
        type = 2;
        error = getIpByName(hostname, type, &result2);

        if (error == 0) {
            for (res2 = result2; res2 != NULL; res2 = res2->ai_next)
            {
                char ip[INET6_ADDRSTRLEN];
                getIpAsString(res2, type, &ip);
                add_next_index_string(return_value, ip, 1);
                foundIpV6++;
            }
            freeaddrinfo(result2);
        }
        type = 1;
    }

    error = getIpByName(hostname, type, &result);
    if (error != 0 && foundIpV6 == 0) {
        char message[255];
        mapError(error, &message);
        throwException(message, error, php_netv6_exception_class_entry);
        return;
    } else if (error == 0) {

        for (res = result; res != NULL; res = res->ai_next)
        {
            char ip[INET6_ADDRSTRLEN];
            getIpAsString(res, type, &ip);
            add_next_index_string(return_value, ip, 1);
        }
        freeaddrinfo(result);
    }
    return;

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

    constval = pemalloc(sizeof(zval), 1);
    INIT_PZVAL(constval);
    ZVAL_LONG(constval, 4);
    zend_hash_add(&ce->constants_table, "DUAL", sizeof("DUAL"), (void*)&constval, sizeof(zval*), NULL);

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
