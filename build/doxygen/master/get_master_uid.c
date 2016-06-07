public class master {
   /**
    * Return the string to be used as root-uid.
    * Under !strict_euids, the function is expendable.
    * 
    * @synopsis{
    * string get_master_uid(void)
    * }
    * 
    * @history{
    * introduced (3.2.1@40) -- replaces get_root_uid().
    * }
    * 
    * @see master::get_bb_uid(), master::get_master_uid(), @ref driver_concepts_uids "uids", master::creator_file(), efun::creator()
   **/
   string get_master_uid(void);
}
