netv6
=====

This extensions offers a Class by the name of "NetV6" with two static methods
 * getHostByName($hostname, $protocol)
 * getHostByNameL($hostname, $protocol)

For $protocol you may use
 * NetV6::IPV4
 * NetV6::IPV6

On error during lookup an NetV6Exception will be thrown with Message and Code (according to getaddrinfo)

To Do
===
 * Allow IPV6-lookup with fallback to IPV4 (as new $protocol)
 * refactor
 * tests
