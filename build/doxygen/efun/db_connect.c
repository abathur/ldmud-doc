public class efun {
   /**
    * Connect to the database \p database on the local mySQL-server. The return-value is the handle for this connection. Automatic reconnects are enabled for this connection; see >>:concept:`mysql`<< for implications. If the database does not exist or the server is <em>not</em> started, a runtime-error is raised.
    * 
    * If specified, the connection is made for \p user with \p password.
    * 
    * The function is available only if the driver is compiled with mySQL support. In that case, @ref driver_topics_predefined "__MYSQL__" is defined.
    * 
    * The efun triggers a privilege violation ("mysql", "db_connect").
    * 
    * @synopsis{
    * int db_connect(string database)
    * int db_connect(string database, string user)
    * int db_connect(string database, string user, string password)
    * }
    * 
    * @history{
    * introduced (3.2.9)
    * changed (3.2.11) -- adds the privilege violation.
    * }
    * 
    * @see efun::db_affected_rows(), efun::db_conv_string(), efun::db_close(), efun::db_coldefs(), efun::db_exec(), efun::db_error(), efun::db_fetch(), efun::db_handles(), efun::db_insert_id(), master::privilege_violation()
   **/
   int db_connect(string database, string user, string password);
}
