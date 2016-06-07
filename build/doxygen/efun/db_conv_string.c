public class efun {
   /**
    * Convert the string <str> into a string that is correctly interpretated
    * for usage as a string in db_exec(), e.g. ' is replaced with ' and so
    * on.
    * 
    * The function is available only if the driver is compiled with
    * mySQL support. In that case, __MYSQL__ is defined.
    * 
    * @synopsis{
    * string db_conv_string(string str)
    * }
    * 
   **/
   string db_conv_string(string str);
}
