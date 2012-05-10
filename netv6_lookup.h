#ifndef NETV6_LOOKUP_H_INCLUDED
#define NETV6_LOOKUP_H_INCLUDED

extern int getIpByName(const char *hostname, long type, struct addrinfo **res);

extern int getIpAsString(struct addrinfo *res, long type, char *dest);


#endif
