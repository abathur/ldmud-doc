public class efun {
   /**
    * Change the current command giver to \p ob. \p ob may be 0 if you want to 'deactivate' the current command giver.
    * 
    * This efun is not privileged, therefore it should be redefined by a nomask simul_efun which then either completely disables the efun or at least performs some security checks. It is easy to undermine a mudlib's security using this efun.
    * 
    * @synopsis{
    * void set_this_player(object ob)
    * }
    * 
    * @history{
    * introduced (3.2.1)
    * changed (3.2.6) -- added the value 0 as acceptable parameter.
    * }
    * 
    * @see efun::set_this_object(), efun::this_player()
   **/
   void set_this_player(object ob);
}
