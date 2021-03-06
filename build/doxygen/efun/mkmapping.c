public class efun {
   /**
    * The first form returns a mapping with indices from \p arr1 and values from \p arr2... . arr1[0] will index arr2...[0], arr1[1] will index arr2...[1], etc. If the arrays are of unequal size, the mapping will only contain as much elements as are in the smallest array.
    * 
    * The second form converts the given struct \p st into a mapping using the struct member names as index values.
    * 
    * @synopsis{
    * mapping mkmapping(mixed *arr1, mixed *arr2, ...)
    * mapping mkmapping(struct st)
    * }
    * 
    * @usage{
    * ~~~{.c}
    * mkmapping( ({ 1, 2 }), ({ 10, 11 }), ({ 20, 21, 22}))
    * // returns ([ 1:10;20, 2:11;21 ])
    * 
    * struct s { int a; int *b; int c; };
    * mkmapping( (<s> a: 1, b: ({ 2, 3 }), c: 3 )
    * // returns ([ "a":1, "b":({2,3}), "c":3 ])
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * changed (3.3.433) -- added the conversion from structs
    * }
    * 
    * @see @ref driver_syntax_mappings "mapping", efun::mappingp(), efun::m_indices(), efun::m_values(), efun::m_add(), efun::m_delete(), efun::sizeof(), efun::widthof(), efun::unmkmapping(), efun::to_struct()
   **/
   mapping mkmapping(struct st);
}
