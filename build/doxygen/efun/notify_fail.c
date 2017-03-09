public class efun {
   /**
    * Store \p str as the error message given instead of the default message "What ?". The result is always 0.
    * 
    * If a closure is given, it is executed to return the error message string, but not before all attempts to execute the commandline failed (read: not at the time of the call to efun::notify_fail()). The closure receives as argument the original commandgiver; usually it is identical to `this_player()`, unless @ref driver_hook_modify_command "H_MODIFY_COMMAND" changed that.
    * 
    * If efun::notify_fail() is called more than once for this command, only the last call will be used. However, calls to efun::notify_fail() in nested commands have no effect on this command.
    * 
    * @synopsis{
    * int notify_fail(string str)
    * int notify_fail(closure cl)
    * }
    * 
    * @usage{
    * The idea of this function is to give better error messages instead of simply 'What ?'.
    * 
    * A naive to write a message when a simple command fails is:
    * 
    * ~~~{.c}
    * write(message);
    * return 1;
    * 
    * ~~~
    * Unfortunately, this message will print before other objects get a chance to evaluate the verb. It is better to use:
    * 
    * ~~~{.c}
    * return notify_fail(message);
    * 
    * ~~~
    * This way, the driver only prints a single failure message--and only if the verb fails all of the objects that get a chance to handle it.
    * 
    * }
    * 
    * @history{
    * changed (3.2.6) -- return type from void to int.
    * changed (3.2.7) -- notify-fail settings are saved over nested commands, and NPCs can see their notify-fail messages.
    * }
    * 
    * @see efun::add_action(), efun::command(), efun::query_verb(), efun::query_command(), efun::query_notify_fail(), @ref driver_hook_overview "hook"
   **/
   int notify_fail(closure cl);
}
