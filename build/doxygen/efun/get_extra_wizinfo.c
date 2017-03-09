public class efun {
   /**
    * Returns the 'extra' information that was set for the given wizard \p wiz in the wizlist.
    * 
    * The function causes a privilege violation.
    * 
    * @synopsis{
    * mixed get_extra_wizinfo(object wiz)
    * mixed get_extra_wizinfo(string wiz)
    * mixed get_extra_wizinfo(int wiz)
    * }
    * 
    * @param wiz the entry of its creator (uid) is used
    * @param wiz a creator (aka uid) that names the entry to use
    * @param wiz Uses the given wizlist entry (or the default entry, if the number is 0)

    * @see efun::wizlist_info(), efun::set_extra_wizinfo()
   **/
   mixed get_extra_wizinfo(int wiz);
}
