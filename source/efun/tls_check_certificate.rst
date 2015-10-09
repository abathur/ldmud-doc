.. efun:: mixed * tls_check_certificate(object obj)
  mixed * tls_check_certificate(object obj, int extra)
  :preliminary:

  tls_check_certificate() checks the certificate of the secured
  connection bound to <obj> (default is the current object). An
  error is thrown if <obj> is not interactive or TLS is not
  available.

  An error is also thrown if <obj> doesn't have a secure connection
  up and running.

  Otherwise, the result is an array with these values:

    int [0]   : Result code of SSL_get_verify_result (see 'man 1 verify'
                subsection DIAGNOSTICS for possible values).
    array [1] : Array with 3*n entries of extra x509 data.
                Structure is:
                  3*i    : numerical form of object name,
                           e.g. "2.5.4.3"
                  3*i + 1: long or short name if available,
                           e.g. "commonName"
                  3*i + 2: value
    array [2] : If <extra> is set:
                  array with 3*n entries of x509 extension data
                  data structure is:
                  3*i    : numerical form of extension name
                  3*i + 1: long or short name of extension
                           name if available
                  3*i + 2: array of strings with the data
                           structure of [1]

  .. note:: An X509 certificate can have more than one object with
  the same name.

.. history
  Introduced in LDMud 3.3.672/3.2.11.
  LDMud 3.3.711/3.2.12 modified the behaviour to return the low-level
  API result value, and to throw an error if the connection is not
  secure.

  .. seealso:: :efun:`tls_init_connection`, :efun:`tls_deinit_connection`, :efun:`tls_error`,
 :efun:`tls_query_connection_state`, :efun:`tls_query_connection_info`,
 :efun:`tls_available`, :efun:`tls_refresh_certs`, mudlib/psyc-tls.c
