public class efun {
   /**
    * returns true if arg was passed by reference to the current function, instead of the usual call-by-value.
    * 
    * Note that arg has to be passed by reference to the efun, a.g. `referencep(&x)`.
    * 
    * @synopsis{
    * int referencep(mixed arg)
    * }
    * 
    * @see @ref driver_syntax_references "reference", efun::clonep(), efun::closurep(), efun::floatp(), efun::mappingp(), efun::objectp(), efun::intp(), efun::pointerp(), efun::stringp(), efun::symbolp(), efun::structp()
   **/
   int referencep(mixed arg);
}
