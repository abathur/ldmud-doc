public class efun {
   /**
    * Return the verb of the current command, of 0 if not executing from a command. If \p flag is 0 or not given, the verb as given by the user is returned (this is the first word from the line input by the player, up to but not including the first space or lineend). If \p flag is non-0, the verb as specified in the efun::add_action() statement is returned.
    * 
    * @synopsis{
    * string query_verb(void)
    * string query_verb(int flag)
    * }
    * 
    * @usage{
    * When the user is in the presence of an object defined as:
    * 
    * ~~~{.c}
    * void init() {
    *    ...
    *    add_action("sing","sing");
    *    add_action("sing","chant", 1);
    *    ...
    * }
    * int sing(string str) {
    *    write("Your command was: "+query_verb()+(str ? str : "")+"\n");
    *    write("The action verb was: "+query_verb(1)+(str ? str : "")+"\n");
    *    return 1;
    * }
    * 
    * ~~~
    * the command 'sing ...' will print:
    * 
    * ~~~{.c}
    * Your command was: sing
    * The action verb was: sing
    * 
    * ~~~
    * the command 'chant ...' will print:
    * 
    * ~~~{.c}
    * Your command was: chant
    * The action verb was: chant
    * 
    * ~~~
    * and the command 'chantit ...' will print:
    * 
    * ~~~{.c}
    * Your command was: chantit
    * The action verb was: chant
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * changed (3.2.9) -- added the optional flag argument.
    * }
    * 
    * @see efun::add_action(), efun::query_command()
   **/
   string query_verb(int flag);
}
