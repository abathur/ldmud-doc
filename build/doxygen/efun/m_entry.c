public class efun {
   /**
    * Query the mapping \p map for the entry for \p key and return all its values in one array.
    * 
    * If \p map does not contain \p key, 0 is returned.
    * 
    * @par note: efun::m_add() can be used to add all values for an entry at once.
    * 
    * @synopsis{
    * mixed * m_entry(mapping map, mixed key)
    * }
    * 
    * @usage{
    * ~~~{.c}
    * mapping m = ([ 1:"foo":-1, 2:"bar":-2 ]);
    * 
    * m_entry(m, 0) // 0
    * m_entry(m, 1) // ({ "foo", -1 })
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * introduced (3.2.10)
    * }
    * 
    * @see efun::m_add(), efun::m_contains(), @ref driver_syntax_mappings "mapping", efun::member()
   **/
   mixed * m_entry(mapping map, mixed key);
}
