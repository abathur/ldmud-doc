.. efun:: int program_time()
  int program_time(object ob)

  Returns the creation (compilation) time of the object's program. Default is ``this_object()``, if no arg is given.

  .. note:: If the objects program is swapped out, this efun swaps it back in.

  .. seealso:: :efun:`object_time`, :efun:`program_name`
