simul_efun {#driver_concepts_simul_efun}
========================================
The simul_efun object is automagically sort-of inherited by every object. That functions that are defined in it can be accessed just like efuns or inherited functions by every object (except the master object). To get access to efuns that are overloaded by the simul_efun object, you can use @aefun::function()` to bypass the simul_efun (unless the simul_efun object has defined the function as "nomask").

@see master::get_simul_efun()
