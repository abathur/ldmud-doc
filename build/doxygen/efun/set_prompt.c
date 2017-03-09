public class efun {
   /**
    * Set the prompt given by the first argument for the interactive object instead of the default prompt. If the second argument is omitted, `this_player()` is used as default. The first arg can be a string or a closure.
    * 
    * The result returned is the old prompt.
    * 
    * If the first arg is the number 0, the prompt is not changed, just returned.
    * 
    * @synopsis{
    * string set_prompt(mixed prompt, object ob)
    * }
    * 
    * @see @ref driver_hook_overview "hook"
   **/
   string set_prompt(mixed prompt, object ob);
}
