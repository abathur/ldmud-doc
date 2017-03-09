public class efun {
   /**
    * If the mapping contains the key map, the corresponding values are assigned to the data arguments, which must be passed by reference, and 1 is returned. If key is not in map, 0 is returned and the data args are left unchanged. It is possible to use this function for a 0-value mapping, in which case it has the same effect as efun::member().
    * 
    * @synopsis{
    * int m_contains(mixed &data1, ..., &dataN, map, key)
    * }
    * 
    * @history{
    * changed (3.2.6) -- Renamed from 'mapping_contains()'.
    * }
    * 
    * @see efun::m_entry(), @ref driver_syntax_mappings "mapping", efun::member()
   **/
   int m_contains(mixed &data1, ..., &dataN, map, key);
}
