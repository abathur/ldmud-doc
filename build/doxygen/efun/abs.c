public class efun {
   /**
    * Returns the absolute value of \p number.
    * 
    * @synopsis{
    * int abs(int number)
    * float abs(float number)
    * }
    * 
    * @usage{
    * ~~~{.c}
    * abs(-18)    - returns 18
    * abs(11)     - returns 11
    * abs(-1.974) - returns 1.974
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * introduced (3.2.6)
    * }
    * 
    * @see efun::sin(), efun::asin(), efun::cos(), efun::acos(), efun::tan(), efun::atan(), efun::log(), efun::exp(), efun::sqrt(), efun::floor(), efun::ceil(), efun::pow(), efun::sgn()
   **/
   float abs(float number);
}
