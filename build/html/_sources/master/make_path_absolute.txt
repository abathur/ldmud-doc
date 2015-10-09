.. master:: string make_path_absolute(string str)

  Absolutize a relative filename str given to the editor. Should
  return the full pathname of the file to use. Any non-string
  result will act as "bad file name".

  .. seealso:: :efun:`ed`, :master:`valid_write`
