public class master {
   /**
    * Argument is a file name, which we want to get the owner of. This used for the wizlist, to determine who gets the score for the file being used.
    * 
    * This call is used only to score errors to the right wizard.
    * 
    * @synopsis{
    * string get_wiz_name(string file)
    * }
    * 
    * @see efun::creator(), efun::getuid()
   **/
   string get_wiz_name(string file);
}
