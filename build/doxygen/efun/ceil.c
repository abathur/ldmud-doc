public class efun {
   /**
    * Round the \p number upwards the nearest whole number, returning that value. If the \p number value is an integer, the result will be that value, converted to float.
    * 
    * @synopsis{
    * float ceil(int|float number)
    * }
    * 
    * @usage{
    * ~~~{.c}
    * ceil(4.5)  - returns 5.0
    * ceil(-4.5) - returns -4.0
    * ceil(4)    - returns 4.0
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * introduced (3.2.7)
    * changed (3.2.9) -- allow integers as argument values.
    * }
    * 
    * @see efun::abs(), efun::floor()
   **/
   float ceil(int|float number);
}
