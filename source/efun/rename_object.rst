.. efun:: void rename_object(object ob, string new_name)

  Give the object :arg:`ob` a new object name :arg:`new_name`. Causes a privilege violation. The new name must not contain a # character, except at the end, to avoid confusion with clone numbers.

  :history 3.2@55 introduced:

  .. seealso:: :efun:`creator`, :efun:`object_name`, :efun:`load_name`.
