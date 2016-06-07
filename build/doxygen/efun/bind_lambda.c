public class efun {
   /**
    * Binds an unbound lambda closure to an object and return it.
    * The efun can also be used to rebind an efun-, simul-efun
    * or operator closure to a different object.
    * 
    * If the optional argument ob is not this_object(), the privilege
    * violation ("bind_lambda", this_object(), ob) occurs.
    * 
    * @synopsis{
    * closure bind_lambda(closure, object ob)
    * }
    * 
    * @history{
    * introduced (3.2@82)
    * }
    * 
    * @see efun::lambda(), efun::unbound_lambda(), efun::apply(), efun::funcall(), @ref driver_LPC_closures "closures"
   **/
   closure bind_lambda(closure, object ob);
}
