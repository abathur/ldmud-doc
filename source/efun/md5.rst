.. efun:: string md5(string arg [, int iterations])
  string md5(int *  arg [, int iterations])
  :deprecated:

  Create and return a :term:`MD5` message digest from :arg:`arg`. :arg:`arg` may be a string, or an array of numbers (each considered to be a character, ignoring all but the lowest byte).

  If :arg:`iterations` is given as a number greater than 0, it is the number of iterations used in the digest calculation. If omitted, the driver executes just one iteration.

  The efun costs 5 ticks per iteration.

  .. usage::

    ::

      string s;

      s = md5("Hello");
      s = md5( ({ 'H', 'e', 'l', 'l', 'o' }) );
      s = md5( ({ 'H', 'e', 'l', 'l', 'o' }), 2 );

  :history 3.2.9 introduced:
  :history 3.2.12 changed: added number arrays as argument, and the number of iterations.
  :history 3.3.717 changed: added the iteration-based evaluation cost.
  :history 3.3.719 deprecated: obsoleted by :efun:`hash`.

  .. seealso:: :efun:`crypt`, :efun:`md5_crypt`, :efun:`sha1`, :efun:`hash`, :efun:`hmac`
