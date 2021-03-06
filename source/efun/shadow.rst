.. efun:: object shadow(object ob, int flag)

  If :arg:`flag` is non-zero the current object will shadow :arg:`ob`. If :arg:`flag` is 0, either 0 or the object that is shadowing :arg:`ob` will be returned.

  The calling object must be permitted by the master object to do the shadowing. In most installations, an object that defines the function ``query_prevent_shadow(ob)`` to return 1 can't be shadowed, and the :efun:`shadow` function will return 0 instead of ob.

  :efun:`shadow` also fails if: the calling object tries to shadow a function that was defined as "nomask"; the program was compiled with the :pragma:`no_shadow`; or the calling object is already shadowing, being shadowed, or has an environment. Also, the target :arg:`ob` must not be shadowing another object.

  If an object A shadows an object B, every :efun:`call_other` to B will be redirected to A. If object A has not defined the function, the call will be passed to B. There is only one object that can directly call functions in B with :efun:`call_other`, and that is A. Not even object B can :efun:`call_other` itself; the calls will still be redirected to object A. All normal (internal) function calls inside B will, however, remain internal to B.

  .. usage::

    With the three objects a.c, b.c and c.c

    .. code-block::
      :caption: a.c

      int fun() {
          debug_message(sprintf("%O [a] fun()\n", this_object()));
      }

      void fun3() {
          debug_message(sprintf("%O [a] fun3()\n", this_object()));
      }

    .. code-block::
      :caption: b.c

      int fun() {
          debug_message(sprintf("%O [b] fun()\n", this_object()));
          find_object("a")->fun();
      }
      void fun2() {
          debug_message(sprintf("%O [b] fun2()\n", this_object()));
          find_object("a")->fun3();
          this_object()->fun3();
      }

      void do_shadow(object target) { shadow(target, 1); }

    .. code-block::
      :caption: c.c

      int fun() {
          debug_message(sprintf("%O [c] fun()\n", this_object()));
          find_object("a")->fun();
      }
      void fun3() {
          debug_message(sprintf("%O [c] fun3()\n", this_object()));
      }
      void do_shadow(object target) { shadow(target, 1); }

    .. todo:: below may be easier to understand if the output is just commented into the first block? Compare first 2 blocks with 3rd below.

    code like the following::

      object a, b, c;

      a = load_object("a");
      b = load_object("b");
      c = load_object("c");
      b->do_shadow(a);
      c->do_shadow(a);
      debug_message("--- a->fun() ---\n");
      a->fun();
      debug_message("--- b->fun() ---\n");
      b->fun();
      debug_message("--- c->fun() ---\n");
      c->fun();
      debug_message("--- b->fun2() ---\n");
      b->fun2();

    produces this output::

      --- a->fun() ---
      /c [c] fun()
      /b [b] fun()
      /a [a] fun()
      --- b->fun() ---
      /c [c] fun()
      /b [b] fun()
      /a [a] fun()
      --- c->fun() ---
      /c [c] fun()
      /b [b] fun()
      /a [a] fun()
      --- b->fun2() ---
      /b [b] fun2()
      /a [a] fun3()
      /c [c] fun3()

    code like the following::

      object a, b, c;

      a = load_object("a");
      b = load_object("b");
      c = load_object("c");
      b->do_shadow(a);
      c->do_shadow(a);
      a->fun();
      /// output:
      // /c [c] fun()
      // /b [b] fun()
      // /a [a] fun()
      //
      b->fun();
      // output:
      // /c [c] fun()
      // /b [b] fun()
      // /a [a] fun()
      //
      c->fun();
      // output:
      // /c [c] fun()
      // /b [b] fun()
      // /a [a] fun()
      //
      b->fun2();
      // output:
      // /b [b] fun2()
      // /a [a] fun3()
      // /c [c] fun3()
      //

    Note that the first call in ``b::fun2()`` finds ``c::fun3()`` because, for calls originating from b to a, the driver assumes that all shadows beyond c have already had their chance. The second call, however, was to b itself, which the gamedriver recognized as being shadowed by c.

  :history 3.2.1@47 changed: shadows may now survive the destruction of the shadowee (unless the :master:`prepare_destruct` in the master object destructs them manually).
  :history 3.2.8 changed: programs may protect themselves from being shadowed with the :pragma:`no_shadow`.

  .. seealso:: :efun:`query_shadowing`, :efun:`unshadow`, :master:`query_allow_shadow`
