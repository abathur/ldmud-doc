public class efun {
   /**
    * Most of the characters in the format string \p fmt get passed straight through to the output (i.e.: printed or put in the return string), to format arguments into the string it is necessary to include an argument format string (AFS) in the format string. An AFS is a series of characters starting with a percent sign "%" and terminated with a argument type specifier.
    * 
    * To include a "%" sign in the output, it is necessary to include a double percent sign "%%". The sequence "%^" will output "%^" again.
    * 
    * Valid argument type specifiers are:
    * "s" : the argument is a string.
    * "d" : the argument is an integer to be included in decimal representation.
    * "i" : same as "d".
    * "b" : the argument is an integer to be included in binary representation.
    * "o" : the argument is an integer to be included in octal representation.
    * "x" : the argument is an integer to be included in hexadecimal representation.
    * "X" : as "x" except letters are capitalised.
    * "e","E","f","g","G" : the argument is a float to be included in decimal representation; see examples for details.
    * "c" : the argument is an int to included as a character.
    * "O" : the argument is an LPC datatype to be printed in an arbituary format, this is for debugging purposes. If the argument is an object the function master::printf_obj_name() is called on the master object with the object as a parameter; the string returned is included in brackets at the end of object file name. If 0 is returned, nothing is appended after the file name.
    * "Q"   Like "O", except that special characters in strings are printed in LPC notation.
    * 
    * Between the percent sign and the argument type specifier in the AFS, the following modifiers can be included to specify the formatting information. Order is not important unless otherwise specified. "n" is used to specify a integer, which can be a "*" in which case the next argument is used as the number.
    * 
    * Modifiers:
    *    n    specifies the field size. If the size is prepended with a 0, the argument is printed with leading zeroes.
    *    
    * "."n  specifies the precision, for simple strings (not columns or tables) specifies the truncation length.
    * ":"n  n specifies both the field size _and_ the precision; if n is prepended by a zero then the pad string is set to "0".
    * "'X'" the pad string is set to the char(s) between the single quotes; if the field size is also prepended with a zero then whichever is specified last will overrule. NOTE: to include "'" in the pad string, you must use "\'" (as the backslash has to be escaped past the interpreter); similarly, to include "" you must use "\\".
    * " "   pad positive integers with a space.
    * "+"   pad positive integers with a plus sign.
    * "-"   left-aligned within field size.
    * 
    *    NB: std (s)printf() defaults to right alignment, which is unnatural in the context of a mainly string based language but has been retained for "compatibility" ;)
    *    
    * "|"   centered within field size.
    * "$"   justified to field size. Ignored unless the type specifier is 's'.
    * "="   column mode. Ignored unless the argument type specifier is 's'. Field size must be specified; if precision is specified then it sets the width for the string to be wordwrapped at, but otherwise the field size is used. Field size specifies the width of the column the last line of the column is padded with spaces to achieve this length.
    * "#"   For strings: table mode.
    * 
    *       Field size must be specified; if precision is specified it sets the number of columns in the table, otherwise the number is "optimally" generated (as few lines and columns as possible). Table mode is passed a list of backslash-n separated 'words' which are put in a format similar to that of ls.
    *       
    *    For %O/%Q: compact output.
    *    
    * "@"   the argument is an array. The corresponding AFS (minus all "@") is applied to each element of the array.
    * 
    * When the formatting of an element results in several output lines (column or table mode) and no explicit pad string has been defined, any padding whitespace before the newlines of all but the last line is removed. However, if an explicit pad string has been given, even if it is the simple char:` `(U+00020 SPACE), the padding will not be removed.
    * 
    * @synopsis{
    * string sprintf(string fmt, ...)
    * }
    * 
    * @usage{
    * ~~~{.c}
    * sprintf("decimal=%d, octal=%o, hexadecimal=%x\n", 7, 7, 7);
    * 
    * sprintf("array=%O\n", ({1, 2, 3}));
    * 
    * // this will return the following:
    * //   ({ // sizeof() == 3
    * //     1,
    * //     2,
    * //     3
    * //   })
    * // An array will be printed recursively and each element of the
    * // array will be indented. Can also be used as a debugging tool.
    * 
    * sprintf("%-*#s\n", 80, implode(get_dir("~/."), "\n"));
    * 
    * sprintf("foo")                      // returns "foo"
    * 
    * sprintf("%s","foo")                 // returns "foo"
    * sprintf("%7s","foo")                // returns "    foo"
    * sprintf("%-7s","foo")               // returns "foo    "
    * sprintf("%|7s","foo")               // returns "  foo  "
    * sprintf("%7'.'s","foo")             // returns "....foo"
    * sprintf("%-7'+-'s","foo")           // returns "foo+-+-"
    * sprintf("%|9'-+'s","foo")           // returns "-+-foo-+-"
    * sprintf("%3s","foobarbloh")         // returns "foobarbloh"
    * sprintf("%3.6s","foobarbloh")       // returns "foobar"
    * sprintf("%6.3s","foobarbloh")       // returns "   foo"
    * sprintf("%:6s","foobarbloh")        // returns "foobar"
    * sprintf("%:3s","foobarbloh")        // returns "foo"
    * sprintf("%*.*s",-7,2,"foobarbloh")  // returns "fo     "
    * 
    * sprintf("%=12s","this is a very long sentence\n")
    *                     // returns "   this is a\n"
    *                     //         "   very long\n"
    *                     //         "    sentence\n"
    * sprintf("%=-12s","this is a very long sentence\n")
    *                     // returns "this is a\n"
    *                     //         "very long\n"
    *                     //         "sentence\n"
    * sprintf("%=|12s","this is a very long sentence\n")
    *                     // returns "  this is a\n"
    *                     //         "  very long\n"
    *                     //         "  sentence\n"
    * sprintf("%=10.6s","this is a very long sentence\n")
    *                     // returns "      this\n"
    *                     //         "      is a\n"
    *                     //         "      very\n"
    *                     //         "      long\n"
    *                     //         "    senten\n"
    *                     //         "        ce\n"
    * sprintf("%#-40.3s",
    *         "one\ntwo\nthree\nfour\nfive\nsix\nseven\neight\nnine\nten\n")
    *                     // returns "one          five         nine\n"
    *                     //         "two          six          ten\n"
    *                     //         "three        seven        \n"
    *                     //         "four         eight        "
    * sprintf("%#-40s",
    *         "one\ntwo\nthree\nfour\nfive\nsix\nseven\neight\nnine\nten\n")
    *                     // returns "one     three   five    seven   nine\n"
    *                     //         "two     four    six     eight   ten"
    * 
    * sprintf("%@-5s",({"foo","bar","bloh"})) // returns "foo  bar  bloh "
    * 
    * sprintf("%d",123)                   // returns "123"
    * sprintf("%7d",123)                  // returns "    123"
    * sprintf("%-7d",123)                 // returns "123" (yes, really)
    * sprintf("%d/%d",123,-123)           // returns "123/-123"
    * sprintf("% d/% d",123,-123)         // returns " 123/-123"
    * sprintf("%+d/%+d",123,-123)         // returns "+123/-123"
    * sprintf("%+6d/%6d",123,123)         // returns " +123/  123"
    * sprintf("%|6d",123)                 // returns "  123" (yes, really)
    * sprintf("%|10d",123)                // returns "    123" (yes, really)
    * sprintf("%|10d%3s",123,"foo")       // returns "    123   foo"
    * 
    * sprintf("%o",16)                    // returns "20"
    * sprintf("%'0'3o",8)                 // returns "010"
    * 
    * sprintf("%x",123)                   // returns "7b"
    * sprintf("%X",123)                   // returns "7B"
    * 
    * sprintf("%f",123.5)                 // returns "124"
    * sprintf("%8.3f",123.5)              // returns " 123.500"
    * sprintf("%E",123.5)                 // returns "1E+02"
    * sprintf("%12.4e",123.5)             // returns "  1.2350e+02"
    * sprintf("%g",123.5)                 // returns "124"
    * sprintf("%8.3G",123.5)              // returns "     124"
    * sprintf("%8.6g",123.5)              // returns "   123.5"
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * changed (3.2.9) -- added the %^ sequence for compatibility with terminal_colour

added the %Q sequence

clarified the meaning of leading 0s in the field size modifier

clarified the interaction between the padding and newlines

added the $ formatter for justified printing of strings.
    * added the %^ sequence for compatibility with terminal_colour
    * added the %Q sequence
    * clarified the meaning of leading 0s in the field size modifier
    * clarified the interaction between the padding and newlines
    * added the $ formatter for justified printing of strings.
    * changed (3.2.10) -- added modifier # for %O/%Q and the datatype %b.
    * }
    * 
    * @see efun::printf(), efun::terminal_colour()
   **/
   string sprintf(string fmt, ...);
}
