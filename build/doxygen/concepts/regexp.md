regexp {#driver_concepts_regexp}
================================
LDMud supports both the traditional regular expressions as implemented by Henry Spencer ("HS" or "traditional"), and optionally the Perl-compatible regular expressions by Philip Hazel ("PCRE").

Both packages can be used concurrently, with the selection being made through extra option flags argument to the efuns. One of the two packages can be selected at compile time, by commandline argument, and by driver hook to be the default package.

If the host system does not supply PCREs at compile-time, they will not be availablea in the driver.

The packages differ in the expressivity of their expressions (PCRE offering more options that Henry Spencer's package), though they both implement the common subset outlined below.

All regular expression efuns take an additional options parameter, which is a an number composed of bitflags, and is used to modify the exact behaviour of the expression evaluation. In addition, certain efuns may accept additional specific options.

For details, refer to the detailed manpages:

- @ref driver_concepts_hsregexp "hsregexp" for the Henry Spencer package
- @ref driver_concepts_pcre "pcre" for the PCRE package

## REGULAR EXPRESSION DETAILS #

A regular expression is a pattern that is matched against a subject string from left to right. Most characters stand for themselves in a pattern, and match the corresponding characters in the subject. As a trivial example, the pattern @aThe quick brown fox` matches a portion of a subject string that is identical to itself. The power of regular expressions comes from the ability to include alternatives and repetitions in the pattern. These are encoded in the pattern by the use of metacharacters, which do not stand for themselves but instead are interpreted in some special way.

The following metacharacters are 'universal' in that both regexp packages understand them in the same way:

+------------+--------------------------------------------------------------------------------------------+
| Metachars  | Description                                                                                |
+------------+--------------------------------------------------------------------------------------------+
| @a.`       | Match any character.                                                                       |
+------------+--------------------------------------------------------------------------------------------+
| @a^`       | Match begin of line.                                                                       |
+------------+--------------------------------------------------------------------------------------------+
| @a$`       | Match end of line.                                                                         |
+------------+--------------------------------------------------------------------------------------------+
| @ax|y`     | Match regexp x or regexp y.                                                                |
+------------+--------------------------------------------------------------------------------------------+
| @a()`      | Match enclosed regexp like a 'simple' one.                                                 |
+------------+--------------------------------------------------------------------------------------------+
| @ax*`      | Match any number (0 or more) of regexp x.                                                  |
+------------+--------------------------------------------------------------------------------------------+
| @ax+`      | Match any number (1 or more) of regexp x.                                                  |
+------------+--------------------------------------------------------------------------------------------+
| @a[..]`    | Match one of the characters enclosed.                                                      |
+------------+--------------------------------------------------------------------------------------------+
| @a[^ ..]`  | Match none of the characters enclosed. The .. are to replaced by single characters or      |
|            | character ranges:                                                                          |
+------------+--------------------------------------------------------------------------------------------+
| @a[abc]`   | matches a, b or c.                                                                         |
+------------+--------------------------------------------------------------------------------------------+
| @a[ab0-9]` | matches a, b or any digit.                                                                 |
+------------+--------------------------------------------------------------------------------------------+
| @a[^a-z]`  | does not match any lowercase character.                                                    |
+------------+--------------------------------------------------------------------------------------------+
| @subpage   | not a word boundary                                                                        |
| driver_LP  |                                                                                            |
| C_string#  |                                                                                            |
| term-b     |                                                                                            |
| "\B"       |                                                                                            |
+------------+--------------------------------------------------------------------------------------------+
| @a\c`      | match character c even if it's one of the special characters.                              |
+------------+--------------------------------------------------------------------------------------------+

The following metacharacters or metacharacter combinations implement
similar functions in the two regexp packages;

+------------+--------------------------------------------------------------------------------------------+
| Metachars  | Description                                                                                |
+------------+--------------------------------------------------------------------------------------------+
| @subpage   | PCRE: word boundary, also used inconjunction with w (any "word" character) and W (any      |
| driver_LP  | "non-word" character).                                                                     |
| C_string#  |                                                                                            |
| term-b     |                                                                                            |
| "\b"       |                                                                                            |
+------------+--------------------------------------------------------------------------------------------+
| @a\<`      | HS: Match begin of word.                                                                   |
+------------+--------------------------------------------------------------------------------------------+
| @a\>`      | HS: Match end of word.                                                                     |
+------------+--------------------------------------------------------------------------------------------+

## OPTIONS #

The package is selected with these option flags:

RE_PCRE
RE_TRADITIONAL
These flags are also used for @ref driver_hook_regexp_package "H_REGEXP_PACKAGE".

Traditional regular expressions understand one option:

RE_EXCOMPATIBLE
PCRE understands these options:

RE_ANCHORED
RE_CASELESS
RE_DOLLAR_ENDONLY
RE_DOTALL
RE_EXTENDED
RE_MULTILINE
RE_UNGREEDY
RE_NOTBOL
RE_NOTEOL
RE_NOTEMPTY

@history{
changed (3.3.596) -- implemented the concurrent use of both packages.
}

@see @ref driver_concepts_hsregexp "hsregexp", @ref driver_concepts_pcre "pcre", @ref driver_hook_regexp_package "regexp_package", efun::regexp(), efun::regexplode(), efun::regmatch(), efun::regreplace(), efun::regexp_package(), @ref driver_driver_invocation "invocation"
