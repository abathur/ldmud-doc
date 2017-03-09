public class efun {
   /**
    * If \p map is given as a non-0 value, this efun expands all colour-defines of the form "%^KEY%^" (see below for details) from the input-string and replaces them by the apropriate values found for the color-key specified by \p map.
    * 
    * If \p map is a mapping, the entries queries have the format "KEY" : "value", non-string contents are ignored with one exception: if the mapping contains an entry 0:value, it is used as a default for all otherwise unrecognized keys. The value in this case can be a string, or a closure. If it is a closure, it takes the key as argument and has to return the replacement string.
    * 
    * If \p map is given as a closure, it is called with the KEYs to replace, and has to return the replacement string.
    * 
    * The special keys `%^%^` and `%%^^` are always replaced with the literal `%^`.
    * 
    * The parameters \p wrap and \p indent are both optional. If only \p wrap is given, \p str will be linewrapped at \p wrap columns (`"this is the first line\nand this is the second line"`). If \p indent is also given, all wrapped lines will also be indented by \p indent blanks (`"this is the first line\n   and this is the indented second one"`.
    * 
    * The wrapper itself ignores the length of the color macros and that what they contain, it wraps the string based on the length of the other chars inside. Therefore it is color-aware.
    * 
    * If \p map is given as 0, the efun does no colour-define detection and replacement at all, but still does linewrapping and indentation if requested. This way efun::terminal_colour() doubles as a simple line wrapping function, duplicating the functionality also provided by `sprintf("%-=s", ...)`.
    * 
    * ## Key Recognition Strategy #
    * 
    * As mentioned above, the special keys `%^%^` and `%%^^` are always replaced with the literal `%^` and play no role in the following considerations.
    * 
    * The input string is supposed to follow this syntax:
    * 
    * ~~~{.c}
    * text { '%^' colorkey '%^' text } [ '%^' colorkey ]
    * 
    * ~~~
    * or in words: the efun splits up the string at every `%^` it finds and then treats every second substring as color key.
    * 
    * @par note: This is different from the way MudOS treats the input string. MudOS uses this syntax:~~~{.c}
    * key_or_text { '%^' key_or_text }
    * 
    * ~~~Or in words: the MudOS efun splits the string at every `%^` and then tries to treat every substring as color key. One can achieve the MudOS behaviour with this LPC function:~~~{.c}
    * string mudos_terminal_colour(string str, mapping ext, int w, int i) {
    *   return terminal_colour("%^"+implode(explode(str, "%^")-({""})
    *                                      ,"%^%^")
    *                         , ext, w, i);
    * }
    * 
    * ~~~
    * 
    * @synopsis{
    * varargs string terminal_colour(string str, null|mapping|closure map, int wrap, int indent)
    * }
    * 
    * @usage{
    * The below will result in str == `"ansi-green and  and BLUE"`:
    * 
    * ~~~{.c}
    * mapping trans;
    * string str;
    * 
    * trans = ([ "GREEN" : "ansi-green", "RED" : "", "BLUE" : 1 ]);
    * 
    * str = terminal_colour( "%^GREEN%^ and %^RED%^ and %^BLUE%^", trans );
    * 
    * ~~~
    * - `%^GREEN%^` is expanded to `ansi-green`,
    * - `%^RED%^` is stripped (more accurately, it's replaced with `""`)
    * - `%^BLUE%^` only has each `%^` removed because the contents of trans are not valid (i.e. not a string). The same would happen to `%^DEFINES%^` (because the key is not found inside the trans mapping).
    * 
    * @par tip: If you have adjacent keys, be careful not to omit part of the key indicator. For example, `terminal_colour( "%^GREEN%^RED%^", trans )` will return the logical but sometimes unexpected `"ansi-greenRED"`. To get `"ansi-green"`, you'd use: `terminal_colour( "%^GREEN%^%^RED%^", trans )`.
    * 
    * }
    * 
    * @history{
    * introduced (3.2.4) -- Efun idea and initial implementation taken from MudOS;
    * changed (3.2.8) -- sorted out the key recognition strategy (including pure wrapping mode)
    * changed (3.2.9/3.3.58) -- added the use of closures to specify the colour mappings.
    * changed (3.2.9/3.3.102) -- officialized the "%%^^" replacement pattern for better MudOS compatibility.
    * }
    * 
    * @see efun::sprintf()
   **/
   varargs string terminal_colour(string str, null|mapping|closure map, int wrap, int indent);
}
