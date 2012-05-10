#ifndef NETV6_EXCEPTION_H_INCLUDED
#define NETV6_EXCEPTION_H_INCLUDED

extern void mapError(int errorno, char *dest);
extern void throwException(char *message, int errorno, zend_class_entry *cex);

#endif
