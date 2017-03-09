public class efun {
   /**
    * Create a deep copy of \p value and return it. For arrays and mappings this means that a new array or mapping is created with copies of the original content. Embedded arrays and mappings are truly copied, too.
    * 
    * For other values this function is a no-op.
    * 
    * If DYNAMIC_COST is defined, every nested mapping or array counts towards the evaluation cost in both size and nesting depth.
    * 
    * @synopsis{
    * mixed deep_copy(mixed value)
    * }
    * 
    * @usage{
    * In contrast to the example in efun::copy(), changes to the nested array below are not visible in both copies:
    * 
    * ~~~{.c}
    * mixed *a, *b;
    * 
    * a = ({ 1, ({ 21, 22 }) });
    * b = deep_copy(a);
    * a[0] = -1;
    * a[1][0] = -21;
    * 
    * // a is now   ({ -1, ({ -21, 22 }) })
    * // b is still ({  1, ({  21, 22 }) })
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * introduced (3.2.6)
    * changed (3.2.9) -- added the dynamic cost to the efun
    * }
    * 
    * @see efun::copy()
   **/
   mixed deep_copy(mixed value);
}
