public class efun {
   /**
    * Set the default runtime limits from the given arguments. The new limits will be in effect as the initial 'max limits' with the next execution thread.
    * 
    * The arguments can be given in two ways: as an array (like the one returned from efun::query_limits(), or as a list of tagged values. The limit settings recognize three special values:
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
    * The efun causes a privilege violation ("set_limits", current_object, limits-array).
    * 
    * @headerfile <rtlimits.h>
    * 
    * @synopsis{
    * void set_limits(int tag, int value, ...)
    * void set_limits(int *limits)
    * }
    * 
    * @usage{
    * Both lines below set a new default eval_cost limit of 200000:
    * 
    * ~~~{.c}
    * set_limits(({ 200000 }))
    * set_limits(LIMIT_EVAL, 200000)
    * 
    * ~~~
    * The lines below both set new eval_cost limit to unlimited, keep the current array size limit, and limit mapping sizes to 5000:
    * 
    * ~~~{.c}
    * set_limits(({ LIMIT_UNLIMITED, LIMIT_KEEP, 5000 }))
    * set_limits(LIMIT_EVAL, LIMIT_UNLIMITED, LIMIT_ARRAY, LIMIT_KEEP,
    *             LIMIT_MAPPING, 5000)
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
    * @see efun::limited(), efun::query_limits()
   **/
   void set_limits(int *limits);
}
