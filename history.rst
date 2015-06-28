HISTORY
=======

.. take 1, using line-block syntax; probably the prettiest plaintexts, but the HTML markup ends up looking a little sloppy

| LDMud 3.2.6
|   Introduced
| LDMud 3.2.7
|   new basic result OIB_REPLACED.
|   basic result OIB_IS_WIZARD is always 0 if set_is_wizard()
        is not available.
|   basic result OIB_APPROVED is gone.
| LDMud 3.2.8
|   added OIM_DATA_SIZE to the result of OINFO_MEMORY.
| LDMud 3.2.9
|   added the index mechanism, OIM_NUM_INCLUDES,
    OIM_NO_INHERIT, OIM_NO_SHADOW, OIM_NO_CLONE, OIM_SIZE_STRINGS_DATA,
    OIM_SIZE_STRINGS_TOTAL, and OIM_DATA_SIZE_TOTAL to the result
    of OINFO_MEMORY.
| LDMud 3.3.378
|   added the OIM_SHARE_VARIABLES to the result
    of OINFO_MEMORY.
| LDMud 3.3.654
|   added the OIB_NEXT_CLEANUP to the result of OINFO_BASIC.

.. take 2, using simple table syntax and a list; probably one of the prettier between both renderings, but the plaintext loses newlines on the 3.2.7 list cell

--------

=======  =====================================================================
LDMud    Change
=======  =====================================================================
3.2.6    Introduced
3.2.7      - new basic result OIB_REPLACED.

           - basic result OIB_IS_WIZARD is always 0 if set_is_wizard()
             is not available.

           - basic result OIB_APPROVED is gone.
3.2.8    added OIM_DATA_SIZE to the result of OINFO_MEMORY.
3.2.9    added the index mechanism, OIM_NUM_INCLUDES,
         OIM_NO_INHERIT, OIM_NO_SHADOW, OIM_NO_CLONE, OIM_SIZE_STRINGS_DATA,
         OIM_SIZE_STRINGS_TOTAL, and OIM_DATA_SIZE_TOTAL to the result
         of OINFO_MEMORY.
3.3.378  added the OIM_SHARE_VARIABLES to the result of OINFO_MEMORY.
3.3.654  added the OIB_NEXT_CLEANUP to the result of OINFO_BASIC.
=======  =====================================================================


.. take 3, using a field list; looks decent in plaintext except for the spacious list format

--------

:3.2.6: Introduced
:3.2.7:
  * new basic result OIB_REPLACED.
  * basic result OIB_IS_WIZARD is always 0 if set_is_wizard()
    is not available.
  * basic result OIB_APPROVED is gone.
:3.2.8: added OIM_DATA_SIZE to the result of OINFO_MEMORY.
:3.2.9: added the index mechanism, OIM_NUM_INCLUDES,
  OIM_NO_INHERIT, OIM_NO_SHADOW, OIM_NO_CLONE, OIM_SIZE_STRINGS_DATA,
  OIM_SIZE_STRINGS_TOTAL, and OIM_DATA_SIZE_TOTAL to the result
  of OINFO_MEMORY.
:3.3.378: added the OIM_SHARE_VARIABLES to the result
  of OINFO_MEMORY.
:3.3.654: added the OIB_NEXT_CLEANUP to the result of OINFO_BASIC.

.. take 4, using definition lists; if we use the line-block syntax for 3.2.7, it has the wrong indent; if we use list syntax all is well, but the spacious list format looks silly in context.

--------

LDMud 3.2.6
  Introduced
LDMud 3.2.7
  * new basic result OIB_REPLACED.
  * basic result OIB_IS_WIZARD is always 0 if set_is_wizard()
    is not available.
  * basic result OIB_APPROVED is gone.
LDMud 3.2.8
  added OIM_DATA_SIZE to the result of OINFO_MEMORY.
LDMud 3.2.9
  added the index mechanism, OIM_NUM_INCLUDES,
  OIM_NO_INHERIT, OIM_NO_SHADOW, OIM_NO_CLONE, OIM_SIZE_STRINGS_DATA,
  OIM_SIZE_STRINGS_TOTAL, and OIM_DATA_SIZE_TOTAL to the result
  of OINFO_MEMORY.
