public class efun {
   /**
    * Call the function \p fun with any given \p args as parameters, and execute it with the given runtime limits.
    * 
    * After the function exits, the currently active limits are restored. Result of the efun is the result of the closure call.
    * 
    * The runtime limits can be given in two ways: as an array (like the one returned from efun::query_limits(), or as a list of tagged values. If the efun is used without any limit specification, all limits are supposed to be 'unlimited'.
    * 
    * The limit settings recognize three special values:
    * 
    * - `LIMIT_UNLIMITED`: the limit is deactivated
    * - `LIMIT_KEEP`:      the former setting is kept
    * - `LIMIT_DEFAULT`:   the 'global' default setting is used.
    * 
    * For `LIMIT_COST`, the special values have these meaning:
    * 
    * - `LIMIT_UNLIMITED`: at maximum 1 tick is accounted
    * - `LIMIT_KEEP`:      `LIMIT_COST` is set to 0
    * - `LIMIT_DEFAULT`:   `LIMIT_COST` is set to -100
    * 
    * The efun causes a privilege violation ("limited", current_object, fun, limits-array).
    * 
    * @headerfile <rtlimits.h>
    * 
    * @synopsis{
    * mixed limited(closure fun)
    * mixed limited(closure fun, int tag, int value, ...)
    * mixed limited(closure fun, int *limits)
    * mixed limited(closure fun, int *limits, mixed *args)
    * }
    * 
    * @usage{
    * Execute function with no limits at all:
    * 
    * ~~~{.c}
    * limited(#'func)
    * 
    * ~~~
    * Executes func with an eval_cost limit of 200000, and calls func as `<func>("foo")`:
    * 
    * ~~~{.c}
    * limited(#'func, ({ 200000 }), "foo")
    * 
    * ~~~
    * Executes func with an eval_cost limit of 200000, and calls func as `<func>("foo")`:
    * 
    * ~~~{.c}
    * limited(lambda(0, ({#'func, "foo"})), LIMIT_EVAL, 200000)
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * introduced (3.2.7)
    * changed (3.3.563) -- added LIMIT_COST.
    * changed (3.3.677) -- added LIMIT_MAPPING_KEYS, LIMIT_MAPPING_SIZE.
    * changed (3.5.0) -- added LIMIT_MEMORY.
    * }
    * 
    * @see efun::query_limits(), efun::set_limits()
   **/
   mixed limited(closure fun, int *limits, mixed *args);
}
