.. efun:: string hash(int method, string arg [, int iterations ] )
  string hash(int method, int *  arg [, int iterations ] )
  :include: <tls.h>

  Calculate the hash from :arg:`arg` as determined by :arg:`method`. The hash is calculated with :arg:`iterations` iterations, default is 1 iteration.

  :arg:`method` is one of the constants defined in tls.h; not all recognized methods may be supported for a given driver:

  .. todo:: recurring macro/include question

  - :macro:`TLS_HASH_SHA1`      (1)
  - :macro:`TLS_HASH_SHA224`    (2)
  - :macro:`TLS_HASH_SHA256`    (3)
  - :macro:`TLS_HASH_SHA384`    (4)
  - :macro:`TLS_HASH_SHA512`    (5)
  - :macro:`TLS_HASH_MD5`       (6)
  - :macro:`TLS_HASH_RIPEMD160` (7)

  If the driver is compiled without OpenSSL or GCrypt support only :macro:`TLS_HASH_SHA1` and :macro:`TLS_HASH_MD5` are available.

  The efun costs 10 ticks per iteration.

  .. usage::

    The example below shows how to compute the :term:`SHA1` hash of a string and an array of characters::

      string s;

      s = hash(TLS_HASH_SHA1, "Hello", 2);
      s = hash(TLS_HASH_SHA1, ({ 'H', 'e', 'l', 'l', 'o' }) );

  :history 3.3.714 introduced:
  :history 3.3.719 changed: added the iteration-based evaluation cost

  .. seealso:: :efun:`crypt`, :efun:`md5`, :efun:`md5_crypt`, :efun:`sha1`, :efun:`hmac`
