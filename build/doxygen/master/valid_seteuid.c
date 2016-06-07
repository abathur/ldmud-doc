public class master {
   /**
    * Should return 1 if ob is allowed to set its euid to newid.
    * Objects are always allowed to set their euid to 0.
    * 
    * @synopsis{
    * int valid_seteuid(object ob, string newid)
    * }
    * 
    * @see efun::seteuid(), @ref driver_concepts_uids "uids"
   **/
   int valid_seteuid(object ob, string newid);
}
