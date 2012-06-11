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
#include "zend_exceptions.h"

void mapError(int errorno, char *dest)
{
    switch (errorno) {
            case EAI_ADDRFAMILY:
                strcpy(dest, "The specified network host does not have any network addresses in the requested address family.");
                break;
            case EAI_AGAIN:
                strcpy(dest, "The name server returned a temporary failure indication. Try again later.");
                break;
            case EAI_FAIL:
                strcpy(dest, "The name server returned a permanent failure indication.");
                break;
            case EAI_NODATA:
                strcpy(dest, "The specified network host exists, but does not have any network addresses defined");
                break;
            case EAI_NONAME:
                strcpy(dest, "The node or service is not known; or both node and service are NULL");
                break;
            default:
                strcpy(dest, "Other system error, check errno for details.");
                break;
    }
}

void throwException(char *message, int errorno, zend_class_entry *cex)
{
    zval *ex;
    MAKE_STD_ZVAL(ex);
    object_init_ex(ex, cex);
    zend_update_property_string(cex, ex, "message", sizeof("message") - 1,
message TSRMLS_CC);
    zend_update_property_long(cex, ex, "code", sizeof("code") - 1, errorno TSRMLS_CC);

    zend_throw_exception_object(ex TSRMLS_CC);
}
