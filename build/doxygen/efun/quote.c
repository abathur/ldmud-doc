public class efun {
   /**
    * @synopsis{
    * mixed quote(mixed)
    * }
    * 
   **/
   mixed quote(mixed);
}
Converts arrays to quoted arrays and strings to symbols.
Symbols and quoted arrays get quoted once more.

EXAMPLES
quote("foo") -> 'foo
quote(({1,2,3})) -> '({1,2,3})

Introduced in @subpage driver_mailto:3.2@70 "3.2@70"

   See Also: 
      efun::symbolp(), efun::unquote()
