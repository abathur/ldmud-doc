.. applied:: int id(string str)

  Let the object identify itself. If str matches an id of the
  current object then return a non-zero value.

  This lfun is applied for the efun present().

  .. usage::

    int id(string str) {
       return "sword" == str || "sword of fire" == str;
    }

  .. seealso:: :efun:`present`
