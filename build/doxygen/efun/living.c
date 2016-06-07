public class efun {
   /**
    * Return true if ob is a living object (that is,
    * enable_commands() has been called from inside the ob).
    * ob may be 0.
    * 
    * @synopsis{
    * int living(object ob)
    * }
    * 
    * @usage{
    * living(this_player())
    * }
    * 
    * @see efun::enable_commands()
   **/
   int living(object ob);
}