LDMud 3.3.378
  added the OIM_SHARE_VARIABLES to the result
  of OINFO_MEMORY.
LDMud 3.3.654
  added the OIB_NEXT_CLEANUP to the result of OINFO_BASIC.

.. take 5, using Sphinx idioms for this purpose (with some necessary loss of formatting on the "list" of 3.2.7 changes); this is probably the easiest to parse for semantics, but I don't really like the plaintext

--------

.. versionadded:: 3.2.6
.. versionchanged:: 3.2.7
   new basic result OIB_REPLACED,
   basic result OIB_IS_WIZARD is always 0 if set_is_wizard() is not available,
   basic result OIB_APPROVED is gone.
.. versionchanged:: 3.2.8
   added OIM_DATA_SIZE to the result of OINFO_MEMORY.
.. versionchanged:: 3.2.9
   added the index mechanism, OIM_NUM_INCLUDES,
   OIM_NO_INHERIT, OIM_NO_SHADOW, OIM_NO_CLONE, OIM_SIZE_STRINGS_DATA,
   OIM_SIZE_STRINGS_TOTAL, and OIM_DATA_SIZE_TOTAL to the result
   of OINFO_MEMORY.
.. versionchanged:: 3.3.378
   added the OIM_SHARE_VARIABLES to the result
   of OINFO_MEMORY.
.. versionchanged:: 3.3.654
   added the OIB_NEXT_CLEANUP to the result of OINFO_BASIC.
.. deprecated:: 10.0.0
   just kidding!

.. take 6, two examples of how it *could* work if we wrote an extension that provided our own directive; there's actually a 'changelog' extension here: https://pypi.python.org/pypi/changelog which isn't quite suitable for us but provides some previous art on how to tackle this.

.. 6a

.. history::
  :introduced 3.2.6:
  :changed 3.2.7:
    - new basic result OIB_REPLACED.
    - basic result OIB_IS_WIZARD is always 0 if set_is_wizard()
        is not available.
    - basic result OIB_APPROVED is gone.
  :changed 3.2.8: added OIM_DATA_SIZE to the result of OINFO_MEMORY.
  :changed 3.2.9: added the index mechanism, OIM_NUM_INCLUDES,
    OIM_NO_INHERIT, OIM_NO_SHADOW, OIM_NO_CLONE, OIM_SIZE_STRINGS_DATA,
    OIM_SIZE_STRINGS_TOTAL, and OIM_DATA_SIZE_TOTAL to the result
    of OINFO_MEMORY.
  :changed 3.3.378: added the OIM_SHARE_VARIABLES to the result
    of OINFO_MEMORY.
  :changed 3.3.654: added the OIB_NEXT_CLEANUP to the result of OINFO_BASIC.
  :deprecated 10.0.0: just kidding!

.. 6b

.. history::
  .. introduced:: 3.2.6
  .. changed:: 3.2.7
     - new basic result OIB_REPLACED.
     - basic result OIB_IS_WIZARD is always 0 if set_is_wizard()
       is not available.
     - basic result OIB_APPROVED is gone.
  .. changed:: 3.2.8
     - added OIM_DATA_SIZE to the result of OINFO_MEMORY.
  .. changed:: 3.2.9
     - added the index mechanism, OIM_NUM_INCLUDES,
      OIM_NO_INHERIT, OIM_NO_SHADOW, OIM_NO_CLONE, OIM_SIZE_STRINGS_DATA,
      OIM_SIZE_STRINGS_TOTAL, and OIM_DATA_SIZE_TOTAL to the result
      of OINFO_MEMORY.
  .. changed:: 3.3.378
     - added the OIM_SHARE_VARIABLES to the result
      of OINFO_MEMORY.
  .. changed:: 3.3.654
     - added the OIB_NEXT_CLEANUP to the result of OINFO_BASIC.
  .. deprecated:: 10.0.0

.. produces no plaintext atm.
