`native` driver mode {#driver_topics_native}
============================================
During the evolution of LPMud there has been a hiatus as the old driver became too restricting for the demands of modern muds: it did a lot of things the mudlib could do better or completely different. Removing these things from the driver weren't a problem, but to keep compatible with the existing mudlibs (namely the well-known 2.4.5 lib), it was possible to undo these changes. First by setting a runtime option, then by compiling the driver either in 'compat' or in 'native' mode.

Starting with 3.2.1, the distinction between compat and native mode is more and more transferred into the mudlib, with the future goal of having a modeless driver.

Starting with 3.2.7, native mode no longer exists as such, only 'plain' (quasi a superset of 'native' and 'compat') and 'compat' mode, and since 3.2.9 the mode selection can be made via commandline option.

The main mode of the driver is determined at compile time by preprocessor symbols to be defined/undefined in config.h:

COMPAT_MODE: when defined, the compat mode specifics are activated
   by default.
   
Additional modifications can be achieved by the specification of commandline arguments (most of them have a default setting entry in config.h as well):

strict-euids: when active, euid usage is enforced.
compat:       when active, the compat mode is used.

Following is the description of the changes (de) activated by these defines. A shorthand notation is used: 'compat' means 'if compat mode is active' and '!compat' means 'if compat mode is not active', etc.

Predefined Preprocessor Symbols
- If compat, the symbols @ref driver_topics_predefined "COMPAT_FLAG" and @ref driver_topics_predefined "__COMPAT_MODE__" are defined for all LPC programs.
- If strict-euids, the symbol @ref driver_topics_predefined "__STRICT_EUIDS__" is defined for all LPC programs.
- For compatibility reasons, the symbol @ref driver_topics_predefined "__EUIDS__" is defined for all LPC programs all the time.

Preloading Of Objects
The driver has the possibility to preload objects before the game is actually opened to the world. This is done by calling master::epilog(), which has to return 0 or an array. If its an array, its elements (as long as they are strings) are given one by one as argument to master::preload() which may now preload the objects (or do anything else).

Initialisation Of Objects
It is task of the mudlib (through the driver hooks) to call the initialisation lfuns in newly created objects. The following table shows the traditional calls:

~~~{.c}
       mode        : init call : reset call
--------------------------------------------
 !compat & !native :  create() :  reset(1)
 !compat &  native :  create() :  reset()
  compat & !native :  reset(0) :  reset(1)
  compat &  native :  reset(0) :  reset(1)

~~~
If INITIALIZATION_BY___INIT was defined, the lfun __INIT() is called first on creation to initialize the objects variables.

Movement Of Objects
The efun::move_object() is implemented in the mudlib through driver hooks and the efun::set_environment(). efun::move_object() itself exists just for convenience and compatibility.

In original native mode, efun::move_object() could applied only to `this_object()` as the object to move, and it called the lfun `exit()` in the old environment if in compat mode. As a side effect, efun::add_action() may not target the lfun `exit()` in compat mode.

In compat mode, objects may be moved using the efun::transfer(). It does make assumptions about the design of the mudlib, though, as it calls the lfuns applied::query_weight(), applied::can_put_and_get(), applied::get(), applied::prevent_insert() and applied::add_weight().

Efuns In General
efun::creator(), efun::transfer()
   These exist only in compat mode (efun::creator() is identical with efun::getuid()).
   
efun::object_name(), efun::function_exists()
   In !compat mode, the returned filenames start with a leading '/', in compat mode they don't.
   
efun::parse_command()
   This command exists in two versions: the old is used with compat, the new with !compat. However, SUPPLY_PARSE_COMMAND must be defined in config.h in both cases (this efun is not very useful at all).
   
efun::process_string()
   If `this_object()` doesn't exist, it defaults to `this_player()` and receives the backbone uid (returned by master::get_bb_uid()) as euid. If strict-euids, this uid must not be 0.
   
Userids and Effective Userids
This is probably the most important difference between the modes.

LPMud always had userids (uids) attributing the objects, though they were called 'creator names' in compat mode. Internally, the compat mode uses the 'creator names' as (e)uid.

With the introduction of native/plain mode, additionally 'effective userids' (euids) were introduced to improve security handling (which was only a partial success). The hardcoded handling of euids and uids was quite complex and too mudlib-insensitive, so most of it got moved from the driver into the mudlib with 3.2.1.

In strict-euids mode, only objects with a non-zero euid may load or create new objects.

## In Detail #

Userids of the Master
   The master's (e)uid is determined by a call to master::get_master_uid().
   
   In strict-euids mode, the result has to be a string, otherwise the driver won't start up at all. If the result is valid it is set as the master's uid and euid.
   
   In !strict-euids mode, the result may be any value: 0 or a string are treated as the uid to set, a non-zero integer leads to the use of the uid set in the default 'global' wizlist entry, and any other value defaults to 0. The euid is either set to the returned string (if any), or to 0.
   
   The master's uid is determined only on startup this way; at runtime the uids of a reloaded master determined as for every object by a call to the appropriate driver hooks.
   
Userids of New Objects
   To determine the (e)uids for a new object (loaded or inherited, or cloned), the appropriate driver hook is evaluated (@ref driver_hook_load_uids "H_LOAD_UIDS", @ref driver_hook_clone_uids "H_CLONE_UIDS") and the result set as (e)uid. The result may be a single value, in which case the euid is set to 0, or an array `({ uid, euid })`.
   
   In strict-euids mode, both uid and euid must be 0 or a string, any other value causes the load/clone to fail.
   
   In !strict-euids mode, the uid (however returned) may also be a non-zero integer to use the uid of the global wizlist entry as uid. The euid is then set to either 0 or the second entry of the returned array if it's a string.
   
@see @ref driver_hook_overview "hook", efun::move_object()
