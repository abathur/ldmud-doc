.. efun:: string copy_bits(string src, string dest[, int srcstart [, int deststart [, int copylen ]]])

  Copy the bitrange :samp:`[{srcstart}..{srcstart}+{copylen}]` from bitstring :arg:`src` and copy it into the bitstring :arg:`dest` starting at :arg:`deststart`, overwriting the original bits at those positions.

  .. todo:: not immediately clear how best to render above (and some below) argument references; RST format requires spacing

  The resulting combined string is returned, the input strings remain unaffected.

  If :arg:`srcstart` is not given, :arg:`src` is copied from the start. If :arg:`srcstart` is negative, it is counted from one past the last set bit in the string (ie. '-1' will index the last set bit).

  If :arg:`deststart` is not given, :arg:`dest` will be overwritten from the start. If :arg:`deststart` is negative, it is counted from one past the last set bit in the string (ie. '-1' will index the last set bit).

  If :arg:`copylen` is not given, it is assumed to be infinite, ie. the result will consist of :arg:`dest` up to position :arg:`deststart`, followed by the data copied from :arg:`src`. If :arg:`copylen` is negative, the function will copy the abs(:arg:`copylen`) bits _before_ :arg:`srcstart` in to the result.

  None of the range limits can become negative.

  .. usage::

    ::

      copy_bits(src, dest, 10)    === src[10..]
      copy_bits(src, dest, 10, 5) === dest[0..4] + src[10..]
      copy_bits(src, dest, 10, 5, 3)
                                  === dest[0..4] + src[10..12] + dest[8..]

    (The src[]/dest[] is just for explanatory purposes!)

  :history 3.3.166 introduced:

  .. seealso:: :efun:`clear_bit`, :efun:`set_bit`, :efun:`test_bit`, :efun:`next_bit`, :efun:`last_bit`, :efun:`count_bits`, :efun:`or_bits`, :efun:`xor_bits`, :efun:`invert_bits`, :efun:`and_bits`
