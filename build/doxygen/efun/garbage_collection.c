public class efun {
   /**
    * Tell the parser to initiate a garbage collection after the current execution ended. Depending on the type of memory allocator used, this GC is more less thorough.
    * 
    * If the 'smalloc' memory allocator is used, the GC produces output to a log file. The default name of the log file is specified at program start, but can be modified at runtime:
    * 
    * - With the \p filename argument a log file for the GC output different from the default log file can be specified.
    * - If \p flag is not given or 0, the output from the next and only the next GC will go into the log file. If the file already exists, the new output will be appended.
    * - If \p flag is 1, the \p filename will be used as the new default log file for all following GCs. If the file already exists, it will be overwritten from the start.
    * 
    * If a different memory allocator is used, the GC does not produce output and the \p filename and \p flag arguments are ignored.
    * 
    * Calling this efun causes a privilege_violation.
    * 
    * @synopsis{
    * void garbage_collection()
    * void garbage_collection(string filename)
    * void garbage_collection(string filename, int flag)
    * }
    * 
    * @usage{
    * The following examples demonstrate how the flag affects logging behavior:
    * 
    * ~~~{.c}
    * garbage_collection()
    * // GC occurs -> logs into default file
    * 
    * garbage_collection("/GCLOG")
    * // GC occurs -> logs into "/GCLOG"
    * 
    * garbage_collection("/GCLOG", 1)
    * // GC occurs -> logs into "/GCLOG", sets default log to "/GCLOG"
    * 
    * garbage_collection("/GCLOG")
    * garbage_collection("/GCLOG2")
    * // GC occurs -> logs into "/GCLOG"
    * 
    * garbage_collection("/GCLOG", 1)
    * garbage_collection("/GCLOG2")
    * // GC occurs -> logs into "/GCLOG2", sets default log to "/GCLOG"
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * changed (3.2.9) -- adds the filename argument.
    * changed (3.3.209) -- adds the flag argument.
    * changed (3.5.0) -- made the efun privileged.
    * }
    * 
    * @see efun::rusage(), master::valid_write(), master::privilege_violation()
   **/
   void garbage_collection(string filename, int flag);
}
