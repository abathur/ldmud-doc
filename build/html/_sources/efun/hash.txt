.. efun:: string hash(int method, string arg [, int iterations ] )
  string hash(int method, int *  arg [, int iterations ] )
  :include: <tls.h>

  Calculate the hash from <arg> as determined by <method>. The hash is
  calculated with <iterations> iterations, default is 1 iteration.

  <method> is one of the TLS_HASH_ constants defined in tls.h; not
  all recognized methods may be supported for a given driven:

    TLS_HASH_SHA1      (1)
    TLS_HASH_SHA224    (2)
    TLS_HASH_SHA256    (3)
    TLS_HASH_SHA384    (4)
    TLS_HASH_SHA512    (5)
    TLS_HASH_MD5       (6)
    TLS_HASH_RIPEMD160 (7)

  If the driver is compiled without OpenSSL or GCrypt support
  only TLS_HASH_SHA1 and TLS_HASH_MD5 are available.

  The efun costs 10 ticks per iteration.

  .. usage::

    string s;

    s = hash(TLS_HASH_SHA1, "Hello", 2);
    s = hash(TLS_HASH_SHA1, ({ 'H', 'e', 'l', 'l', 'o' }) )

.. history
  :history 3.3.714 introduced:
  :history 3.3.719 changed: added the iteration-based evaluation cost

  .. seealso:: :efun:`crypt`, :efun:`md5`, :efun:`md5_crypt`, :efun:`sha1`, :efun:`hmac`
