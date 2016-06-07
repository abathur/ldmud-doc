public class efun {
   /**
    * If the mapping contains the key map, the corresponding values
    * are assigned to the data arguments, which massed be passed by
    * reference, and 1 is returned. If key is not in map, 0 is
    * returned and the data args are left unchanged.
    * It is possible to use this function for a 0-value mapping, in
    * which case it has the same effect as efun::member().
    * 
    * @synopsis{
    * int mapping_contains(mixed &data1, ..., &dataN, map, key)
    * }
    * 
    * @history{
    * changed (3.2.6) -- renamed to 'm_contains()'.
    * changed (3.2.9) -- not available if driver is compiled without USE_DEPRECATED.
    * removed (3.3)
    * }
    * 
    * @see @ref driver_LPC_mappings "mappings", efun::member()
   **/
   int mapping_contains(mixed &data1, ..., &dataN, map, key);
}
