public class efun {
   /**
    * Groups objects together for which the separator function returns the same value. obarr should be an array of objects, other types are ignored.
    * 
    * If the separator function is defined by name, it is searched and called in the objects from \p obarr. If \p extra arguments are given, they are passed to the function as arguments.
    * 
    * If the separator function is defined as a closure, it will be passed the objects from \p obarr as first argument, with the \p extra arguments (if any) passed following.
    * 
    * If the \p skip argument is given (it is required when \p extra arguments are to be used), and the return value from the separator function call matches this value, the object in question will _not_ be included in the returned array. Default value for \p skip is the number 0.
    * 
    * The returned array is an array of arrays of objects in the form:
    * 
    * ~~~{.c}
    * ({ ({ Same1:1, Same1:2, ... Same1:N }),
    *    ({ Same2:1, Same2:2, ... Same2:N }),
    *       ....
    *    ({ SameM:1, SameM:2, ... SameM:N }) })
    * 
    * ~~~
    * 
    * @synopsis{
    * mixed unique_array(object *obarr, string|closure fun)
    * mixed unique_array(object *obarr, string|closure fun, mixed skip)
    * mixed unique_array(object *obarr, string|closure fun, mixed extra..., mixed skip)
    * }
    * 
    * @usage{
    * The below will return an array of arrays holding all user objects grouped together by their user levels. Wizards have a user level of -1 so they will not appear in the the returned array:
    * 
    * ~~~{.c}
    * mixed *arr;
    * arr=unique_array(users(), "_query_level", -1);
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * changed (3.3) -- added the possibility to call closures, and to pass extra arguments to the separator function.
    * }
    * 
    * @see efun::filter(), efun::map()
   **/
   mixed unique_array(object *obarr, string|closure fun, mixed extra..., mixed skip);
}
