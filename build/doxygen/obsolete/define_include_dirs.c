public class master {
   /**
    * Return an array of string patterns giving the absolut paths
    * where to search an include file. The patterns have to have a
    * %s at the place where the name given in the #include statement
    * has to be inserted.
    * 
    * @synopsis{
    * string *define_include_dirs(void)
    * }
    * 
    * @usage{
    * define_include_dirs() { return ({ "sys/%s", "lib/%s" }); }
    * }
    * 
    * @history{
    * removed (3.2.1) -- replaced by H_INCLUDE_DIRS hook.
    * }
    * 
    * @see efun::master()
   **/
   string *define_include_dirs(void);
}
