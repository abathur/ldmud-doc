.. topic:: PostgreSQL support
  :name: pgsql
  :topics: driver

  On hosts with the PostgreSQL package installed, the driver can be configured to interface with the PostgreSQL database. If that is done, the driver defines the macro :macro:`__PGSQL__` for LPC programs and activates a number of related efuns.

  .. usage::

    The interface to the PostgreSQL database is implemented through the concept of a controlling object: when opening a database connection, the LPC code has to provide a callback function. The object this function is bound to is the controlling object: all queries to the database will be issued by this object, and the responses will be sent to the callback function.

    The interface is also asynchronous: :efun:`pg_query` just queues the query with the database connection, and returns immediately. When the database has finished working the query, the callback function is called with the results.

    The callback function can be defined by name or by closure, and can be defined with extra parameters::

      #include <pgsql.h>

      void <callback>(int type, mixed ret, int id [, mixed extra...])

        <type> is the type of the call, <id> identifies the query
        for which this call is executed:

          PGRES_TUPLES_OK: <ret> is the result from a query.
                           It is either a mapping (field name as
                           key, indexing <n> values for n returned
                           tuples), or an array of arrays (one per
                           row).

          PGRES_COMMAND_OK: <ret> is a string which contains the
                            server response (e.g. on INSERT or DELETE)

          PGRES_BAD_RESPONSE,
          PGRES_NONFATAL_ERROR,
          PGRES_FATAL_ERROR: ret is the error-string


      void <callback>(int type, mixed ret [, mixed extra...])

        <type> is the type of the call, which is not related to a
        specific query:

          PGCONN_SUCCESS: The database-connection was established,
                          <ret> is a dummy string.
          PGCONN_FAILED:  The database-connection failed, <ret> is
                          the error message.
            The first message to the callback after a call to
            pg_connect() is always one of these two.

          PGRES_NOTICE: <ret> is a informational text.

          PGCONN_ABORTED: If the connection to the backend fails
                          we try to re-establish (reset) it. If the
                          reset fails, the connection is closed and
                          this value is returned. Consider the
                          connection gone and don't try to close or
                          otherwise operate further on it.
                          <ret> is a dummy string.

  .. todo:: the above section should probably use more semantic markup instead of just being a big literal block

  .. subtopic:: security

    All SQL efuns (unless execute by the master or the simul-efun object) trigger a ``privilege_violation ("pgsql", "<efun_name>")``. If a more fine-grained control is desired, overload the individual efuns with a nomask simul_efun.

    .. todo:: privilege violation above

  :history 3.3.445 introduced:
  :history 3.3.640 changed: added a privilege_violation() call for each efun.

  .. lore::

    Authored by Florian Heinz and others.

  .. seealso:: :concept:`mysql`, :efun:`pg_connect`, :efun:`pg_conv_string`, :efun:`pg_query`, :efun:`pg_pending`, :efun:`pg_close`, :master:`privilege_violation`
