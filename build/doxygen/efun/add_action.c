public class efun {
   /**
    * Set up a local function fun to be called when user input matches the command cmd. Functions called by a user command will get the arguments as a string. It must then return 0 if it was the wrong command, otherwise 1.
    * 
    * If it was the wrong command, the parser will continue searching for another command, until one returns 1 or give an error message to the user.
    * 
    * For example, there can be a wand and a rod. Both of these objects define as command "wave". One of them will be randomly called first, and it must look at the argument, and match against "wand" or "rod" respectively.
    * 
    * The function associated to a command will be called with a string as argument which stands for the given words behind the typed command. The verb entered can be retrieved using efun::query_verb() efun and is always the first word in the input line up to the first space.
    * 
    * Always have efun::add_action() called only from an applied::init() routine. The object defining these commands must be present to the user, either being the user, being carried by the user, being the room around the user, or being an object in the same room as the user. If the player leaves this vicinity of the object, the actions are automatically removed.
    * 
    * Actions can also be removed on demand with efun::remove_action().
    * 
    * If \p flag is `AA_SHORT` (1), then the arguments may follow the verb without separating space. Any arguments after the first space are passed as argument string.
    * 
    * If \p flag is `AA_NOSPACE` (2), then again the arguments may follow the verb without separating space. In contrast to `AA_SHORT`, all characters following the verb are passed as the argument string. However, note that the characters immediately following the given verb are passed as argument AND as result of efun::query_verb().
    * 
    * If \p flag is `AA_IMM_ARGS` (3), then again the arguments may follow the verb without separating space. All characters following the given verb are passed as argument, and only as argument.
    * 
    * If \p flag is negative, the verb given by the player has to match only the first `abs(flag)` characters of the verb \p cmd.
    * 
    * Never use one of the functions 'create' 'reset' 'init' 'exit' 'heart_beat' etc as the first argument to efun::add_action(). In general, a function with a name defined in /doc/applied should have the behaviour defined there.
    * 
    * @headerfile <commands.h>
    * 
    * @synopsis{
    * void add_action(string|closure fun, string cmd)
    * void add_action(string|closure fun, string cmd, int flag)
    * }
    * 
    * @usage{
    * In this example, `GoInside()` is invoked when the user types `enter`:
    * 
    * ~~~{.c}
    * add_action("GoInside", "enter");
    * 
    * ~~~
    * The `AA_SHORT` flag used below means `DisFunc()` will be called if the user enters any command that _starts_ with `dis`. To get the full first word of the user's command, you have to call efun::query_verb():
    * 
    * ~~~{.c}
    * add_action("DisFunc", "dis", AA_SHORT);
    * 
    * ~~~
    * Similarly, the `AA_NOSPACE` means the function `DisFunc()` will be called for all commands which use `disconnect` or a shortened form like `di`, `dis` or `discon` as verb. The command `disconnecting` would _not_ be recognized. To get the real word which was typed in you have to call efun::query_verb().:
    * 
    * ~~~{.c}
    * add_action("DisFunc", "disconnect", AA_NOSPACE);
    * 
    * ~~~
    * To make the effect of these flags more clear, consider the following commands:
    * 
    * ~~~{.c}
    * add_action("...", "cmd");
    * add_action("...", "xcmd", AA_SHORT);
    * add_action("...", "scmd", AA_NOSPACE);
    * add_action("...", "icmd", AA_IMM_ARGS);
    * 
    * ~~~
    * Next, see the table below for an example of how the driver will parse various commands. In this table, <em>verb</em> is what efun::query_verb() would return, and <em>argument</em> is what would be passed to the command function.
    * 
    * | Command        | Verb      | Argument   |
    * |----------------|-----------|------------|
    * | "cmd"          | "cmd"     | 0          |
    * | "cmd foo bar"  | "cmd"     | "foo bar"  |
    * | "xcmd"         | "xcmd"    | 0          |
    * | "xcmd foo"     | "xcmd"    | "foo"      |
    * | "xcmdfoo"      | "xcmdfoo" | 0          |
    * |                |           |            |
    * | "xcmd foo bar" | "xcmd"    | "foo bar"  |
    * |                |           |            |
    * | "xcmdfoo bar"  | "xcmdfoo" | "bar"      |
    * |                |           |            |
    * | "scmd"         | "scmd"    | 0          |
    * | "scmd foo"     | "scmd"    | " foo"     |
    * | "scmdfoo"      | "scmdfoo" | "foo"      |
    * |                |           |            |
    * | "scmd foo bar" | "scmd"    | " foo bar" |
    * |                |           |            |
    * | "scmdfoo bar"  | "scmdfoo" | "foo bar"  |
    * |                |           |            |
    * | "icmd"         | "icmd"    | 0          |
    * | "icmd foo"     | "icmd"    | " foo"     |
    * | "icmdfoo"      | "icmd"    | "foo"      |
    * | "icmd foo bar" | "icmd"    | " foo bar" |
    * |                |           |            |
    * | "icmdfoo bar"  | "icmd"    | "foo bar"  |
    * 
    * }
    * 
    * @history{
    * changed (3.2@127) -- adds partial support for flag values < 0
    * changed (3.2.8) -- now actually respects flag values < 0
    * changed (3.2.9) -- introduced the AA_IMM_ARGS flag.
    * changed (3.3) -- removed the historical add_action(fun) notation.
    * changed (3.5) -- the function can be given as a closure.
    * }
    * 
    * @see efun::query_verb(), efun::query_command(), efun::remove_action(), applied::init()
   **/
   void add_action(string|closure fun, string cmd, int flag);
}
