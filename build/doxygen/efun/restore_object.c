public class efun {
   /**
    * Restore values of variables for current object from the file \p name, or directly from the string \p str.
    * 
    * To restore directly from a string \p str, the string must begin with the typical line `#x:y` as it is created by efun::save_object().
    * 
    * When restoring from a file, the name may end in `.c` which is stripped off by the parser. The master object will probably append a `.o` to the \p name. The validity of the filename is checked with a call to `check_valid_path`.
    * 
    * Return 1 on success, 0 if there was nothing to restore.
    * 
    * Variables with >>:modifer:`nosave`<< will not be restored:
    * 
    * ~~~{.c}
    * ``nosave int xxx;``
    * 
    * ~~~
    * Lfun, variable and simul_efun closures are restored only if they can be found (this excludes closures of private lfuns as well) - if not, they are restored as value `0`.
    * 
    * If inheritance is used, then it might be possible that a variable will exist with the same name in more than one place, and thus appear in the  save file multiple times. When restoring, the variables are restored in the order they are found in the inheritance tree. A good practice is to have verbose and unique name on non-static variables, which also will make it more easy to read or patch the save file manually.
    * 
    * @synopsis{
    * int restore_object(string name)
    * int restore_object(string str)
    * }
    * 
    * @history{
    * changed (3.2.8) -- added restoring directly from a string.
    * changed (3.2.9) -- added restoring of non-lambda closures, symbols, and quoted arrays, using a new savefile format version 1.
    * changed (3.5.0) -- added the possibility to restore version 2 with its higher float precision.
    * }
    * 
    * @see efun::save_object(), efun::restore_value(), master::valid_read()
   **/
   int restore_object(string str);
}
