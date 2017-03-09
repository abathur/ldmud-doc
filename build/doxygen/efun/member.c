public class efun {
   /**
    * For arrays and strings, returns the index of the first occurance of second arg in the first arg, or -1 if none found. If `start` is given and non-negative, the search starts at that position. A start position beyond the end of the string or array will cause the efun to return -1.
    * 
    * For mappings it checks, if key is present in mapping m and returns 1 if so, 0 if key is not in m.
    * 
    * @synopsis{
    * int member(mixed *array, mixed elem [, int start])
    * int member(string s, int elem [, int start])
    * int member(mapping m, mixed key)
    * }
    * 
    * @history{
    * changed (3.3.556) -- added the start parameter.
    * }
    * 
    * @see efun::rmember(), @ref driver_syntax_mappings "mapping"
   **/
   int member(mapping m, mixed key);
}
