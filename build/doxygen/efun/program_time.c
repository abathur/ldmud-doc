public class efun {
   /**
    * Returns the creation (compilation) time of the object's
    * program. Default is this_object(), if no arg is given.
    * 
    * @par note:If the objects program is swapped out, this efun
    * swaps it back in.
    * 
    * @synopsis{
    * int program_time()
    * int program_time(object ob)
    * }
    * 
    * @see efun::object_time(), efun::program_name()
   **/
   int program_time(object ob);
}
