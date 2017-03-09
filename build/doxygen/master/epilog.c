public class master {
   /**
    * Perform final actions before opening the system to users.
    * 
    * The argument is the number of -e options that were given to the parser on the commandline. Normally it is just 0 or 1. The function should return an array of strings, which traditionally denote the objects to be preloaded with master::preload(). Any other return value is interpreted as "no object to preload". The resulting strings will be passed one at a time as arguments to master::preload().
    * 
    * @synopsis{
    * string *epilog(int eflag)
    * }
    * 
    * @see master::preload()
   **/
   string *epilog(int eflag);
}
