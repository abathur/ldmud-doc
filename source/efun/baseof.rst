.. efun:: int baseof(struct b, struct s)

  Test if the type of struct :arg:`b` is a base of struct :arg:`s` (the values of :arg:`b` and :arg:`s` are irrelevant). Results are:

  0
    :arg:`b` is not a base of :arg:`s`, nor is :arg:`b` of equal type as :arg:`s` (though :arg:`s` might be a base of :arg:`b`).

  1
    :arg:`b` is a true base of :arg:`s`

  2
    :arg:`b` and :arg:`s` are the same struct type

  .. todo:: Should/do these values have named macro defs?

  :history 3.3.344 introduced:

  .. seealso:: :efun:`structp`, :type:`struct`
