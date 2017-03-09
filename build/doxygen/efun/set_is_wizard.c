public class efun {
   /**
    * Change object \p ob wizardhood flag. If \p n is 0, it is cleared, if \p n is, it is set, if \p n is -1 the current status is reported. The return value is always the old value of the flag. Using this function sets a flag in the parser, that affects permissions for dumpallobj etc, which are by default free for every user.
    * 
    * @synopsis{
    * int set_is_wizard(object ob, int n)
    * }
    * 
    * @history{
    * changed (3.2.7) -- made this efun optional.
    * }
    * 
   **/
   int set_is_wizard(object ob, int n);
}
