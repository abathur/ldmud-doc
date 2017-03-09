public class efun {
   /**
    * Round the \p number downwards the nearest whole number, returning that value. If the \p number value is an integer, the result will be that value, converted to float.
    * 
    * @synopsis{
    * float floor(float number)
    * }
    * 
    * @usage{
    * ~~~{.c}
    * floor(4.5)  - returns  4.0
    * floor(-4.5) - returns -5.0
    * floor(5)    - returns  5.0
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * introduced (3.2.7)
    * changed (3.2.9) -- adds integers as argument values.
    * }
    * 
    * @see efun::abs(), efun::ceil()
   **/
   float floor(float number);
}
