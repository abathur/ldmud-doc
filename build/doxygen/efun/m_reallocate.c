public class efun {
   /**
    * @synopsis{
    * mapping m_reallocate(mapping m, int width)
    * }
    * 
   **/
   mapping m_reallocate(mapping m, int width);
}
Create a new mapping with <width> values per key and fill it
with the values from mapping <m>. If <m> has less than <width>
values per key, the extra values in the result are set to 0.
If <m> has more values per key, the extra values are ignored.

The mapping <m> is not changed.

EXAMPLES
mapping m = ([ "foo":1;2;3, "bar":4;5;6 ])

m_reallocate(m, 1) --> returns ([ "foo":1,       "bar:4 ])
m_reallocate(m, 4) --> returns ([ "foo":1;2;3;0, "bar:4;5;6;0 ])

Introduced in LDMud 3.2.6, suggested by Tubmud.

   See Also: 
      efun::m_allocate(), efun::m_values(), efun::widthof()