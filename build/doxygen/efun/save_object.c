public class efun {
   /**
    * Encode the saveable variables of the current object into a string.
    * 
    * In the first form, the string is written to the file <name>.
    * A suffix ".c" will be stripped from the name, the suffix ".o"
    * may be added by the master object during the check in
    * valid_read(). Result is 0 if the save file could be created,
    * and non-zero on a non-fatal error (file could not be written,
    * or current object is destructed).
    * 
    * In the second form the string is returned directly. If the
    * object is destructed, the result is 0.
    * 
    * In both forms, the optional <format> argument determines the
    * format of the savefile to be written:
    * 
    * -1: use the driver's native format (default).
    *    0: original format, used by Amylaar LPMud and LDMud <= 3.2.8 .
    *    1: LDMud >= 3.2.9: non-lambda closures, symbols, quoted arrays
    *    
    *       can be saved.
    *       
    *    2: LDMUd >= 3.5.0: floats are stored in a different way, which is
    *       more compact and can store the new floats losslessly.
    *       
    * It is recommended to use version 2 or higher.
    * 
    * A variable is considered 'saveable' if it is not declared
    * as 'nosave' or 'static'.
    * 
    * Only lfuns bound to the current object can be saved.
    * 
    * @synopsis{
    * int save_object(string name [, int format])
    * string save_object([int format])
    * }
    * 
   **/
   string save_object([int format]);
}
