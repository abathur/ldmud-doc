.. efun:: void set_environment(object item, object env)

  The item is moved into its new environment env, which may be 0. This efun is to be used in :hook:`H_MOVE_OBJECT`, as it does *nothing* beyond moving the item - no calls to :applied:`init` or such.

  Don't use it in your own objects!

  :history 3.2.1@1 introduced: as ``efun308()``
  :history 3.2.6 changed: renamed to :efun:`set_environment`

  .. seealso:: :applied:`remove`, :applied:`init`, :efun:`move_object`, :efun:`transfer`, :overview:`hook`, :concept:`native`
