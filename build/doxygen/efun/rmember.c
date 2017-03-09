public class efun {
   /**
    * For arrays and strings, returns the index of the last occurance of second arg in the first arg, or -1 if none found. If `start` is given and non-negative, the search starts at that position.
    * 
    * @synopsis{
    * int rmember(mixed *array, mixed elem [, int start])
    * int rmember(string s, int elem [, int start])
    * }
    * 
    * @history{
    * introduced (3.2.10)
    * changed (3.3.556) -- added the start parameter.
    * }
    * 
    * @see efun::member()
   **/
   int rmember(string s, int elem [, int start]);
}
