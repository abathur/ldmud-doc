.. efun:: string variable_exists(string str)
  string variable_exists(string str, int flags)
  string variable_exists(string str, object ob)
  string variable_exists(string str, object ob, int flags)
  :include: <functionlist.h>

  Look up a variable :arg:`str` in the current object, respectively in the object :arg:`ob`.

  The result is the name of the program the variable is defined in. This can be either ``object_name(ob)``, or the name of an inherited program. If !compat mode, the returned name always begins with a '/'.

  :arg:`flags` can be passed as :macro:`NAME_HIDDEN` to return information about static and protected variables in other objects. It is not possible to return information about private variables.

  If the variable cannot be found (because it doesn't exist or it is not visible to the caller), the result is 0.

  :history 3.2.10 introduced:

  .. seealso:: :efun:`function_exists`, :efun:`variable_list`
