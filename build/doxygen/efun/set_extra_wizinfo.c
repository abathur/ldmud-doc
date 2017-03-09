public class efun {
   /**
    * Set the value \p extra as the 'extra' information for the wizlist entry of \p wiz.
    * 
    * - If \p wiz is an object, the entry of its creator (uid) is used.
    * - If \p wiz is a string (a creator aka uid), it names the entry to use.
    * - If \p wiz is the number 0, the data is set in the default wizlist entry. It can be used to store data for the lifetime of this driver run, like the time of the last reboot.
    * 
    * The \p extra argument may be any value.
    * 
    * The function causes a privilege violation.
    * 
    * @synopsis{
    * void set_extra_wizinfo(object wiz, mixed extra)
    * void set_extra_wizinfo(string wiz, mixed extra)
    * void set_extra_wizinfo(int    wiz, mixed extra)
    * }
    * 
    * @see efun::get_extra_wizinfo(), efun::set_extra_wizinfo_size(), efun::wizlist_info()
   **/
   void set_extra_wizinfo(int    wiz, mixed extra);
}
