public class efun {
   /**
    * Execute str as a command given directly by the user. Any effects of the command will apply to the current object, or to \p ob.
    * 
    * Return value is 0 for failure. Otherwise a numeric value is returned which tells the evaluation cost. Bigger number means higher cost. The evaluation cost is approximately the number of LPC machine code instructions executed.
    * 
    * If efun::command() is called on another object, it is not possible to call static functions in this way, to give some protection against illegal forces.
    * 
    * Commands are stacked, meaning that after the given command \p str has finished, the old settings of efun::this_player(), efun::query_verb() etc, are restored.
    * 
    * @synopsis{
    * int command(string str)
    * int command(string str, object ob)
    * }
    * 
    * @history{
    * changed (3.2.6) -- in native mode, commands are no longer limited to the current object only.
    * changed (3.2.7) -- commands are stacked.
    * }
    * 
    * @see efun::command_stack(), efun::notify_fail(), efun::enable_commands(), efun::get_eval_cost()
   **/
   int command(string str, object ob);
}
