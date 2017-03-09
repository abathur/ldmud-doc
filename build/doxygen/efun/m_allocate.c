public class efun {
   /**
    * Reserve memory for a mapping.
    * 
    * \p size is the number of entries (i.e. keys) to reserve, \p width is the number of data items per entry. If the optional width is omitted, 1 is used as default.
    * 
    * This is useful only when you are going to construct a mapping whose approximate size you know beforehand, to save overhead on repeated memory allocations. If you don't fill in data for all the allocated elements, any leftovers will be eventually freed some time later (see remark below).
    * 
    * It is also useful if you want the mapping to have a certain width even if you don't provide all the data items for the keys yet.
    * 
    * If the goal is just to create an empty mapping with a certain width, the following notations can be used:
    * 
    * `([ ])`
    * creates an empty mapping of width 1.
    * 
    * `([:width ])`
    * creates an empty mapping the given \p width, where \p width can be any expression yielding an integer result. In fact this notation is compiled as `m_allocate(0, width)`.
    * 
    * @par note: Unused memory in the allocated mapping will be freed during the so-called compacting of the mapping. This is done during the data-cleanup or the garbage collection. The time between data-cleanups is configurable by efun::configure_driver().
    * 
    * @synopsis{
    * mapping m_allocate(int size)
    * mapping m_allocate(int size, int width)
    * }
    * 
    * @usage{
    * To allocate a mapping with 7 values per key, and with space for 3 entries:
    * 
    * ~~~{.c}
    * m_allocate(3, 7)
    * 
    * ~~~
    * If you only need to allocate width, you can just use the literal syntax:
    * 
    * ~~~{.c}
    * ([:2*3 ]) -> same as m_allocate(0, 6)
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * changed (3.2.6) -- Renamed from 'allocate_mapping'.
    * changed (3.2.9) -- The ([:width ]) notation was introduced in LDMud 3.2.9 / 3.3.208.
    * }
    * 
    * @see @ref driver_syntax_mappings "mapping", efun::walk_mapping(), efun::get_type_info(), efun::m_reallocate()
   **/
   mapping m_allocate(int size, int width);
}
