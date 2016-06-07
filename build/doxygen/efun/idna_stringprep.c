public class efun {
   /**
    * @headerfile <idn.h>
    * 
    * @synopsis{
    * string idna_stringprep(string str, int profile, int flags)
    * }
    * 
   **/
   string idna_stringprep(string str, int profile, int flags);
}
Prepare the UTF-8 string <str> according to the stringprep
<profile> (see also libidn stringprep(3)).

<profile> and <flags> are one of the values defined in <idn.h>.

If an error occurs, an exception is thrown.

The efun is available only if the system supports libidn - in
that case __IDNA__ is defined.

Introduced in LDMud 3.3.713.

   See Also: 
      efun::convert_charset(), efun::idna_to_ascii(), efun::idna_to_unicode()
