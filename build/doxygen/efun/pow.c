public class efun {
   /**
    * The function returns the value of \p base raised to the power of \p exp.
    * 
    * @synopsis{
    * float pow(int|float base, int|float exp)
    * }
    * 
    * @usage{
    * ~~~{.c}
    * pow(-2, 3)      // returns -8.0
    * pow(8, 1.0/3.0) // returns 2.0
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * introduced (3.2.7)
    * changed (3.2.9) -- added integers as arguments.
    * }
    * 
    * @see efun::exp(), efun::log()
   **/
   float pow(int|float base, int|float exp);
}
