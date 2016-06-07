public class efun {
   /**
    * This function is connected to the add_action() function. It
    * will set up the command str to trigger a call to the function
    * set up by the previous call to add_action().
    * 
    * add_xverb() differs from add_verb() in that only leading
    * characters of the input line must match with str. It basically
    * is the same as setting flag in add_action().
    * 
    * [marion Sun Jan 19 1992 Don't use it. This file is retained
    * because of somewhat nostalgic reasons.]
    * 
    * @synopsis{
    * void add_xverb(string str)
    * }
    * 
    * @history{
    * removed (3.3) -- obsoleted by add_action().
    * }
    * 
    * @see efun::add_action(), efun::query_verb(), efun::add_verb()
   **/
   void add_xverb(string str);
}
