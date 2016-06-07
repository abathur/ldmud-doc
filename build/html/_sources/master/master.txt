.. directory:: master

  .. todo:: this doc is referenced from 4 docs in this folder (epilog, flag, preload, reactivate_destructed_master), which makes me wonder if they _all_ should, if we should have an automagic backref of some sort, if none should, etc.

  This directory contains descriptions for the functions that
  LDMud expects to find in the master object (similar to lfuns,
  but for the master object only). The name of the master object
  is hardcoded in the parser, but can also be specified on
  the commandline (usually to "secure/master").

  The master is the gateway between the interpreter and the
  mudlib to perform actions with mudlib specific effects. Calls
  to the master by the interpreter have an automatic catch() in
  effect. Functions to be called by the driver can be public
  or static, but not private.

  Note that the master is loaded first of all objects. Thus you
  shouldn't inherit an other object, nor is the compiler able to
  search include files (read: they must be specified with full
  path).

  .. note:: you can inherit, but the file will be loaded then before the master, which isn't good for most files.

  .. subtopic:: system startup

    The Initialisation functions are called after (re)loading the
    master to establish the most basic operation parameters.

    The initialisation of the mud on startup follows this schedule:

    - The interpreter evaluates the commandline options and
      initializes itself.
    - The master is loaded, but since the driverhooks are not set yet,
      no standard initialisation lfun is called.
    - get_master_uid() is called. If the result is valid, it becomes the
      masters uid.
    - inaugurate_master() is called.
    - flag() is called for each given '-f' commandline option.
    - get_simul_efun() is called.
    - the WIZLIST is read in.
    - epilog() is called. If it returns an array of strings,
      they are given one at a time as argument to preload().
      Traditionally, these strings are the filenames of the objects to
      pre-load, which preload() then does.
    - The interpreter sets up the IP communication and enters
      the backend loop.

  .. subtopic:: reloaded master object

    If the master is reloaded during system operation, these
    actions are taken:

    - The master is loaded, and its initialisation lfun is
      called according to the settings of the driverhooks (if set).
    - Any auto-include string and all driverhooks are cleared.
    - get_master_uid() is called. If the result is valid, it becomes the
      masters uid and euid.
    - inaugurate_master() is called.

  .. subtopic:: destructed master object

    If the master was destructed, but couldn't be reloaded, the old
    master object could be reactivated. In that case:

    - reactivate_destructed_master() is called.
    - inaugurate_master() is called.

  .. subtopic:: master function reference

    The following is a short reference to all expected master functions, categorized for easier reading. There is also an alphabetical :ref:`index <master-topics>` of all master-object topics and functions at the end of the document.

    .. todo:: the below was tagged "Security hint" in our docs; it might be nice to either have a separate directive for security issues, or be able to supply a type/category option to the other admonitions (i.e., use directives like note, warning, hint, tip, but be able to supply a :category: security, etc.)

    .. admonition:: Security hint

      most of these functions are not useful to be
      called directly from other objects and can be made private or
      static. Unlike create(), these functions that are applied to
      the master object are found by the interpreter even if not
      publicly accessible.

    .. todo:: this is another case where being able to pull part of this from the target would be nice; I wonder if a ``:role:`ref``` can be magicked into an expansion based on the synopses declared in the target? If nothing else, can use the link feature (``:master:`void inaugurate master() <inaugurate_master>``` or whatnot.)

    .. enumerate:: Initialisation

      :master:`void inaugurate_master () <inaugurate_master>`
        Perform mudlib specific setup of the master.

      string get_master_uid ()
        Return the string to be used as uid (and -euid) of a
        (re)loaded master.

      void flag (string arg)
        Evaluate an argument given as option '-f' to the driver.

      string *epilog (int eflag)
        Perform final actions before opening the system to users.

      void preload (string file)
        Preload a given object.

      void external_master_reload ()
        Called after a reload of the master on external request.

      void reactivate_destructed_master (int removed)
        Reactivate a formerly destructed master.

      ``string|string * get_simul_efun ()``
      :master:`string|string * get_simul_efun () <get_simul_efun>`
        Load the simul_efun object and return one or more paths of it.

    .. enumerate:: Handling of user connections

      object connect ()
        Handle the request for a new connection.

      void disconnect (object obj)
        Handle the loss of an IP connection.

      void remove_player (object user)
        Remove a user object from the system.

      void stale_erq (closure callback)
        Notify the loss of the erq demon.

    .. enumerate:: Runtime support

      object compile_object (string filename)
        Compile a virtual object.

      mixed include_file (string file, string compiled_file, int sys_include)
        Return the full pathname for an included file. // 3.2.8 and later

      mixed inherit_file (string file, string compiled_file)
        Return the full pathname for an inherited object. // 3.2.8 and later

      string get_wiz_name (string file)
        Return the author of a file.

      string printf_obj_name (object obj)  // 3.2.6 and later
      string object_name (object obj)      // 3.2.1 .. 3.2.5
        Return a printable name for an object.

      mixed prepare_destruct (object obj)
        Prepare the destruction of the given object.

      void quota_demon (void)
        Handle quotas in times of memory shortage.

      void receive_imp (string host, string msg, int port)
        Handle a received IMP message.

      void slow_shut_down (int minutes)
        Schedule a shutdown for the near future.

      void notify_shutdown ()
        Notify the master about an immediate shutdown.

    .. enumerate:: Error handling

      void dangling_lfun_closure ()
        Handle a dangling lfun-closure.

      void log_error (string file, string err, int warn)
        Announce a compiler-time error or warning.

      mixed heart_beat_error (object culprit, string err,string prg, string curobj, int line)
        Announce an error in the heart_beat() function.

      void runtime_error (string err, string prg, string curobj, int line)
        Announce a runtime error.

      void runtime_warning (string msg, string curobj, string prg, int line)
        Announce a runtime warning.

    .. enumerate:: Security and Permissions

      int privilege_violation (string op, mixed who, mixed arg3, mixed arg4)
        Validate the execution of a privileged operation.

      int query_allow_shadow (object victim)
        Validate a shadowing.

      int valid_exec (string name)
        Validate the rebinding of an IP connection by usage of efun
        exec().

      int valid_query_snoop (object obj)
        Validate if the snoopers of an object may be revealed by
        usage of the efun query_snoop().

      int valid_snoop (object snoopee, object snooper)
        Validate the start/stop of a snoop.

    .. enumerate:: Userids and depending security

      string get_bb_uid()
        Return the string to be used as root-uid.

      int valid_seteuid (object obj, string neweuid)
        Validate the change of an objects euid by efun seteuid().

      int|string valid_read (string path, string euid, string fun, object caller)
      int|string valid_write (string path, string euid, string fun, object caller)
        Validate a reading/writing file operation.

    .. enumerate:: ed() support

      string make_path_absolute (string str)
        Absolutize a relative filename given to the editor.

      int save_ed_setup (object who, int code)
        Save individual settings of ed for a wizard.

      int retrieve_ed_setup (object who)
        Retrieve individual settings of ed for a wizard.

      string get_ed_buffer_save_file_name (string file)
        Return a filename for the ed buffer to be saved into.

    .. enumerate:: parse_command() support (!compat, SUPPLY_PARSE_COMMAND defined)

      .. todo:: make the last half of the title some sort of addendum/annotation

      string *parse_command_id_list ()
        Return generic singular ids.

      string *parse_command_plural_id_list ()
        Return generic plural ids.

      string *parse_command_adjectiv_id_list ()
        Return generic adjective ids.

      string *parse_command_prepos_list ()
        Return common prepositions.

      string parse_command_all_word()
        Return the one(!) 'all' word.

  .. subtopic:: All Topics

    .. toctree::
      :maxdepth: 1
      :glob:
      :name: master-topics

      *

  .. seealso:: :directory:`applied`, :directory:`concepts`, :directory:`driver`, :directory:`efun`, :directory:`hook`, :directory:`internals`, :directory:`LPC`, :directory:`obsolete`
