public class master {
   /**
    * This function is called when a runtime error occurs while
    * executing the heart_beat() function of the object culprit. prg
    * is program where the actual error happened, in object curobj
    * at the given line.
    * 
    * At time of call, the heart_beat has been turned off.
    * Return anything != 0 to restart the heart_beat in culprit.
    * 
    * If culprit is a user, it should at least get the message "You
    * have no heartbeat". A more advanced handling would destruct
    * the offending object curobj and and allow the heartbeat to
    * restart.
    * 
    * If the error is caught on a higher level, <caught> is non-zero;
    * otherwise it is 0.
    * 
    * Note that prg denotes the program actually executed (which
    * might be an inherited one) whereas curobj is just the
    * offending object.
    * 
    * @synopsis{
    * mixed heart_beat_error(object culprit, string err, string prg, string curobj, int line, int caught)
    * }
    * 
    * @history{
    * changed (3.2.12/3.3.705) -- added the <caught> argument.
    * }
    * 
    * @see efun::set_heart_beat(), applied::heart_beat(), master::runtime_error()
   **/
   mixed heart_beat_error(object culprit, string err, string prg, string curobj, int line, int caught);
}
