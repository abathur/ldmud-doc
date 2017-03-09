preprocessor {#driver_syntax_preprocessor}
==========================================
The LPC driver understands the following preprocessor directives:

`#include, #define, #if, #ifdef, #ifndef, #else, #elif, #endif, #undef`
same as in ANSI C

`#line <num>`
line numbers start at <em>num</em> with the next line

`#echo`
the rest of the line is printed to the error output (stderr), thus can be captured into a log file

`#pragma`
see the separate @ref driver_syntax_pragma "pragma" page

@see @ref driver_syntax_pragma "pragma", @ref driver_topics_predefined "predefined"
