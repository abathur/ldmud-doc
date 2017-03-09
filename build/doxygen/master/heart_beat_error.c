public class master {
   /**
    * This function is called when a runtime error occurs while executing the applied::heart_beat() function of the object \p culprit. \p prg is program where the actual error happened, in object \p curobj at the given \p line.
    * 
    * At time of call, the heart_beat has been turned off. Return anything != 0 to restart the heart_beat in \p culprit.
    * 
    * If \p culprit is a user, it should at least get the message "You have no heartbeat". A more advanced handling would destruct the offending object \p curobj and and allow the heartbeat to restart.
    * 
    * If the error is caught on a higher level, \p caught is non-zero; otherwise it is 0.
    * 
    * @par note: \p prg denotes the program actually executed (which might be an inherited one) whereas \p curobj is just the offending object.
    * 
    * @synopsis{
    * mixed heart_beat_error(object culprit, string err, string prg, string curobj, int line, int caught)
    * }
    * 
    * @history{
    * changed (3.2.12/3.3.705) -- added the caught argument.
    * }
    * 
    * @see efun::set_heart_beat(), applied::heart_beat(), master::runtime_error()
   **/
   mixed heart_beat_error(object culprit, string err, string prg, string curobj, int line, int caught);
}
