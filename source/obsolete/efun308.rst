.. efun:: void efun308(object item, object env)
  :removed:

  The item is moved into its new environment env, which may be 0.
  This efun is to be used in the move_object() hook, as it does
  nothing else than moving the item - no calls to init() or such.

  Don't use it in your own objects!

  :history 3.2.1@1 introduced:
  :history 3.2.6 changed: renamed to :efun:`set_environment`
  :history 3.2.9 changed: not available if driver is compiled without USE_DEPRECATED.
  :history 3.3 removed:

  .. seealso:: :applied:`remove`, :applied:`init`, :efun:`move_object`, :efun:`transfer`, :concept:`hooks`, :concept:`native`
