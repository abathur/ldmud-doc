public class efun {
   /**
    * @synopsis{
    * void set_this_player(object ob)
    * }
    * 
   **/
   void set_this_player(object ob);
}
Change the current command giver to <ob>. <ob> may be 0 if
you want to 'deactivate' the current command giver.

This efun is not privileged, therefore it should be redefined
by a nomask simul_efun which then either completely disables
the efun or at least performs some security checks.
It is easy to undermine a mudlib's security using this efun.

Introduced in 3.2.1.
LDMud 3.2.6 added the value 0 as acceptable parameter.

   See Also: 
      efun::set_this_object(), efun::this_player()
