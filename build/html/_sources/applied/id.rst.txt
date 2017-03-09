.. applied:: int id(string str)

  Let the object identify itself. If str matches an id of the current object then return a non-zero value.

  This lfun is applied for :efun:`present`.

  .. todo:: this is now a false document, right?

  .. usage::

    Return 1 if the object identifies to "sword" or "sword of fire"; 0 otherwise::

      int id(string str) {
        return "sword" == str || "sword of fire" == str;
      }

  .. seealso:: :efun:`present`
