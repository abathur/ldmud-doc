Welcome to lddoc's documentation!
=================================

.. |t_applied| replace:: :overview:`applied`
.. |t_concepts| replace:: :overview:`concepts`
.. |t_driver| replace:: :overview:`driver`
.. |t_efun| replace:: :overview:`efun`
.. |t_hooks| replace:: :overview:`hook`
.. |t_LPC| replace:: :overview:`LPC`
.. |t_master| replace:: :overview:`master`
.. |t_obsolete| replace:: :overview:`obsolete`
.. |t_other| replace:: :overview:`other`
.. |t_loc| replace:: linked

.. |f_applied| replace:: :file:`applied/`
.. |f_concepts| replace:: :file:`concepts/`
.. |f_driver| replace:: :file:`driver/`
.. |f_efun| replace:: :file:`efun/`
.. |f_hooks| replace:: :file:`hooks/`
.. |f_LPC| replace:: :file:`LPC/`
.. |f_master| replace:: :file:`master/`
.. |f_obsolete| replace:: :file:`obsolete/`
.. |f_other| replace:: :file:`other/`
.. |f_loc| replace:: stored in separate directories described

.. |d_applied| replace:: @subpage driver_applied_applied "applied"
.. |d_concepts| replace:: @subpage driver_concepts_concepts "concepts"
.. |d_driver| replace:: @subpage driver_driver_driver "driver"
.. |d_efun| replace:: @subpage driver_efun_efun "efun"
.. |d_hooks| replace:: @subpage driver_hook_hook "hook"
.. |d_LPC| replace:: @someubpage driver_LPC_lpc "LPC"
.. |d_master| replace:: @subpage driver_master_master "master"
.. |d_obsolete| replace:: @subpage driver_obsolete_obsolete "obsolete"
.. |d_other| replace:: @subpage driver_other_other "other"
.. |d_loc| replace:: linked

.. todo:: there isn't actually an other/other.rst file


.. only:: plain

  The LDMud documentation is organized in chapters that are |f_loc| below.

  :|f_applied|: member functions (lfuns) that the driver applies to objects
  :|f_concepts|: general concepts of LPMUD and LPC
  :|f_driver|: some info about internal operation of the driver
  :|f_efun|: the "system calls" of LPC
  :|f_hooks|: the driver hooks
  :|f_LPC|: about parts of the LPC language
  :|f_master|: lfuns that are applied to the master object only
  :|f_obsolete|: docs for features removed from the driver
  :|f_other|: other useful MUD-related documents

.. only:: html

  The LDMud documentation is organized in chapters that are |t_loc| below.

  :|t_applied|: member functions (lfuns) that the driver applies to objects
  :|t_concepts|: general concepts of LPMUD and LPC
  :|t_driver|: some info about internal operation of the driver
  :|t_efun|: the "system calls" of LPC
  :|t_hooks|: the driver hooks
  :|t_LPC|: about parts of the LPC language
  :|t_master|: lfuns that are applied to the master object only
  :|t_obsolete|: docs for features removed from the driver
  :|t_other|: other useful MUD-related documents

.. only:: doxygen

  The LDMud documentation is organized in chapters that are |d_loc| below.

  :|d_applied|: member functions (lfuns) that the driver applies to objects
  :|d_concepts|: general concepts of LPMUD and LPC
  :|d_driver|: some info about internal operation of the driver
  :|d_efun|: the "system calls" of LPC
  :|d_hooks|: the driver hooks
  :|d_LPC|: about parts of the LPC language
  :|d_master|: lfuns that are applied to the master object only
  :|d_obsolete|: docs for features removed from the driver
  :|d_other|: other useful MUD-related documents

.. todo:: above lists don't include the new "internals" directory, yet.

.. todo:: need to figure out how to integrate the efun.de copy (which I also have yet to convert) ``efun.de/    german translations of the efun/ manpages.``

.. only:: plain or html

  A reference to foo(X) means the function foo as descibed in chapter X, where X is one of:

    :A: for applied
    :C: for concepts
    :D: for driver
    :E: for efun
    :H: for hook
    :LPC: for LPC
    :M: for master
    :O: for obsolete
    :OTHER: for other

    .. todo:: I for internal? SE for simul_efun; I had a note for S as well--perhaps that's SYS? dunno.

    .. todo:: add history, info on doc format?

.. toctree::
  :titlesonly:
  :maxdepth: 1
  :hidden:

  admin/overview.rst
  applied/overview.rst
  efun/overview.rst
  hook/overview.rst
  internals/overview.rst
  master/overview.rst
  obsolete/overview.rst
  syntax/overview.rst
  topics/overview.rst

.. only:: html

  Indices and tables
  ==================

  * :ref:`genindex`
  * :ref:`search`

