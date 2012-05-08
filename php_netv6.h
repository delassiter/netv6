#ifndef PHP_NETV6_H
#define PHP_NETV6_H
#define PHP_NETV6_EXTNAME	"netv6"
#define PHP_NETV6_EXTVER	"0.1.0"
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "php.h"
extern zend_module_entry netv6_module_entry;
#define phpext_netv6_ptr &netv6_module_entry
#endif
