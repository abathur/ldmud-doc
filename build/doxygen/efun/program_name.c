public class efun {
   /**
    * Returns the name of the program of \p obj, resp. the name of the program of the current object if \p obj is omitted.
    * 
    * The returned name is usually the name from which the blueprint of \p obj was compiled (the 'load name'), but changes if an object replaces its programs with the efun::replace_program().
    * 
    * As a special case, if \p obj is passed as 0, the function will return 0.
    * 
    * The name always ends in '.c'. It starts with a '/' unless the driver is running in @ref driver_topics_predefined "__COMPAT_MODE__".
    * 
    * @par warning: This efun swaps in the program if it is swapped out.
    * 
    * @synopsis{
    * string program_name()
    * string program_name(object obj)
    * }
    * 
    * @usage{
    * ~~~{.c}
    * object o;
    * o = clone_object("/std/thing");
    * write(program_name(o)); // writes "/std/thing.c" in !compat mode
    *                         // and "std/thing.c"  in compat mode
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * introduced (3.2.6)
    * changed (3.2.9) -- allowed a 0 argument.
    * }
    * 
    * @see efun::clone_object(), efun::clonep(), efun::load_name(), efun::load_object(), efun::object_name(), efun::replace_program()
   **/
   string program_name(object obj);
}
