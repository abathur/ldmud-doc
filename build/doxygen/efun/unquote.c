public class efun {
   /**
    * Removes a quote from quoted arrays and symbols. When the
    * last quote from a symbol is removed, the result is a string.
    * 
    * @synopsis{
    * mixed * unquote(quoted_array)
    * string|symbol unquote(symbol)
    * }
    * 
    * @usage{
    * unquote('foo) -> "foo"
    * unquote( '({1,2,3}) ) -> ({1,2,3})
    * }
    * 
   **/
   string|symbol unquote(symbol);
}
