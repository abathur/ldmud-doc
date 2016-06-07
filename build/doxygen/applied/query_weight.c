public class applied {
   /**
    * In compat mode this lfun is used by efun::transfer(). Note that no set_weight() is required by the parser.
    * 
    * @synopsis{
    * int query_weight(void)
    * }
    * 
    * @history{
    * deprecated (3.3) -- because transfer() has been deprecated.
    * }
    * 
    * @see efun::transfer(), applied::add_weight()
   **/
   int query_weight(void);
}
