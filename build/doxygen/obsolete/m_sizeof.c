public class efun {
   /**
    * Returns the number of indices in mapping 'map'.
    * This function is in fact an alias for sizeof().
    * 
    * @synopsis{
    * int m_sizeof(mapping map)
    * }
    * 
    * @history{
    * changed (3.2.9) -- not available if driver is compiled without USE_DEPRECATED.
    * removed (3.3)
    * }
    * 
    * @see efun::mappingp(), efun::mkmapping(), efun::m_indices(), efun::m_values(), efun::m_delete(), efun::sizeof(), efun::widthof()
   **/
   int m_sizeof(mapping map);
}
