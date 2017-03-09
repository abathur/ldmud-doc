public class efun {
   /**
    * Instruct the gamedriver to reset this object not earlier than in \p delay seconds. If a negative value is given as delay, the object will never reset (useful for blueprints). If 0 is given, the object's reset time is not changed.
    * 
    * Result is the former delay to the objects next reset (which can be negative if the reset was overdue).
    * 
    * Note that the actual time the reset occurs depends on when the object will be used after the given time delay.
    * 
    * @synopsis{
    * int set_next_reset(int delay)
    * }
    * 
    * @usage{
    * ~~~{.c}
    * set_next_reset(15*60); // Next reset in 15 Minutes or later
    * set_next_reset(0);     // just returns the time until the next reset.
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * introduced (3.2.6) -- adapted from Morgengrauen.
    * }
    * 
   **/
   int set_next_reset(int delay);
}
