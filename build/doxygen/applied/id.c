public class applied {
   /**
    * Let the object identify itself. If str matches an id of the current object then return a non-zero value.
    * 
    * This lfun is applied for efun::present().
    * 
    * @synopsis{
    * int id(string str)
    * }
    * 
    * @usage{
    * Return 1 if the object identifies to "sword" or "sword of fire"; 0 otherwise:
    * 
    * ~~~{.c}
    * int id(string str) {
    *   return "sword" == str || "sword of fire" == str;
    * }
    * 
    * ~~~
    * 
    * }
    * 
    * @see efun::present()
   **/
   int id(string str);
}
