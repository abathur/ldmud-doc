public class efun {
   /**
    * Returns 1 if \p value is a symbol.
    * 
    * @synopsis{
    * int symbolp(mixed value)
    * }
    * 
    * @usage{
    * `symbolp('foo) // returns 1.`
    * 
    * }
    * 
    * @history{
    * introduced (3.2@70)
    * }
    * 
    * @see efun::quote(), efun::clonep(), efun::closurep(), efun::floatp(), efun::mappingp(), efun::objectp(), efun::intp(), efun::referencep(), efun::pointerp(), efun::stringp(), efun::structp()
   **/
   int symbolp(mixed value);
}
