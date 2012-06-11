netv6
=====

This extensions offers a Class by the name of "NetV6" with two static methods
 * getHostByName($hostname, $protocol)
 * getHostByNameL($hostname, $protocol)

For $protocol you may use
 * NetV6::IPV4
 * NetV6::IPV6
 * NetV6::DUAL

On error during lookup a NetV6Exception will be thrown with Message and Code (according to getaddrinfo)

For getHostByName NetV6::DUAL will get IPv6 and if not available IPv4 (or error)
For getHostByNameL NetV6::DUAL will get both IPv6 and IPv4

To Do
===
 * refactor (!!!)
 * tests

Installation
===

Requirements: php5, php5-dev, *nix os, pear & pecl

1. phpize .
2. ./configure
3. make
4. make install
5. Add extension to php
