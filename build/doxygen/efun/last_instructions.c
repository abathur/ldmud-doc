public class efun {
   /**
    * Returns an array showing the 'length' last executed instructions in disassembled form. If 'verbose' is non-zero (the default), line number information are also included. Each string is built as this:
    * 
    * ~~~{.c}
    * Opcode-Address: Opcode Operand Mnemonic (Stackdepth) Linenumber
    * 
    * ~~~
    * The Stackdepth information consists of two numbers `<em>rel</em>:<em>abs</em>` <em>rel</em> is the relative stack usage in this function, <em>abs</em> is the absolute stack usage.
    * 
    * The linenumber information is appended if requested and a new source line is reached. Also, calls between objects produce a:
    * 
    * ~~~{.c}
    * Objectname Programname Linenumber
    * 
    * ~~~
    * entry in the resulting array (in verbose mode only).
    * 
    * There is a preconfigured upper limit for the backtrace.
    * 
    * @synopsis{
    * string * last_instructions(int length, int verbose)
    * }
    * 
    * @history{
    * introduced (3.2.1@34)
    * changed (3.2.8) -- added absolute stack depth information
    * }
    * 
    * @see efun::debug_message()
   **/
   string * last_instructions(int length, int verbose);
}
