public class efun {
   /**
    * Removes a quote from quoted arrays and symbols. When the last quote from a symbol is removed, the result is a string.
    * 
    * @synopsis{
    * mixed * unquote(quoted_array)
    * string|symbol unquote(symbol)
    * }
    * 
    * @usage{
    * ~~~{.c}
    * unquote('foo)         // returns "foo"
    * unquote( '({1,2,3}) ) // returns ({1,2,3})
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * introduced (3.2.9)
    * }
    * 
    * @see efun::quote(), efun::symbolp()
   **/
   string|symbol unquote(symbol);
}
