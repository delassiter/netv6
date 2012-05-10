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

#ifndef NETV6_LOOKUP_H_INCLUDED
#define NETV6_LOOKUP_H_INCLUDED

extern int getIpByName(const char *hostname, long type, struct addrinfo **res);

extern int getIpAsString(struct addrinfo *res, long type, char *dest);


#endif
