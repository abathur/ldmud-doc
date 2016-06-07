public class efun {
   /**
    * @synopsis{
    * mapping m_add(mapping map, mixed key, [mixed data...])
    * }
    * 
   **/
   mapping m_add(mapping map, mixed key, [mixed data...]);
}
Add (or replace) an entry with index <key> in mapping <map>.
The modified mapping is also returned as result.

The values for the entry are taken from the <data> arguments.
Unassigned entry values default to 0, extraneous <data> arguments
are ignored.

The difference between m_add() and the operator += is that the
latter creates a duplicate of the target mapping if it has
several references (see EXAMPLES).

EXAMPLES
mapping m;

m = ([ "foo" ]);
m_add(m, "bar", 1) --> ([ "foo", "bar" ])

m = ([ "foo":1 ]);
m_add(m, "bar", 1) --> ([ "foo":1, "bar":1 ])

m = ([ "foo":1;2 ]);
m_add(m, "bar", 1) --> ([ "foo":1;2, "bar":1;0 ])
m_add(m, "baz", ({ 4, 5 })... )

   --> ([ "foo":1;2, "bar":1;0, "baz":4;5 ])

Introduced in LDMud 3.2.9.

   See Also: 
      efun::mappingp(), efun::mkmapping(), efun::m_delete(), efun::m_entry(), efun::m_indices(), efun::m_values(), efun::sizeof(), efun::widthof()
