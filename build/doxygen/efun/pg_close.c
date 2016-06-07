public class efun {
   /**
    * Close the database connection for the current object, if there is one.
    * 
    * The function is available only if the driver is compiled with
    * PostgreSQL support. In that case, __PGSQL__ is defined.
    * 
    * The efun triggers a privilege violation ("pgsql", "pg_close").
    * 
    * @synopsis{
    * void pg_close()
    * }
    * 
   **/
   void pg_close();
}
