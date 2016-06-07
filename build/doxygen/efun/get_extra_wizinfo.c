public class efun {
   /**
    * @synopsis{
    * mixed get_extra_wizinfo(object wiz)
    * mixed get_extra_wizinfo(string wiz)
    * mixed get_extra_wizinfo(int wiz)
    * }
    * 
   **/
   mixed get_extra_wizinfo(int wiz);
}
Returns the 'extra' information that was set for the given
wizard <wiz> in the wizlist.

If <wiz> is an object, the entry of its creator (uid) is used.
If <wiz> is a string (a creator aka uid), it names the entry
to use.
If <wiz> is the number 0, the data is get from the default wizlist
entry.

The function causes a privilege violation.

   See Also: 
      efun::wizlist_info(), efun::set_extra_wizinfo()
