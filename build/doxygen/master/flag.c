public class master {
   /**
    * Evaluate an argument given as option '-f' to the driver.
    * If several '-f' options are given, this function will be
    * called sequentially with all given arguments.
    * This function can be used to pass the master commands via
    * arguments to the driver. This is useful when building a new
    * mudlib from scratch. It is called only when the system is
    * started.
    * 
    * @synopsis{
    * void flag(string arg)
    * }
    * 
    * @usage{
    * // The code given implements these commands:
    * //  '-fcall <ob> <fun> <arg>': call function <fun> in object <ob> with
    * //                                argument <arg>.
    * //  '-fshutdown': shutdown the system immediately.
    * // Thus, starting the driver as
    * //         'parse "-fcall foo bar Yow!" -fshutdown' would
    * // first do foo->bar("Yow!") and then shut down the system.
    * 
    * {
    *   string obj, fun, rest;
    * 
    *   if (arg == "shutdown")
    *   {
    *     shutdown();
    *     return;
    *   }
    *   if (sscanf(arg, "call %s %s %s", obj, fun, rest) >= 2)
    *   {
    *     write(obj+"->"+fun+"(\""+rest+"\") = ");
    *     write(call_other(obj, fun, rest));
    *     write("\n");
    *     return;
    *   }
    *   write("master: Unknown flag "+arg+"\n");
    * }
    * }
    * 
    * @see @ref driver_master_master "master"
   **/
   void flag(string arg);
}