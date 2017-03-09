public class master {
   /**
    * This function is called to check if the object \p ob with the user-id \p uid has read permissions for the file given by \p path for the operation named by \p func. It should return 0 if permission is denied, or the normalized path if permission is granted. You can also return 1 to indicate that the \p path can be used unchanged.
    * 
    * The returned pathname must not contain "..", a leading / will be stripped by the interpreter. By default, the returned path must also not contain space characters; if the driver is instructed to allow them, the preprocessor @ref driver_topics_predefined "__FILENAME_SPACES__" is defined.
    * 
    * \p func denotes the efun call or other operation that caused master::valid_read() to be called:
    * 
    * - copy_file
    * - ed_start (check if the file to be edited is readable)
    * - file_size
    * - get_dir
    * - print_file
    * - read_bytes
    * - read_file
    * - restore_object
    * - tail
    * 
    * For efun::restore_object(), the \p path passed is the filename as given in the efun call.
    * 
    * @par tip: This function is called in compat mode as well. If you need to be compatible with the old 2.4.5-mudlib, redirect these calls to the master::valid_read() or master::valid_write() in the user object.
    * 
    * @synopsis{
    * string valid_read(string path, string uid, string func, object ob)
    * }
    * 
    * @see master::valid_write(), master::make_path_absolute()
   **/
   string valid_read(string path, string uid, string func, object ob);
}
