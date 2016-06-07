public class efun {
   /**
    * @synopsis{
    * mixed * unmkmapping(mapping map)
    * }
    * 
   **/
   mixed * unmkmapping(mapping map);
}
DESCRIPTION
Take mapping <map> and return an array of arrays with the keys
and values from the mapping.

The return array has the form ({ keys[], data0[], data1[], ... }),
with keys[] being the array of all keys, data0[] the array of
all values in the first column, data1[] the array of all values
in the second column, etc. In particular, the data for key[x]
is stored in data0[x], data1[x], etc.

unmkmapping() is inverse to mkmapping(), so that

   apply(#'mkmapping, unmkmapping(m)) == m

holds.

EXAMPLES
mapping m = ([ 1:10;20, 2:11;21 ]);
unmkmapping(m)

   --> returns ({ ({1, 2}), ({ 10, 11 }), ({ 20, 21 }) })

Introduced in LDMud 3.2.6.

      See Also: 
         @ref driver_LPC_mappings "mappings", efun::mappingp(), efun::m_indices(), efun::m_values(),

   efun::m_delete(), efun::sizeof(), efun::widthof().
