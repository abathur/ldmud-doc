.. efun:: string read_file(string file, int start, int number)

Reads lines from file.
If <start> is not given or 0, the file is read from the
beginning, else the efun starts reading at the beginning of line
<start>.

If <number> is not given or 0, the whole file is read, else
just the given amount of lines.

If <start> would be outside the actual size of the file, 0 is
returned instead of a string.

The maximum bytes (not lines!) being read per call is LIMIT_FILE (see
query_limits()).

  .. seealso:: :efun:`read_bytes`, :efun:`write_file`
