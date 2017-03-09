public class efun {
   /**
    * Returns the angle part of the polar coordinates of the point (x, y) in the range (-pi, pi).
    * 
    * Note the exchange of the coordinates x and y in the parameter list reflecting the sequence in the gradient to angle transformation `atan(y / x)`.
    * 
    * @synopsis{
    * float atan2(int|float y, int|float x)
    * }
    * 
    * @history{
    * changed (3.2.9) -- added integers as arguments
    * }
    * 
    * @see efun::sin(), efun::cos(), efun::tan(), efun::asin(), efun::acos(), efun::atan()
   **/
   float atan2(int|float y, int|float x);
}
