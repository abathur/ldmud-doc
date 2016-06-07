public class efun {
   /**
    * Encode the <value> into a string suitable for restoration with
    * restore_value() and return it.
    * 
    * The optional <format> argument determines the format of the savefile
    * to be written:
    * 
    * -1: use the driver's native format (default).
    *    0: original format, used by Amylaar LPMud and LDMud <= 3.2.8 .
    *    1: LDMud >= 3.2.9: no-lambda closures, symbols, quoted arrays
    *    
    *       can be saved.
    *       
    *    2: LDMUd >= 3.5.0: floats are stored in a different way, which is
    *       more compact and can store the new floats losslessly.
    *       
    * It is recommended to use version 2 or higher.
    * 
    * The created string consists of two lines, each terminated with
    * a newline character: the first line describes the format used to
    * save the value in the '#x:y' notation; the second line is the
    * representation of the value itself.
    * 
    * The format of the encoded value and of the format line matches
    * the format used by save_object() and restore_object().
    * 
    * @synopsis{
    * string save_value(mixed value)
    * string save_value(mixed value, int format)
    * }
    * 
   **/
   string save_value(mixed value, int format);
}
