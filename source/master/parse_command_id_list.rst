.. master:: string *parse_command_id_list(void)

  Used by :efun:`parse_command`. Return an array of common singular 'thing' ids in the installation's native language.

  .. usage::

    ::

      string *parse_command_id_list() {
          return ({ "one", "thing" });
      }

  .. seealso:: :efun:`parse_command`
