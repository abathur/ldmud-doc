public class efun {
   /**
    * This function is connected to the add_action() function. It
    * will set up the command str to trigger a call to the function
    * set up by the previous call to add_action().
    * 
    * This function is now obsolete as the verb can be given directly
    * with add_action(). add_verb() remains for compatibility.
    * 
    * [marion Sun Jan 19 1992 Don't use it. This file is retained
    * because of somewhat nostalgic reasons.]
    * 
    * @synopsis{
    * void add_verb(string str)
    * }
    * 
    * @history{
    * removed (3.3) -- obsoleted by add_action().
    * }
    * 
    * @see efun::add_action(), efun::query_verb(), efun::add_xverb(), efun::remove_action()
   **/
   void add_verb(string str);
}
