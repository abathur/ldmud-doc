public class efun {
   /**
    * @synopsis{
    * int random(int n)
    * }
    * 
   **/
   int random(int n);
}
Returns a number in the random range [0 .. n-1].

The random number generator is proven to deliver an equal distribution
of numbers over a big range, with no repetition of number sequences
for a long time. The downside of these (desirable) qualities is that
when generating numbers in a small range over short time, certain
numbers will appear far more often than others.

The only solution is the implementation of a special simul_efun which
takes special steps to implement an equal distribution over small
ranges and short times.
