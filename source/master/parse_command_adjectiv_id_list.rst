.. master:: string *parse_command_adjectiv_id_list(void)

  Used by :efun:`parse_command`. Return an array of common adjectives in the installation's native language.

  .. usage::

    ::

      string * parse_command_adjectiv_id_list() {
          return ({ "iffish" });
      }

  .. seealso:: :efun:`parse_command`
