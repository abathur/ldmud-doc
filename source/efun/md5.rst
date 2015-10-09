.. efun:: string md5(string arg [, int iterations])
  string md5(int *  arg [, int iterations])
  :obsolete:

Create and return a MD5 message digest from <arg>.
<arg> may be a string, or an array of numbers (each considered to
be a character, ignoring all but the lowest byte).

If <iterations> is given as a number greater than 0, it is
the number of iterations used in the digest calculation. If omitted,
the driver executes just one iteration.

The efun costs 5 ticks per iteration.

EXAMPLES
string s;

s = md5("Hello");
s = md5( ({ 'H', 'e', 'l', 'l', 'o' }) )
s = md5( ({ 'H', 'e', 'l', 'l', 'o' }), 2 )

.. history
Introduced in LDMud 3.2.9.
LDMud 3.2.12 added number arrays as argument, and the number of
interations.
LDMud 3.3.717 added the iteration-based evaluation cost.
Since LDMud 3.3.719 obsoleted by hash().

  .. seealso:: :efun:`crypt`, :efun:`md5_crypt`, :efun:`sha1`, :efun:`hash`, :efun:`hmac`
