architectures {#driver_admin_platform}
======================================
Actively supported and tested architectures:

- i386
- x86_64 (work in progress until the release of 3.5.0)

Other architectures can't be tested by us. Many will probably work as well.
Your mileage may vary, but we encourage you to test it. And please tell us
about your experiences.

Platforms which require aligned memory access seem to be not used by the users
of LDMud (e.g. ARM, PowerPC, Sparc). For the sake of code simplicity and/or
speed some code pieces (bytecode, murmur hash functions) don't care about
alignment. On these platforms, the driver will probably not work at all right
now. That can be fixed, but only if needed (there are users) and if the
potential users support us (e.g. testing).
