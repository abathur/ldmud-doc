public class efun {
   /**
    * @synopsis{
    * int command(string str)
    * int command(string str, object ob)
    * }
    * 
   **/
   int command(string str, object ob);
}
Execute str as a command given directly by the user. Any
effects of the command will apply to the current object,
or to the given <ob>ject.

Return value is 0 for failure. Otherwise a numeric value is
returned which tells the evaluation cost. Bigger number means
higher cost.  The evaluation cost is approximately the number
of LPC machine code instructions executed.

If command() is called on another object, it is not possible
to call static functions in this way, to give some protection
against illegal forces.

Commands are stacked, meaning that after the given command <str>
has finished, the old settings of this_player(), query_verb()
etc, are restored.

Up to 3.2.6 in native mode, commands could be applied to the current
object only.
Since 3.2.7, commands are stacked.

   See Also: 
      efun::command_stack(), efun::notify_fail(), efun::enable_commands(), efun::get_eval_cost()
