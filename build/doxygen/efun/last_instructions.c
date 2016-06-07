public class efun {
   /**
    * Returns an array showing the 'length' last executed
    * instructions in disassembled form. If 'verbose' is non-zero
    * (the default), line number information are also included.
    * Each string is built as this:
    * 
    * Opcode-Address: Opcode Operand Mnemonic (Stackdepth) Linenumber
    * 
    * The Stackdepth information consists of two numbers <rel>:<abs>:
    * <rel> is the relative stack usage in this function, <abs> is the
    * absolute stack usage.
    * 
    * The linenumber information is appended if requested and a new
    * source line is reached. Also, calls between objects produce a
    * 
    * Objectname Programname Linenumber
    * 
    * entry in the resulting array (in verbose mode only).
    * 
    * There is a preconfigured upper limit for the backtrace.
    * 
    * @synopsis{
    * string * last_instructions(int length, int verbose)
    * }
    * 
   **/
   string * last_instructions(int length, int verbose);
}
