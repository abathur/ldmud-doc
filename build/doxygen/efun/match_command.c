public class efun {
   /**
    * Take the command <command>, parse it, and return an array of all
    * matching actions added to <origin> (read: <origin> is the object
    * 'issuing' the command).
    * 
    * Each entry in the result array is itself an array of:
    * 
    * string [CMDM_VERB]:   The matched verb.
    * string [CMDM_ARG]:    The argument string remaining, or 0 if none.
    * object [CMDM_OBJECT]: The object defining the action.
    * string [CMDM_FUN]:    The name of the function to call in
    * 
    *    CMDM_OBJECT, which may be static.
    *    
    * The efun is useful for both debugging, and for implementing your
    * own H_COMMAND handling.
    * 
    * @headerfile <commands.h>
    * 
    * @synopsis{
    * mixed * match_command(string command, object origin)
    * }
    * 
   **/
   mixed * match_command(string command, object origin);
}