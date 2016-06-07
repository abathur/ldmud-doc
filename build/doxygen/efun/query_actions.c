public class efun {
   /**
    * query_actions takes either an object or a filename as first
    * argument and a bitmask (int) or string as a second argument.
    * If the second argument is a string, query_actions() will return
    * an array containing information (see below) on the verb or
    * zero if the living object "ob" cannot use the verb. If the
    * second argument is a bitmask, query_actions() will return a
    * flat array containing information on all verbs added to ob.
    * The second argument is optional (default is QA_VERB).
    * 
    * QA_VERB       ( 1):  the verb
    * QA_TYPE       ( 2):  type
    * QA_SHORT_VERB ( 4):  short_verb
    * QA_OBJECT     ( 8):  object
    * QA_FUNCTION   (16): function
    * 
    * "type" is one of the values defined in <sent.h>
    * (which is provided with the parser source).
    * 
    * SENT_PLAIN        added with add_action (fun, cmd);
    * SENT_SHORT_VERB   added with add_action (fun, cmd, AA_SHORT);
    * SENT_NO_SPACE     added with add_action (fun, AA_NOSPACE);
    * SENT_MARKER       internal, won't be in the returned array
    * negative value: The verb given by the player has to match only
    * 
    * the leading -<value> characters of the action's verb.
    * 
    * @headerfile <sent.h>
    * 
    * @headerfile <commands.h>
    * 
    * @synopsis{
    * mixed * query_actions(object ob, mixed mask_or_verb)
    * }
    * 
    * @see efun::add_action(), applied::init()
   **/
   mixed * query_actions(object ob, mixed mask_or_verb);
}
