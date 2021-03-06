.. efun:: mixed * struct_info(struct st, int what)
  :include: <struct_info.h>
    <lpctypes.h>

  Return an array of information about the structure of struct :arg:`st`. If :arg:`st` has a base struct, :arg:`what` determines how the information is returned:

  :arg:`what` == :macro:`SINFO_FLAT`:
    All members of :arg:`st`, including those inherited from the base struct, are returned on the top level of the result. The base struct is signified by just its name.

  :arg:`what` == :macro:`SINFO_NESTED`:
    Only the members defined in :arg:`st` itself are returned on the top level of the result. The information for the base struct is an array by itself, as it would be returned by a call to :efun:`struct_info` for a base struct instance.

  The elements in the resulting array are:

    string [:macro:`SI_NAME`]:        the name of the struct
    string [:macro:`SI_PROG_NAME`]:   the name of program defining the struct
    string [:macro:`SI_PROG_ID`]:     the id of the program defining the struct
    mixed  [:macro:`SI_BASE`]:        0, or the base struct information
    mixed *[:macro:`SI_MEMBER`+0]:    the first member information
    mixed *[:macro:`SI_MEMBER`+n]:    the last member information

  The member information entries are arrays themselves with these elements:

    string [:macro:`SIM_NAME`]:  name of the member
    int    [:macro:`SIM_TYPE`]:  the type of the member (compile-time value)
    string [:macro:`SIM_EXTRA`]: 0, or if the member is a struct, the struct name

  :history 3.3.344 introduced:
  :history 3.3.417 changed: introduced :macro:`SI_PROG_NAME` and :macro:`SI_PROG_ID` in exchange for :macro:`SI_UNIQUE_NAME`.

  .. seealso:: :type:`struct`
