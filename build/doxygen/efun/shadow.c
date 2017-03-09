public class efun {
   /**
    * If \p flag is non-zero the current object will shadow \p ob. If \p flag is 0, either 0 or the object that is shadowing \p ob will be returned.
    * 
    * The calling object must be permitted by the master object to do the shadowing. In most installations, an object that defines the function `query_prevent_shadow(ob)` to return 1 can't be shadowed, and the efun::shadow() function will return 0 instead of ob.
    * 
    * efun::shadow() also fails if: the calling object tries to shadow a function that was defined as "nomask"; the program was compiled with the @ref driver_syntax_pragma "no_shadow"; or the calling object is already shadowing, being shadowed, or has an environment. Also, the target \p ob must not be shadowing another object.
    * 
    * If an object A shadows an object B, every efun::call_other() to B will be redirected to A. If object A has not defined the function, the call will be passed to B. There is only one object that can directly call functions in B with efun::call_other(), and that is A. Not even object B can efun::call_other() itself; the calls will still be redirected to object A. All normal (internal) function calls inside B will, however, remain internal to B.
    * 
    * @synopsis{
    * object shadow(object ob, int flag)
    * }
    * 
    * @usage{
    * With the three objects a.c, b.c and c.c
    * 
    * code like the following:
    * 
    * ~~~{.c}
    * object a, b, c;
    * 
    * a = load_object("a");
    * b = load_object("b");
    * c = load_object("c");
    * b->do_shadow(a);
    * c->do_shadow(a);
    * debug_message("--- a->fun() ---\n");
    * a->fun();
    * debug_message("--- b->fun() ---\n");
    * b->fun();
    * debug_message("--- c->fun() ---\n");
    * c->fun();
    * debug_message("--- b->fun2() ---\n");
    * b->fun2();
    * 
    * ~~~
    * produces this output:
    * 
    * ~~~{.c}
    * --- a->fun() ---
    * /c [c] fun()
    * /b [b] fun()
    * /a [a] fun()
    * --- b->fun() ---
    * /c [c] fun()
    * /b [b] fun()
    * /a [a] fun()
    * --- c->fun() ---
    * /c [c] fun()
    * /b [b] fun()
    * /a [a] fun()
    * --- b->fun2() ---
    * /b [b] fun2()
    * /a [a] fun3()
    * /c [c] fun3()
    * 
    * ~~~
    * code like the following:
    * 
    * ~~~{.c}
    * object a, b, c;
    * 
    * a = load_object("a");
    * b = load_object("b");
    * c = load_object("c");
    * b->do_shadow(a);
    * c->do_shadow(a);
    * a->fun();
    * /// output:
    * // /c [c] fun()
    * // /b [b] fun()
    * // /a [a] fun()
    * //
    * b->fun();
    * // output:
    * // /c [c] fun()
    * // /b [b] fun()
    * // /a [a] fun()
    * //
    * c->fun();
    * // output:
    * // /c [c] fun()
    * // /b [b] fun()
    * // /a [a] fun()
    * //
    * b->fun2();
    * // output:
    * // /b [b] fun2()
    * // /a [a] fun3()
    * // /c [c] fun3()
    * //
    * 
    * ~~~
    * Note that the first call in `b::fun2()` finds `c::fun3()` because, for calls originating from b to a, the driver assumes that all shadows beyond c have already had their chance. The second call, however, was to b itself, which the gamedriver recognized as being shadowed by c.
    * 
    * }
    * 
    * @history{
    * changed (3.2.1@47) -- shadows may now survive the destruction of the shadowee (unless the prepare_destruct in the master object destructs them manually).
    * changed (3.2.8) -- programs may protect themselves from being shadowed with the no_shadow.
    * }
    * 
    * @see efun::query_shadowing(), efun::unshadow(), master::query_allow_shadow()
   **/
   object shadow(object ob, int flag);
}
