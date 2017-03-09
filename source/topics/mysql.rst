.. topic:: mysql

  On hosts with the mySQL package installed, the driver can be configured to interface with the mySQL database. If that is done, the driver defines the :macro:`__MYSQL__` for LPC programs and activates a number of efuns.

  .. todo:: above or below should maybe link to where we actually explain driver compile config?

  .. subtopic:: Configuration

    Create a dedicated user in the mySQL database for the driver. Enter this username and password in the file pkg-mysql.c, (function ``mysql_real_connect()``), and compile the driver (the username and password are built into the driver for security reasons). If you choose to not create either a username and/or a password, leave the corresponding entry at 0.

    Use mysqladmin to create any databases you want to provide - the names are later used in the :efun:`db_connect` to connect to the databases.

  .. todo:: reconcile how this doc uses usage/example sections

  .. subtopic:: Working with a mySQL database

    The idea behind SQL-support is that you can swap large amounts of data into a database where it can be accessed very easily. As mySQL "limits" the number of connections to 100 and as every connection to the mySQL-server takes time, you should use database serverobjects in your MUD which constantly keep the connection to the mySQL-server.

    To connect to your mySQL-server, use the :efun:`db_connect`. It takes only one argument which is the name of the database (which must exist). The return-value of :efun:`db_connect` is an integer representing the unique handle to the database with which you will identify your connection later.

    To send or retrieve data from this connection, use :efun:`db_exec`. The first parameter for all efuns dealing with an open connection is always the handle and so is the first argument the handle and the second one the command you want to issue. The return-value is either 0 if there was an error in your command (this can have various reasons), otherwise your handle is returned again. A typical SQL-statement to retrieve data would be like:

    .. code-block:: sql

      select aliases.command from aliases where (name = 'mario' AND
        alias regexp 'l.*')

    As you know, mySQL accepts either " or ' to classify strings for parameters. Most likely, you will pass variables and don't know whether they contain one or more of these key-chars (or even other chars that need to be converted). mySQL provides a function for converting just any string into an acceptable argument and this is implemented in :efun:`db_conv_string`.

    So the above example with variables looks like:

    .. code-block:: sql

      select aliases.command from aliases where (name ='"+
        db_conv_string(name)+"' AND alias regexp '"+
        db_conv_string(mask)+"')

    I left out the :efun:`db_exec`-stuff, more complete examples will follow.

    .. warning:: After you initiated a statement that could return rows from the database, use :efun:`db_fetch` to retrieve each row. You need to call it until it returns 0. If you stop calling :efun:`db_fetch` before it reaches the end of data, serious inconsistencies can happen!

    .. todo:: is the above warning still true?

    If you used a ``DELETE`` or ``UPDATE`` statement, you cannot call :efun:`db_fetch`, but you can query the number of deleted/changed rows with :efun:`db_affected_rows`.

    After all operations are done in the database, you should use :efun:`db_close` to close the connection again. If you are using a database-server concept (such as the one in the usage section), call it from the lfun :applied:`remove`.

    The SQL efuns have some built-in optimization-features to speed up often used connections. To get a list of all open connections to the mySQL-server, use :efun:`db_handles` which returns an array of integers with all open handles.

  .. subtopic:: Security

    Most SQL efuns (unless executed by the master or simul-efun objects) trigger a ``privilege_violation ("mysql", "<efun_name>")``. If a more fine-grained control is desired, overload the individual efuns with a nomask simul-efun.

    .. todo:: privilege violation above

    The unprivileged efuns are:

      - :efun:`db_conv_string`

  .. warning:: The driver enables automatic reconnects on the database connections. This means that if a connection is lost (the most common case for this is timeouts, which by default happen after 28800 seconds of inactivity) an attempt will be made to establish a new connection to the database server. When that happens, all session state (temprary tables and state changes from ``SET`` statements) will be lost. It's best not to rely on such state.

  .. usage::

    A simple server to store aliases could be implemented like this::

      /*
      **  CREATION:
      **
      **  create table aliases (
      **      name varchar(15) not NULL,
      **      alias varchar(20) not NULL,
      **      command varchar(255) not NULL,
      **      primary key (name, alias));
      */

      #define DATABASE "mud"

      private int handle;

      public void create()
      {
        handle = db_connect(DATABASE);
      }

      public int remove()
      {
        if ( handle )
          db_close(handle);
        destruct(ME);
        return !ME;
      }

      public int AddAlias(string alias, string command, object ob)
      {
        if ( !handle )
          handle = db_connect(DATABASE);
        if ( !db_exec(handle, "insert into aliases (name, alias, command) values ('" + getuid(ob) + "','" + db_conv_string(alias)+ "','" +db_conv_string(command) + "')") )
          return -1;
        return 1;
      }

      public int RemoveAlias(string alias, object ob)
      {
        int res;

        if ( !handle )
          handle = db_connect(DATABASE);
        res = db_exec(handle,
          "delete from aliases where (name = '"+ getuid(ob) + "' AND alias = '" + db_conv_string(alias)+ "')");
        if ( !res )
          return 0;
        res = db_affected_rows(handle);
        return (res > 0)?1:-1;
      }

      public mixed *QueryAliases(string mask, object ob)
      {
        mixed *result;
        string *tmp;

        if ( !handle )
          handle = db_connect(DATABASE);
        if ( !db_exec(handle, "select aliases.alias, aliases.command from aliases where (name = '" + getuid(ob) + "' AND alias regexp '" + db_conv_string(mask) + "')") )
          return ({ });
        result = ({ });
        while ( sizeof(tmp = db_fetch(handle)) )
          result += ({ tmp });
        return result;
      }

      public string QueryAlias(string alias, object ob)
      {
        mixed *result;
        string *tmp;

        if ( !handle )
          handle = db_connect(DATABASE);
        if ( !db_exec(handle, "select aliases.command from aliases where (name = '" + getuid(ob)+ "' AND alias = '" + db_conv_string(alias) + "')") )
          return 0;
        result = ({ });
        while ( sizeof(tmp = db_fetch(handle)) )
          result += tmp;
        return sizeof(result)?result[0]:0;
      }

  .. lore::

    Author
      Mark Daniel Reidel and others.

  :history 3.2.8 introduced: as package
  :history 3.2.9 changed: integrated with driver
  :history 3.2.11 changed: added a privilege_violation() call for each efun

  .. seealso:: :topic:`pgsql`, :efun:`db_affected_rows`, :efun:`db_conv_string`, :efun:`db_close`, :efun:`db_connect`, :efun:`db_exec`, :efun:`db_fetch`, :efun:`db_handles`, :efun:`db_insert_id`, :efun:`db_coldefs`, :efun:`db_error`, :master:`privilege_violation`
