public class efun {
   /**
    * Reserve memory for a mapping.
    * 
    * size is the number of entries (i.e. keys) to reserve, width is
    * the number of data items per entry. If the optional width is
    * omitted, 1 is used as default.
    * 
    * This is useful only when you are going to construct a mapping
    * whose approximate size you know beforehand, to save on malloc
    * overhead. If you don't fill in data for all the allocated
    * elements, any leftovers will be freed after the current
    * function execution ended. It is also useful if you want the
    * mapping to have a certain width even if you don't provide
    * all the data items for the keys yet.
    * 
    * @synopsis{
    * mapping allocate_mapping(int size, int width)
    * }
    * 
    * @history{
    * changed (3.2.6) -- renamed to 'm_allocate()'
    * changed (3.2.9) -- not available if driver is compiled without USE_DEPRECATED.
    * removed (3.3)
    * }
    * 
    * @see @ref driver_LPC_mappings "mappings", efun::walk_mapping(), efun::get_type_info()
   **/
   mapping allocate_mapping(int size, int width);
}
