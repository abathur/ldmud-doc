.. master:: string *parse_command_plural_id_list(void)

  Used by :efun:`parse_command`. Return an array of common plural 'thing' ids in the installation's native language.

  .. usage::

    ::

      string *parse_command_pural_id_list() {
          return: ({ "ones", "things", "them" });
      }

  .. seealso:: :efun:`parse_command`
