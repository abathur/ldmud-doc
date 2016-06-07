public class efun {
   /**
    * Give the text of the current command, or 0 if not executing
    * from a command.
    * 
    * The text is the command as seen by the parser, ie. after
    * modify_command and after stripping trailing spaces.
    * 
    * query_command() returns 0 when invoked by a function which was started
    * by a call_out or the heart beat.  Also when a user logs in
    * query_command() returns 0.
    * 
    * @synopsis{
    * string query_command(void)
    * }
    * 
    * @usage{
    * void init() {
    * 
    * ...
    * add_action("sing","sing");
    * ...
    * }
    * int sing(string str) {
    * write("Your command was:"+query_command()+"n");
    * return 1;
    * }
    * When ever you type "sing ..." you get "Your command was: sing ...".
    * }
    * 
    * @see efun::add_action(), efun::query_verb()
   **/
   string query_command(void);
}
