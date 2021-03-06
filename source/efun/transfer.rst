.. efun:: int transfer(object item, object dest)
  :deprecated:

  This efun is for backward compatibility only. It is only available in compat mode.

  Move the object :arg:`item` to the object :arg:`dest`. All kinds of tests are done, and a number is returned specifying the result:

  0: Success.
  1: Too heavy for destination.
  2: Can't be dropped.
  3: Can't take it out of it's container.
  4: The object can't be inserted into bags etc.
  5: The destination doesn't allow insertions of objects.
  6: The object can't be picked up.

  If an object is transfered to a newly created object, make sure that the new object first is transfered to its destination.

  The efun calls :applied:`add_weight`, :applied:`drop`, :applied:`get`, :applied:`prevent_insert`, :applied:`add_weight`, and :applied:`can_put_and_get` where needed.

  .. subtopic:: replacement simul_efun

    This efun can easily be replaced with a simul_efun::

      /*--------------------------------------------------------*/
      int transfer(object item, object dest)
      {
          int weight;
          object from;

          efun::set_this_object(previous_object());

          weight = item->query_weight();
          if (!item)
              return 3;

          from = environment(item);
          if (from)
          {
              /*
               * If the original place of the object is a living object,
               * then we must call drop() to check that the object can be
               * dropped.
               */
              if (living(from))
              {
                  if (item->drop() || !item)
                      return 2;
              }
              /*
               * If 'from' is not a room and not a player, check that we may
               * remove things out of it.
               */
              else if (environment(from))
              {
                  if (!from->can_put_and_get() || !from)
                      return 3;
              }
          }

          /*
           * If the destination is not a room, and not a player,
           * Then we must test 'prevent_insert', and 'can_put_and_get'.
           */
          if (environment(dest) && !living(dest))
          {
              if (item->prevent_insert())
                  return 4;
              if (!dest->can_put_and_get() || !dest)
                  return 5;
          }

          if (living(dest))
          {
              if (!item->get() || !item)
                  return 6;
          }

          /*
           * If it is not a room, correct the total weight in the
           * destination.
           */
          if (environment(dest) && weight)
          {
              if (!dest->add_weight(weight) || !dest)
                  return 1;
          }

          /*
           * If it is not a room, correct the weight in the 'from' object.
           */
          if (from && environment(from) && weight)
          {
              from->add_weight(-weight);
          }

          move_object(item, dest);

          return 0;
      }
      /*--------------------------------------------------------*/

  :history 3.3 deprecated: available only when compiled with USE_DEPRECATED.

  .. seealso:: :efun:`move_object`, :applied:`drop`, :applied:`get`, :applied:`prevent_insert`, :applied:`can_put_and_get`, :applied:`add_weight`
