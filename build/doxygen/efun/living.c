public class efun {
   /**
    * Return true if \p ob is a living object (that is, efun::enable_commands() has been called from inside the \p ob). \p ob may be 0.
    * 
    * @synopsis{
    * int living(object ob)
    * }
    * 
    * @usage{
    * `living(this_player())`
    * 
    * }
    * 
    * @see efun::enable_commands()
   **/
   int living(object ob);
}
