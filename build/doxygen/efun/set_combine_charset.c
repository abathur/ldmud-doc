public class efun {
   /**
    * Set the set of characters which can be combined into a single string when already received en-bloc in charmode from the current interactive user.
    * 
    * Non-combinable characters and single received characters are returned as separate strings as usual. The function must be called with the interactive user being the command giver.
    * 
    * The newline 'n' and the NUL character '0' are always non-combinable.
    * 
    * The charset can be given either directly as a string, or indirectly as a bitvector. If given as the number 0, the default combine charset is re-established.
    * 
    * The bitvector is interpreted as an array of 8-bit-values and might contain up to 32 elements. Character n is allowed to be output if `sizeof(bitvector) > n/8 && bitvector[n/8] & (1 << n%8)`.
    * 
    * @synopsis{
    * void set_combine_charset(int *bitvector)
    * void set_combine_charset(string charset)
    * void set_combine_charset(0)
    * }
    * 
    * @usage{
    * ~~~{.c}
    * // In a screen-oriented editor, most of the printable characters
    * // (excluding answers to editor prompts 'j', 'n' and 'q') can be
    * // combined into strings.
    * set_combine_charset("abcdefghijklmoprstuvwxz0123456789"
    *                     "ABCDEFGHIJKLMOPRSTUVWXZ");
    * 
    * // Disable any previous setting.
    * set_combine_charset("");
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * introduced (3.2.8)
    * changed (3.2.10) -- added the ability to reset the charset to the default.
    * }
    * 
    * @see efun::get_combine_charset(), efun::input_to(), efun::set_connection_charset()
   **/
   void set_combine_charset(0);
}
