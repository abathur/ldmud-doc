public class efun {
   /**
    * Returns 1 if <arg> is a symbol.
    * 
    * @synopsis{
    * int symbolp(mixed arg)
    * }
    * 
    * @usage{
    * symbolp('foo) returns 1.
    * }
    * 
    * @history{
    * introduced (3.2@70)
    * }
    * 
    * @see efun::quote(), efun::clonep(), efun::closurep(), efun::floatp(), efun::mappingp(), efun::objectp(), efun::intp(), efun::referencep(), efun::pointerp(), efun::stringp(), efun::structp()
   **/
   int symbolp(mixed arg);
}
