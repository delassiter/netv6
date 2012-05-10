PHP_ARG_ENABLE(netv6,
  [Whether to enable the "netv6" extension],
  [ --enable-netv6	Enable "netv6" exentsion support])

if test $PHP_NETV6 != "no"; then
  PHP_SUBST(NETV6_SHARED_LIBADD)
  PHP_NEW_EXTENSION(netv6, netv6.c netv6_lookup.c netv6_exception.c, $ext_shared)
fi
