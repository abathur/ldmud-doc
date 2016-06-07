uids {#driver_concepts_uids}
============================
Every object in the mud is attributed with a user-id 'uid': a string which associates the object with a certain 'user' (aka 'wizard' or 'creator', though it is not limited to that). The uid can be 0, which internally is the default-uid.

The uid serves a dual purpose: on the on hand it is used to gather statistics about the various groups of objects (in the famous 'wizlist'), on the other hand the uid can come in handy in the implementation of security systems.

The uid of an object is assigned at its creation through the driver hooks @ref driver_hook_load_uids "H_LOAD_UIDS" for loaded objects, and @ref driver_hook_clone_uids "H_CLONE_UIDS" for cloned objects, and can't be changed afterwards.

The uid of an object can be queried with the efun::getuid() (resp. creator() in compat-mode).

Every object also has a second string attribute, the 'effective userid' or 'euid', which also may be 0. This value was intended to implement a security system based on difference between theoretical and effective permissions. Since the effectiveness of this system is doubtful, the driver enforces such a use only as an option.

As uids, euids are assigned at an objects creation through the two aformentioned driverhooks. They can be queried with efun::geteuid() and changed with efun::seteuid(). Calls to the latter are verified by the master lfun @avalid_seteuid()`.

Additionally objects can impose their uid onto an other objects euid with the efun export_uid().

If the driver is run in 'strict euids' mode, euids are taken more seriously than being just another attribute:

- all objects must have a non-0 uid.
- objects with a 0 euid can't load or clone other objects.
- the backbone uid as returned by @amaster::get_bb_uid()` must
not be 0.

Userids are assigned at the time of the creation of an object by calling the driverhooks H_LOAD_UIDS and H_CLONE_UIDS:

~~~{.c}
mixed <load_uids closure> (string objectname)
mixed <clone_uids closure>(object blueprint, string objectname)

~~~
When an object is newly loaded, the H_LOAD_UIDS hook is called with the object name as argument.

When an object is cloned, the H_CLONE_UIDS hook is called with the blueprint object as first and the clone's designated name as second argument.

In both cases the new object already exists, but has 0 uids.

For the result, the following possibilities exist (<num> is a non-zero number, <no-string> is anything but a string):

~~~{.c}
"<uid>"                    -> uid = "<uid>", euid = "<uid>"
({ "<uid>", "<euid>" })    -> uid = "<uid>", euid = "<euid>"
({ "<uid>", <no-string> }) -> uid = "<uid>", euid = 0

~~~
If strict-euids is not active, the following results are possible, too:

~~~{.c}
<num>                      -> uid = 'default', euid = 0
({ <num>, "<euid>" })      -> uid = 'default', euid = "<euid>"
({ <num>, <no-string> })   -> uid = 'default', euid = 0

~~~
Slightly different rules apply to the (e)uid of the master. The master's (e)uid is determined by a call to @amaster->get_master_uid()`:

~~~{.c}
"<uid"> -> uid = "<uid>", euid = "<uid>"

~~~
In non-strict-euids mode, more results are possible:

~~~{.c}
0       -> uid = 0, euid = 0
<num>   -> uid = 'default', euid = 0

~~~
If your uids are in general based on filenames, it is wise to return a value here which can not be legally generated from any filename. OSB for example uses 'ze/us'.

The masters uid is determined only on startup this way, at runtime the uids of a reloaded master determined as for every object by a call to the appropriate driver hooks.

@see @ref driver_concepts_native "native", master::get_root_uid(), master::valid_seteuid(), @ref driver_concepts_objects "objects", efun::clone_object(), efun::geteuid(), efun::getuid(), efun::seteuid()