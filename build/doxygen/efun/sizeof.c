public class efun {
   /**
    * Returns the number of elements of an array or struct, the number of characters in a string, or the number of keys in a mapping.
    * 
    * As a special case, the number 0 can be passed, and the function will return 0.
    * 
    * If there were any objects destroyed in the game since the mapping was last checked for destructed keys, the mapping needs to be checked for destructed objects in keys first. In that case, the runtime increases linear with the number of keys in the mapping (`O(n)`). Otherwise the runtime is independent of the mappings size (`O(1)`).
    * 
    * @synopsis{
    * int sizeof(mixed * val)
    * int sizeof(string  val)
    * int sizeof(mapping val)
    * int sizeof(struct xxx val)
    * }
    * 
    * @history{
    * changed (3.2.9) -- added strings to the possible parameters.
    * changed (3.3) -- added support for structs.
    * }
    * 
    * @see efun::strlen(), efun::allocate(), efun::pointerp(), efun::mappingp(), efun::m_allocate(), efun::widthof()
   **/
   int sizeof(struct xxx val);
}
