public class master {
   /**
    * This function is called to let the mudlib handle a runtime warning, e.g. by logging it to a database.
    * 
    * - \p msg is the warning message.
    * - \p curobj is the name of the current object which caused the message (the object itself might already be destructed), or 0 if there is none.
    * - \p prog, \p line determine the name of the program and the line where the error occured if the current object exists, otherwise they are 0.
    * - \p inside_catch : != 0 if the warning occurs inside a efun::catch().
    * 
    * @par limit: The driver is limited to three nested warnings, to prevent an endless recursion in case master::runtime_warning() itself causes warnings.
    * 
    * @synopsis{
    * void runtime_warning(string msg, string curobj, string prog, int line, int inside_catch)
    * }
    * 
    * @history{
    * introduced (3.3.551)
    * changed (3.3.705) -- added the inside_catch argument.
    * }
    * 
    * @see master::runtime_error()
   **/
   void runtime_warning(string msg, string curobj, string prog, int line, int inside_catch);
}
