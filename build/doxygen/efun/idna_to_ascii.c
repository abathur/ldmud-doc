public class efun {
   /**
    * Convert string \p name from UTF-8 to idna representation (8z punycode).
    * 
    * If an error occurs, an exception is thrown.
    * 
    * The efun is available only if the system supports libidn - in that case @ref driver_topics_predefined "__IDNA__" is defined.
    * 
    * @headerfile <idn.h>
    * 
    * @synopsis{
    * string idna_to_ascii(string name)
    * }
    * 
    * @history{
    * introduced (3.3.713)
    * }
    * 
    * @see efun::convert_charset(), efun::idna_to_ascii(), efun::idna_stringprep()
   **/
   string idna_to_ascii(string name);
}
