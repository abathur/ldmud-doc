.. overview:: External functions
  :name: efun

  This directory contains descriptions for the efuns of LDMud.

  These are functions that are supplied by the driver and can be called by any LPC object (somewhat similar to system calls in the C library).

  .. todo:: in theory this information could probably be massaged for doxygen such that it documents the "efun" class

  .. todo:: below language calls these 'kinds' but they're really 'statuses', and there might be a smart way to link these (at least in the HTML docs) with the actual status on individual docs. IIRC we use these for more than just efuns, so it might be best to have a meta page with a list of document statuses/explanations, link all of the actual statuses there, and then link these items to those members.

  .. todo:: verify use of synopsis below

  .. enumerate::
    :noindex:
    :synopsis: There a few kinds of efuns:

    *optional*
      A mud's maintainer is free to deactivate these efuns when
      compiling the driver:

      - :efun:`break_point`
      - :efun:`db_affected_rows`
      - :efun:`db_close`
      - :efun:`db_coldefs`
      - :efun:`db_connect`
      - :efun:`db_conv_string`
      - :efun:`db_error`
      - :efun:`db_exec`
      - :efun:`db_fetch`
      - :efun:`db_handles`
      - :efun:`db_insert_id`
      - :efun:`parse_command`
      - :efun:`process_string`
      - :efun:`rusage`
      - :efun:`set_is_wizard`
      - :efun:`transfer`
      - :efun:`tls_available`
      - :efun:`tls_check_certificate`
      - :efun:`tls_deinit_connection`
      - :efun:`tls_error`
      - :efun:`tls_init_connection`
      - :efun:`tls_query_connection_info`
      - :efun:`tls_query_connection_state`
      - :efun:`tls_refresh_certs`
      - :efun:`xml_generate`
      - :efun:`xml_parse`

      .. todo:: failed refs for assoc, insert_alist and intersect_alist above

      alt approach:

      .. toctree::
        :maxdepth: 1
        :glob:

        assoc.rst
        break_point.rst
        db_*
        insert_alist
        intersect_alist
        parse_command
        process_string
        rusage
        set_is_wizard
        transfer
        tls_*
        xml_*

      .. todo:: decide between the brief/less-explicit alt-approach, and the explicit approaches above... One advantage of the explicit approach is that breakages in it reveal when documents have moved or gone away and haven't been properly rooted out. That said, it can still easily miss new documents (i.e., we add some TLS efun).

      .. todo:: should JSON funcs be here?

    *experimental*
      The behaviour of these efuns is not fixed yet, and may change with further releases:

      - :efun:`tls_available`
      - :efun:`tls_check_certificate`
      - :efun:`tls_deinit_connection`
      - :efun:`tls_error`
      - :efun:`tls_init_connection`
      - :efun:`tls_query_connection_info`
      - :efun:`tls_query_connection_state`
      - :efun:`tls_refresh_certs`
      - :efun:`xml_generate`
      - :efun:`xml_parse`

    *deprecated*
      These efuns should no longer be used, they are merely provided for backwards compatibility:

      - :efun:`make_shared_string`
      - :efun:`md5`
      - :efun:`sha1`

  .. subtopic:: efun index

    .. toctree::
      :maxdepth: 1
      :glob:

      *

  .. seealso:: :concept:`efuns`,
    :overview:`applied`, :overview:`topics`, :overview:`hook`, :overview:`internals`, :overview:`syntax`, :overview:`master`, :overview:`obsolete`
