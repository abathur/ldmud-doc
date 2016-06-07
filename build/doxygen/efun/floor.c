public class efun {
   /**
    * @synopsis{
    * float floor(float arg)
    * }
    * 
   **/
   float floor(float arg);
}
Round the <arg>ument downwards the nearest whole number, returning
that value. If the <arg>ument value is an integer, the result will
be that value, converted to float.

EXAMPLES
floor(4.5)  - returns  4.0
floor(-4.5) - returns -5.0
floor(5)    - returns  5.0

Introduced in LDMud 3.2.7.
LDMud 3.2.9 added integers as argument values.

   See Also: 
      efun::abs(), efun::ceil()
