.. efun:: void set_connection_charset(int *bitvector, int quote_iac)
  void set_connection_charset(string charset, int quote_iac)
  void set_connection_charset(0, int quote_iac)

  Set the set of characters that can be output to the interactive user (this does not apply to :efun:`binary_message`). The function must be called by the interactive user object itself.

  The charset can be given either directly as a string, or indirectly as a bitvector. If the charset is given as the number 0, the default connection charset is re-established.

  The bitvector is interpreted as an array of 8-bit-values and might contain up to 32 elements. Character n is allowed to be output if ``sizeof(bitvector) > n/8 && bitvector[n/8] & (1 << n%8)``.

  If quote_iac is 0 and char 255 is allowed to be output, IAC will be output unmodified. If quote_iac is 1 and char 255 is allowed to be output, char 255 will be quoted so that it is not interpreted as IAC by the telnet protocol. This is the default.

  :history 3.2.1@40 introduced:
  :history 3.2.8 changed: added the ability to specify the charset as a string.
  :history 3.2.10 changed: added the ability to reset the charset to the default.

  .. seealso:: :efun:`get_connection_charset`, :efun:`binary_message`, :efun:`set_combine_charset`
