public class efun {
   /**
    * This privileged efun sets the driver hook 'what' (values are defined in <driver_hook.h>) to 'arg'. The exact meanings and types of 'arg' depend of the hook set. To remove a hook, set 'arg' to 0.
    * 
    * These hooks exist:
    * 
    * `H_MOVE_OBJECT0`
    * `H_MOVE_OBJECT1`
    * 
    * arg: unbound lambda
    * Mandatory hooks implementing the efun::move_object().
    * 
    * `H_LOAD_UIDS`
    * `H_CLONE_UIDS`
    * 
    * arg: unbound lambda or lfun closure
    * Mandatory hooks to determine the (e)uid of new objects.
    * 
    * `H_CREATE_SUPER`
    * `H_CREATE_OB`
    * `H_CREATE_CLONE`
    * `H_RESET`
    * `H_CLEAN_UP`
    * 
    * arg: lambda closure (`H_CLEAN_UP` also accepts a lfun
    *    closure), function name.
    *    
    * Optional hooks for creation/reset/clean up-actions.
    * 
    * `H_DEFAULT_METHOD`
    * arg: lambda closure, lfun closure, function name.
    * Optional hook for default method implementation.
    * 
    * `H_DEFAULT_PROMPT`
    * arg: lambda closure, lfun closure, prompt string.
    * Optional hook for the default command prompt.
    * 
    * `H_PRINT_PROMPT`
    * arg: lambda closure, lfun closure, function name.
    * Optional hook to print the command prompt.
    * 
    * `H_MODIFY_COMMAND`
    * arg: lambda closure, lfun closure, function name, mapping
    * Optional hook for modifying player commands before the
    * parser sees them.
    * 
    * `H_NOTIFY_FAIL`
    * arg: lambda closure, lfun closure, string.
    * Mandatory hook to generate the default message if an entered
    * command couldn't be parsed and no efun::notify_fail() command is
    * in effect.
    * 
    * `H_SEND_NOTIFY_FAIL`
    * arg: lambda closure, lfun closure, string.
    * Optional hook to deliver the notify fail message from a failed
    * command.
    * 
    * `H_NO_IPC_SLOT`
    * arg: string.
    * Optional hook specifying the 'sorry' messages if logins are
    * rejected due to fullness of the mud.
    * 
    * `H_INCLUDE_DIRS`
    * arg: lambda closure, lfun closure, string array.
    * Semi-mandatory hook specifying the directories where <>-type
    * include files are searched.
    * 
    * `H_AUTO_INCLUDE`
    * arg: lambda closure, lfun closure, string
    * Optional hook to specify a string to be included before the
    * source of every compiled LPC object.
    * 
    * `H_TELNET_NEG`
    * arg: lambda closure, lfun closure, string.
    * Optional hook to specifiy how to perform a single telnet
    * negotiation.
    * 
    * `H_NOECHO`
    * arg: lambda closure, lfun closure, string.
    * Optional hook to specifiy how to perform the telnet actions
    * to switch the echo mode (used for e.g. passwords in efun::input_to()).
    * 
    * `H_ERQ_STOP`
    * arg: lambda closure, lfun closure.
    * Optional hook to notify the mudlib about the termination of
    * the erq demon.
    * 
    * `H_MSG_DISCARDED`
    * arg: lambda closure, lfun closure, string
    * Optional hook to specify a message or take other measures
    * when a message had to be discarded.
    * 
    * See @ref driver_hook_overview "hook" for a detailed discussion.
    * 
    * @headerfile <driver_hook.h>
    * 
    * @synopsis{
    * void set_driver_hook(int what, closure arg)
    * void set_driver_hook(int what, string arg)
    * void set_driver_hook(int what, string *arg)
    * }
    * 
    * @history{
    * introduced (3.2.1@1) -- as efun309(),
    * changed (3.2.1@13) -- renamed to set_driver_hook.
    * }
    * 
    * @see @ref driver_hook_overview "hook"
   **/
   void set_driver_hook(int what, string *arg);
}
