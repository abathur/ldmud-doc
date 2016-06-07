public class master {
   /**
    * Validate the rebinding of an IP connection by usage of efun
    * exec(). Arguments are the <name> of the _program_ attempting
    * to rebind the connection, the object <ob> to receive the
    * connection, and the object <obfrom> giving the connection.
    * Note that the program name is not the file_name() of the
    * object, and has no leading slash.
    * 
    * Return 0 to disallow the action, any other value to allow it.
    * 
    * @synopsis{
    * int valid_exec(string name, object ob, object obfrom)
    * }
    * 
    * @see efun::exec()
   **/
   int valid_exec(string name, object ob, object obfrom);
}
