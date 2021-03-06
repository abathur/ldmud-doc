.. efun:: string invert_bits(string str)

  Invert the status of all bits in bitstring :arg:`str` and return the new string.

  Note that the total number of bits (ie the string length) stays the same.

  .. usage::

    ::

      string s;

      s = set_bit("", 3);
      s = set_bit(s, 4);
      s = set_bit(s, 15); //s is now  "8 ("

      invert_bits(s) //returns "G_W"

  .. seealso:: :efun:`set_bit`, :efun:`clear_bit`, :efun:`test_bit`, :efun:`last_bit`, :efun:`and_bits`, :efun:`or_bits`, :efun:`xor_bits`, :efun:`count_bits`, :efun:`copy_bits`
