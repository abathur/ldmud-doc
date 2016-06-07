public class efun {
   /**
    * @synopsis{
    * int m_contains(mixed &data1, ..., &dataN, map, key)
    * }
    * 
   **/
   int m_contains(mixed &data1, ..., &dataN, map, key);
}
If the mapping contains the key map, the corresponding values
are assigned to the data arguments, which must be passed by
reference, and 1 is returned. If key is not in map, 0 is
returned and the data args are left unchanged.
It is possible to use this function for a 0-value mapping, in
which case it has the same effect as efun::member().

Renamed from 'mapping_contains()' in LDMud 3.2.6.

   See Also: 
      efun::m_entry(), @ref driver_LPC_mappings "mappings", efun::member()
