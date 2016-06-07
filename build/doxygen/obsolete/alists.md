alists {#driver_obsolete_alists}
================================
Alists provide a fast and convenient way to access data
associatively.

Alists are implemented as arrays of arrays, the first being
the array holding the keys, the others arrays holding
associated data. An empty alist is an array of empty arrays.

Note that the the dimensions of the arrays are used the other
way than in lisp to allow for faster searching.

Keys have to be of type integer, string or object. Types can
be mixed.

The search functions return an undefined value when another
list is given in place of a presorted key list.

A list with non-numeric keys retrieved by restore_object() has
to be readjusted by using order_alist(), especially after
reboot.

Deleting an entry can safely be done with exclude_array as
long as all associated data lists are treated like the key
array; index finding for such purposes can be done with assoc.

Typical applications: holding administrary information about
wizards, list of visitors in a pub, list of customers having
some sort of credit, information remembered about items etc.

@par note:The main use of alists, storing data associatively, is now
better performed by mappings. Alists are needed for more
extreme situations only.

Alists are available only if the driver is compiled with
alist support. In that case, __ALISTS__ is defined.

## LAST UPDATE
2 MAR 92 21:10:21 GMT #

## AUTHOR
FROM: AMYLAAR@MCSHH.HANSE.DE (JOERN RENNECKE)
SUBJECT: GENERAL DOCUMENTATION ON ALISTS #

@history{
changed (3.3) -- made alists optional
removed (3.5)
}

@see @ref driver_LPC_mappings "mappings", efun::order_alist(), efun::insert_alist(), efun::assoc(), efun::transpose_array()
