public class efun {
   /**
    * Returns the number of values per key of mapping <map>.
    * If <map> is 0, the result is 0.
    * 
    * @synopsis{
    * int widthof(mapping map)
    * }
    * 
   **/
   int widthof(mapping map);
}
EXAMPLES
   mapping m = ([ "foo": 1,2 ]);
   widthof(m)  --> returns 2
