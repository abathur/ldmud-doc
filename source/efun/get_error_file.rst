.. efun:: mixed * get_error_file(string name, int set_forget_flag)

  Return information about the last error which occured for :arg:`name` (where :arg:`name` is a valid name from the wiz list).

  Result is an array of four elements: the filename of the program where the error occured, the linenumber in the program, the error message (runtime error messages usually start with a '*'), and a numerical flag (the 'forget flag') if the error information has been queried already.

  If there is no error stored for the given :arg:`name`, 0 is returned.

  If :arg:`set_forget_flag` is non-zero, the 'forget' flag is set for the error message after it has been returned.

  .. seealso:: :efun:`ed`, :master:`valid_read`
