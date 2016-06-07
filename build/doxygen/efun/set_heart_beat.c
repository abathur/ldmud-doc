public class efun {
   /**
    * @synopsis{
    * int set_heart_beat(int flag)
    * }
    * 
   **/
   int set_heart_beat(int flag);
}
Enable or disable heart beat. The driver will apply the lfun
heart_beat() to the current object every __HEARTBEAT_INTERVAL__
seconds, if it is enabled. A shadow over the heart_beat() lfun
will be ignored.

If the heart beat is not needed for the moment, then do disable it.
This will reduce system overhead.

Return true for success, and false for failure.

Disabling an already disabled heart beat (and vice versa
enabling and enabled heart beat) counts as failure.

Note that heart_beat()s are called only if there are interactive
players in the game.

   See Also: 
      applied::heart_beat(), efun::call_out()
