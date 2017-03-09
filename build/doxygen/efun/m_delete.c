public class efun {
   /**
    * Remove the entry with index 'key' from mapping 'map'. The changed mapping 'map' is also returned as result. If the mapping does not have an entry with index 'key', nothing is changed.
    * 
    * @synopsis{
    * mapping m_delete(mapping map, mixed key)
    * }
    * 
    * @see efun::mappingp(), efun::mkmapping(), efun::m_add(), efun::m_indices(), efun::m_values(), efun::sizeof(), efun::widthof()
   **/
   mapping m_delete(mapping map, mixed key);
}
