public class efun {
   /**
    * Return the current command giver. This can be an interactive user or another living object (like an npc).
    * 
    * If called from inside the applied::heart_beat() of a non-living object, 0 will be returned.
    * 
    * @synopsis{
    * object this_player(void)
    * }
    * 
    * @usage{
    * ~~~{.c}
    * if (this_player() != this_interactive())
    *    write("Hey, somebody must have forced us to do a
    *    command!\n");
    * 
    * ~~~
    * 
    * }
    * 
    * @see efun::this_object(), efun::previous_object(), efun::interactive(), efun::living()
   **/
   object this_player(void);
}
