.. master:: mixed include_file (string file, string compiled_file, int sys_include)

  Generate the pathname of an included file.

  Arguments:

    ``previous_object()``
      The object causing the compile.

    file
      The name given in the #include directive.

    compiled_file
      The object file which is just compiled. (compat: name given without leading "/")

    sys_include
      TRUE for #include <> directives.

  Result:

    ``0``
      use the normal include filename generation (""-includes are used as they are, <>-includes are handled according to :hook:`H_INCLUDE_DIRS`).

    ``<path>``
      the full absolute pathname of the file to include, without parentdir parts ("/../"). Leading slashes ("/") may be omitted.

    else
      The include directive is not legal.

  If the function does not generate a valid pathname, the driver will next try to resolve the include using the :hook:`H_INCLUDE_DIRS` hook.

  :history 3.2.8 introduced:

  .. seealso:: :overview:`hook`, :master:`inherit_file`, :hook:`include_dirs`
