.. efun:: int * rusage(void)
  :optional:

  Return an array with current system resource usage statistics, as returned by the getrusage(2) of Unix.

  .. todo:: general revision per unixisms?

  namely::

    ({
      utime, stime, maxrss, rus.ru_ixrss, rus.ru_idrss,
      rus.ru_isrss, rus.ru_minflt, rus.ru_majflt, rus.ru_nswap,
      rus.ru_inblock, rus.ru_oublock, rus.ru_msgsnd,
      rus.ru_msgrcv, rus.ru_nsignals, rus.ru_nvcsw,
      rus.ru_nivcsw
    })

  .. seealso::        <sys/resource.h>(Unix)
