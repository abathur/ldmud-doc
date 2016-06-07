public class efun {
   /**
    * The arg will be automatically included into every compiled LPC
    * object. This is useful to enforce global definitions, e.g.
    * >>``<<#pragma rtt_checks'' or >>``<<#pragma strict_types''.  The
    * calling object needs to be privileged by the master object.
    * 
    * Note that the auto-include-string is cleared when the master
    * object is reloaded.
    * 
    * @synopsis{
    * void set_auto_include_string(string arg)
    * }
    * 
   **/
   void set_auto_include_string(string arg);
}