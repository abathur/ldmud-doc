public class efun {
   /**
    * Prepare the UTF-8 string \p str according to the stringprep \p profile (see also libidn stringprep(3)).
    * 
    * \p profile and \p flags are one of the values defined in `idn.h`.
    * 
    * If an error occurs, an exception is thrown.
    * 
    * The efun is available only if the system supports libidn - in that case @ref driver_topics_predefined "__IDNA__" is defined.
    * 
    * @headerfile <idn.h>
    * 
    * @synopsis{
    * string idna_stringprep(string str, int profile, int flags)
    * }
    * 
    * @history{
    * introduced (3.3.713)
    * }
    * 
    * @see efun::convert_charset(), efun::idna_to_ascii(), efun::idna_to_unicode()
   **/
   string idna_stringprep(string str, int profile, int flags);
}
