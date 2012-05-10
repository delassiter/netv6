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

