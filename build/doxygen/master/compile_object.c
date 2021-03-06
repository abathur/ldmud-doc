public class master {
   /**
    * This function is caled if the interpreter cannot find the file for an object to be loaded. The master object has now the opportunity to return an object that will then serve as if compiled from the given filename.
    * 
    * If 0 is returned, the usual "Could not load descr for" error will occur.
    * 
    * @synopsis{
    * object compile_object(string filename)
    * }
    * 
   **/
   object compile_object(string filename);
}
