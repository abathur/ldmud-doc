public class master {
   /**
    * Validate the execution of a privileged operation. op denotes the requested operation, who is the object requesting the operation (file_name or object pointer), \p arg and \p arg2 are additional arguments, depending on the operation.
    * 
    * The function should return >0 to grant the privilege, 0 to indicate that the caller was probably misled and the error might be fixed, and anything else to indicate a real violation that will be handled as run time error.
    * 
    * The privileged operations are:
    * 
    * attach_erq_demon
    * Attach the erq demon to object \p arg with  flag \p arg2.
    * 
    * bind_lambda
    * Bind a lambda-closure to object \p arg.
    * 
    * call_out_info
    * Return an array with all call_out informations.
    * 
    * configure_interactive
    * Set option \p arg2 with value \p arg3 as default (`arg==0`) or for object \p arg.
    * 
    * configure_driver
    * Set option `arg1` to value(s) \p arg2.
    * 
    * enable_telnet
    * Enable/disable telnet (\p arg2) for object \p arg.
    * 
    * execute_command
    * Execute command string \p arg2 for the object \p arg.
    * 
    * erq
    * At the request \p arg2 is to be sent to the erq-demon by the object \p who.
    * 
    * garbage_collection
    * Object \p who calls the efun::garbage_collection() with \p arg as filename and \p arg2 as flag.
    * 
    * input_to
    * Object \p who redirects the next input from commandgiver \p arg, using \p arg2 as value for the flags. This is used for flag values including the 'no bang' option.
    * 
    * limited
    * Execute \p arg with reduced/changed limits \p arg2 (as return by efun::query_limits()).
    * 
    * mysql
    * Object \p who attempted to execute mySQL efun \p arg.
    * 
    * pgsql
    * Object \p who attempted to execute Postgres efun \p arg.
    * 
    * net_connect
    * Attempt to open a connection to host \p arg, port \p arg2.
    * 
    * nomask simul_efun
    * Attempt to get an efun \p arg via efun:: when it is shadowed by a nomask type simul_efun.
    * 
    * rename_object
    * The object \p who tries to rename the object \p arg to the name \p arg2.
    * 
    * send_udp
    * Send UDP-data to host \p arg.
    * 
    * get_extra_wizinfo
    * Get the additional wiz-list info for user \p arg.
    * 
    * set_extra_wizinfo
    * Set the additional wiz-list info for user \p arg.
    * 
    * set_extra_wizinfo_size
    * Set the size of the additional user info in the wiz-list to \p arg.
    * 
    * set_driver_hook
    * Set hook \p arg to \p arg2.
    * 
    * set_limits
    * Set limits to \p arg (as returned by efun::query_limits()).
    * 
    * set_max_commands
    * Set the max. number of commands interactive object \p arg can issue per second to \p arg2.
    * 
    * set_this_object
    * Set `this_object()` to \p arg.
    * 
    * shadow_add_action
    * Add an action to function \p arg2 of object \p arg from the shadow \p who which is shadowing \p arg.
    * 
    * shutdown
    * Object \p who calls the efun shutdown with \p arg as argument.
    * 
    * sqlite_pragma
    * Execute pragma statement in SQLite.
    * 
    * symbol_variable
    * Attempt to make a symbol from a hidden inherited variable. \p arg is the object in question, \p arg2 the number of the variable in the variable table.
    * 
    * variable_list
    * An attempt to return the variable values of object \p arg is made from a different object \p who.
    * 
    * wizlist_info
    * Return an array with all wiz-list information.
    * 
    * efun::call_out_info() can return the arguments to functions and lambda closures to be called by efun::call_out(); you should consider that read access to closures, mappings and arrays means write access and/or other privileges. efun::wizlist_info() will return an array which holds, among others, the extra wizlist field. While a toplevel array, if found, will be copied, this does not apply to nested arrays or to any mappings. You might also have some sensitive closures there. efun::send_udp() should be watched as it could be abused. The xxx_extra_wizinfo operations are necessary for a proper wizlist and should therefore be restricted to admins. All other operations are potential sources for direct security breaches - any use of them should be scrutinized closely.
    * 
    * @synopsis{
    * int privilege_violation(string op, mixed who, mixed arg, mixed arg2, mixed arg3)
    * }
    * 
    * @history{
    * changed (3.2.10) -- added the "enable_telnet", "net_connect", "set_max_commands" and "variable_list" violations.
    * changed (3.3.563) -- added the passing of the limits to the "limited" and "set_limits".
    * changed (3.2.11/3.3.640) -- added the "mysql" violation.
    * changed (3.3.717) -- added the "sqlite_pragma" violation.
    * }
    * 
    * @see efun::net_connect(), efun::send_erq(), efun::set_this_object(), efun::rename_object(), efun::call_out_info(), efun::shadow(), efun::add_action(), efun::bind_lambda(), efun::send_udp(), efun::input_to(), efun::execute_command(), efun::variable_list(), efun::enable_telnet()
   **/
   int privilege_violation(string op, mixed who, mixed arg, mixed arg2, mixed arg3);
}
