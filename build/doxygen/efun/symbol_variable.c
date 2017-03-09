public class efun {
   /**
    * Constructs an identifier (lfun) closure from the global variable \p arg of the current program. The variable may be given as a symbol, by name, or by its ordinal number in the object's variable table.
    * 
    * If there is no such variable, or if it is not visible outside the object, 0 is returned.
    * 
    * If the argument is an integer, and the variable is both inherited and private in the inherited object (i.e. hidden), then a privilege violation will occur.
    * 
    * @synopsis{
    * closure symbol_variable(string arg)
    * closure symbol_variable(symbol arg)
    * closure symbol_variable(int arg)
    * }
    * 
    * @usage{
    * ~~~{.c}
    * int base;
    * int var;
    * symbol_variable("var") // #'<this_object>->var
    * symbol_variable(0)     // #'<this_object>->base
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * introduced (3.2.1@8)
    * }
    * 
    * @see efun::lambda(), efun::quote(), efun::symbol_function()
   **/
   closure symbol_variable(int arg);
}
