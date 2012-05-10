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
#include "netv6_lookup.h"

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

