public class efun {
   /**
    * Converts arrays to quoted arrays and strings to symbols. Symbols and quoted arrays get quoted once more.
    * 
    * @synopsis{
    * mixed quote(mixed)
    * }
    * 
    * @usage{
    * ~~~{.c}
    * quote("foo") -> 'foo
    * quote(({1,2,3})) -> '({1,2,3})
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * introduced (3.2@70)
    * }
    * 
    * @see efun::symbolp(), efun::unquote()
   **/
   mixed quote(mixed);
}
