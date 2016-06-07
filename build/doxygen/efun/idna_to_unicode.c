public class efun {
   /**
    * @headerfile <idn.h>
    * 
    * @synopsis{
    * string idna_to_unicode(string name)
    * }
    * 
   **/
   string idna_to_unicode(string name);
}
Convert string <name> from idna representation (8z punycode)
to UTF-8.

If an error occurs, an exception is thrown.

The efun is available only if the system supports libidn - in
that case __IDNA__ is defined.

Introduced in LDMud 3.3.713.

   See Also: 
      efun::convert_charset(), efun::idna_to_ascii(), efun::idna_stringprep()
