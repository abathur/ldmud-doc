.. topic:: Regular Expressions
  :name: regexp
  :topics: driver

  LDMud supports both the traditional regular expressions as implemented by Henry Spencer ("HS" or "traditional"), and optionally the Perl-compatible regular expressions by Philip Hazel ("PCRE").

  Both packages can be used concurrently, with the selection being made through extra option flags argument to the efuns. One of the two packages can be selected at compile time, by commandline argument, and by driver hook to be the default package.

  If the host system does not supply PCREs at compile-time, they will not be availablea in the driver.

  The packages differ in the expressivity of their expressions (PCRE offering more options that Henry Spencer's package), though they both implement the common subset outlined below.

  All regular expression efuns take an additional options parameter, which is a an number composed of bitflags, and is used to modify the exact behaviour of the expression evaluation. In addition, certain efuns may accept additional specific options.

  For details, refer to the detailed manpages:

  .. todo:: intentionally leaving bad roles below until I am catching the underlying sphinx/docutils errors that they trigger.

  * :concept:`hsregexp` for the Henry Spencer package
  * :concept:`pcre` for the PCRE package

  .. subtopic:: Regular Expression Details

    A regular expression is a pattern that is matched against a subject string from left to right. Most characters stand for themselves in a pattern, and match the corresponding characters in the subject. As a trivial example, the pattern ``The quick brown fox`` matches a portion of a subject string that is identical to itself. The power of regular expressions comes from the ability to include alternatives and repetitions in the pattern. These are encoded in the pattern by the use of metacharacters, which do not stand for themselves but instead are interpreted in some special way.

    The following metacharacters are 'universal' in that both regexp packages understand them in the same way:

    .. list-table::
      :widths: 10 90
      :stub-columns: 1

      * - Metachars
        - Description

      * - ``.``
        - Match any character.

      * - ``^``
        - Match begin of line.

      * - ``$``
        - Match end of line.

      * - ``x|y``
        - Match regexp x or regexp y.

      * - ``()``
        - Match enclosed regexp like a 'simple' one.

      * - ``x*``
        - Match any number (0 or more) of regexp x.

      * - ``x+``
        - Match any number (1 or more) of regexp x.

      * - ``[..]``
        - Match one of the characters enclosed.

      * - ``[^ ..]``
        - Match none of the characters enclosed. The .. are to replaced by single characters or character ranges:

      * - ``[abc]``
        - matches a, b or c.

      * - ``[ab0-9]``
        - matches a, b or any digit.

      * - ``[^a-z]``
        - does not match any lowercase character.

      * - ``\\B``
        - not a word boundary

      * - ``\\c``
        - match character c even if it's one of the special characters.

    The following metacharacters or metacharacter combinations implement similar functions in the two regexp packages;

    .. list-table::
      :widths: 10 90
      :stub-columns: 1

      * - Metachars
        - Description

      * - ``\\b``
        - PCRE: word boundary, also used in conjunction with ``\w`` (any "word" character) and ``\W`` (any "non-word" character).

      * - ``\\<``
        - HS: Match begin of word.

      * - ``\\>``
        - HS: Match end of word.

  .. subtopic:: Options

    The package is selected with these option flags:

    .. macro:: RE_PCRE
    .. macro:: RE_TRADITIONAL

    These flags are also used for :hook:`H_REGEXP_PACKAGE`.

    Traditional regular expressions understand one option:

    .. macro:: RE_EXCOMPATIBLE

    PCRE understands these options:

    .. macro:: RE_ANCHORED
    .. macro:: RE_CASELESS
    .. macro:: RE_DOLLAR_ENDONLY
    .. macro:: RE_DOTALL
    .. macro:: RE_EXTENDED
    .. macro:: RE_MULTILINE
    .. macro:: RE_UNGREEDY
    .. macro:: RE_NOTBOL
    .. macro:: RE_NOTEOL
    .. macro:: RE_NOTEMPTY

  :history 3.3.596 changed: implemented the concurrent use of both packages.

  .. seealso:: :concept:`hsregexp`, :concept:`pcre`, :hook:`regexp_package`, :efun:`regexp`, :efun:`regexplode`, :efun:`regmatch`, :efun:`regreplace`, :efun:`regexp_package`, :topic:`invocation`
