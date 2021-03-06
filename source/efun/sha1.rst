.. efun:: string sha1(string arg [, int iterations ])
  string sha1(int  * arg [, int iterations ])
  :deprecated:

  Create and return a SHA1 message digest from :arg:`arg`. :arg:`arg` may be a string, or an array of numbers (each considered to be a character, ignoring all but the lowest byte).

  .. todo:: the brackets in these synopses don't fare well in the current parse, but I'm not sure if it's ideal to fix this, or to follow the more verbose style of some other docs which explicitly list each form.

  If :arg:`iterations` is given as a number greater than 0, it is the number of iterations used in the digest calculation. If omitted, the driver executes just one iteration.

  The efun costs 5 ticks per iteration.

  .. usage::

    ::

      string s;

      s = sha1("Hello");
      s = sha1( ({ 'H', 'e', 'l', 'l', 'o' }) );

  :history 3.3.523 introduced:
  :history 3.3.712 changed: added number arrays as argument, and the number of iterations.
  :history 3.3.717 changed: added the iteration-based evaluation cost.
  :history 3.3.719 deprecated: obsoleted by hash().

  .. seealso:: :efun:`crypt`, :efun:`md5`, :efun:`md5_crypt`, :efun:`hash`, :efun:`hmac`
