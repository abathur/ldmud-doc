.. efun:: int baseof(struct b, struct s)

  Test if the type of struct <b> is a base of struct <s> (the
  values of <b> and <s> are irrelevant). Results are:
    0: <b> is not a base of <s>, nor is <b> of equal type as <s>
         (though <s> might be a base of <b>).
    1: <b> is a true base of <s>
    2: <b> and <s> are the same struct type

.. history
  :history 3.3.344 introduced:

  .. seealso:: :efun:`structp`, :lang:`structs`
