public class efun {
   /**
    * Enable next line of user input to be sent to the function \p fun as an argument. Exception: if the next input line starts with a "!", it will be parsed as a command resp. passed to the most recent input_to given with the `INPUT_IGNORE_BANG` flag. The function \p fun may be static, but must not be private (or it won't be found).
    * 
    * @par note: that fun is not called immediately but after pressing the `RETURN` key.
    * 
    * Usually, if input_to is called more than once in the same execution, only the first call has any effect. This behaviour can be modified by specifying the `INPUT_APPEND` flag which will append the given input_to to the already existing input_tos.
    * 
    * Also, if a command given during an input_to (using the "!" escape) issues its own input_to, the previous input_to is suspended until the new input_to has been handled, then the previous one becomes active again.
    * 
    * The optional argument \p flag may be a binary-OR ('|') of the following option values:
    * 
    * `INPUT_NOECHO`  (1):
    *    The line given by the player will not be echoed, and is not seen if snooped.
    *    
    *    A change of this mode not possible with telnet disabled.
    *    
    * `INPUT_CHARMODE`  (2):
    *    The connection is switched from line- into charmode to retrieve a single character(!) from the player.
    *    
    *    Is telnet disabled, then only the handling of the incoming data by the driver is changed - the client program of the player will remain in its current mode.
    *    
    *    After execution of \p fun, the connection is switched back into linemode unless a subsequent `input_to( , 2)` has been issued.
    *    
    *    Lineends are received exactly as the client sent them: "n", "r" followed by "n", or just "r".
    *    
    *    Note that the players frontend is free to stay in linemode all the time: even if you request a single character, the player might be forced to type (and send) that character plus the return key. Usually your function will then receive the complete input line (including the newline character sequence!) in one call.
    *    
    *    If you plan to stay in charmode a longer time , you can reduce the call overhead by using efun::set_combine_charset() to retrieve sequences of certain characters as one string instead of one-by-one. In a screen-oriented editor for example this would be most of the printable characters.
    *    
    * `INPUT_PROMPT` (4):
    *    The argument following the \p flag argument is used as prompt for the input. If this flag is not given, and thus no prompt specified, nothing will be printed.
    *    
    * `INPUT_NO_TELNET` (8):
    *    Modifies the `INPUT_CHARMODE` flag: the driver will switch it's internal handling of incoming data, but not send out any telnet commands to switch the client's behaviour.
    *    
    * `INPUT_APPEND` (16):
    *    Append the input_to to the list of currently pending input_tos (if any).
    *    
    * `INPUT_IGNORE_BANG`  (128):
    *    Input lines starting with '!' (or whatever the input escape character was configured to be) will _not_ be parsed as commands, but are given to the function as well. Usage of this option is privileged.
    *    
    * The optional trailing args will be passed as second and subsequent args to the function fun.
    * 
    * @par limit: In charmode, it is not possible to receive the NUL character and pass it to the mudlib: internally the NUL character has magical properties.
    * 
    * @headerfile <input_to.h>
    * 
    * @synopsis{
    * void input_to(string|closure fun)
    * void input_to(string|closure fun, int flag, ...)
    * void input_to(string|closure fun, int flag, string|closure prompt, ...)
    * }
    * 
    * @usage{
    * When reaching the efun::input_to() statement in the example below, the driver continues executing the function `func()`, but also asks the user for input. When the user enters whatever is asked and presses `RETURN`, the driver will invoke the `enter_name()` function with the entered string as argument:
    * 
    * ~~~{.c}
    * void func() {
    *    ...
    *    input_to("enter_name", INPUT_PROMPT, "Please enter your name:");
    *    // The traditional way of doing this was:
    *    //   write("Please enter your name:");
    *    //   input_to("enter_name");
    *    ...
    * }
    * enter_name(string str) {
    *    write("Is '"+str+"' really your name?? *giggle*\n");
    *    ...
    * }
    * 
    * ~~~
    * This next sequence will queue two input_tos: the input first goes to `enter_firstname()` and when this function is done (including any non-appended input_tos of its own), the next input will go to `enter_lastname()`:
    * 
    * ~~~{.c}
    * void func() {
    *   ..
    *   input_to("enter_firstname");
    *   input_to("enter_lastname, INPUT_APPEND);
    *   ...
    * }
    * 
    * ~~~
    * The list of input_tos is treated as a flat list:
    * 
    * ~~~{.c}
    * void func() {
    *   ..
    *   input_to("func1");
    *   input_to("func2", INPUT_APPEND);
    * }
    * 
    * void func1() {
    *   ..
    *   input_to("func3", INPUT_APPEND);
    * }
    * 
    * void func2() { ... }
    * void func3() { ... }
    * 
    * ~~~
    * This code will result in the functions being called in the order `func(), func1(), func2(), func3();` and not `func(), func1(), func3(), func2()`.
    * 
    * }
    * 
    * @history{
    * changed (3.2.1@93) -- The meaning of the flag parameter was extended.
    * changed (3.2.8) -- added limited "stacking" of input_tos issued from !commands.
    * changed -- the function can be given as a closure.
    * changed (3.2.9/3.3.125) -- added the INPUT_PROMPT flag and argument.
    * changed (3.2.11/3.3.593) -- added the INPUT_NO_TELNET flag.
    * changed (3.2.11/3.3.637) -- added the INPUT_APPEND flag.
    * changed (3.3) -- changed handling of newline sequences in charmode to verbatim passing. Earlier drivers passed an empty string instead.
    * changed -- driver can be configured to use a different input escape character.
    * }
    * 
    * @see master::privilege_violation(), efun::set_combine_charset(), efun::query_input_pending(), efun::find_input_to(), efun::input_to_info(), efun::remove_input_to(), efun::enable_telnet()
   **/
   void input_to(string|closure fun, int flag, string|closure prompt, ...);
}
