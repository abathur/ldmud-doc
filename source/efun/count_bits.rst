.. efun:: int count_bits(string str)

  Count the number of set bits in bitstring :arg:`str` and return the number as result.

  .. todo:: is it possible to make an example scenario that actually suggests _why_ we'd want to count them?

  .. usage::

    Here's a very simple example::

      string s;

      s = set_bit("", 3);
      s = set_bit(s, 15);

      count_bits(s) // returns 2

  .. seealso:: :efun:`clear_bit`, :efun:`set_bit`, :efun:`test_bit`, :efun:`next_bit`, :efun:`last_bit`, :efun:`or_bits`, :efun:`xor_bits`, :efun:`invert_bits`, :efun:`copy_bits`
