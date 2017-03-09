public class efun {
   /**
    * Add (or replace) an entry with index \p key in mapping \p map. The modified mapping is also returned as result.
    * 
    * The values for the entry are taken from the `data` arguments. Unassigned entry values default to 0, extraneous `data` arguments are ignored.
    * 
    * The difference between efun::m_add() and @ref driver_syntax_operators "+=" is that the latter creates a duplicate of the target mapping if it has several references.
    * 
    * @synopsis{
    * mapping m_add(mapping map, mixed key, [mixed data...])
    * }
    * 
    * @usage{
    * ~~~{.c}
    * mapping m;
    * 
    * m = ([ "foo" ]);
    * m_add(m, "bar", 1) // ([ "foo", "bar" ])
    * 
    * m = ([ "foo":1 ]);
    * m_add(m, "bar", 1) // ([ "foo":1, "bar":1 ])
    * 
    * m = ([ "foo":1;2 ]);
    * m_add(m, "bar", 1) // ([ "foo":1;2, "bar":1;0 ])
    * m_add(m, "baz", ({ 4, 5 })... ) // ([ "foo":1;2, "bar":1;0, "baz":4;5 ])
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * introduced (3.2.9)
    * }
    * 
    * @see efun::mappingp(), efun::mkmapping(), efun::m_delete(), efun::m_entry(), efun::m_indices(), efun::m_values(), efun::sizeof(), efun::widthof()
   **/
   mapping m_add(mapping map, mixed key, [mixed data...]);
}
