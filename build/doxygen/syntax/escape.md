escape {#driver_syntax_escape}
==============================
Character escape codes are used to represent some common special characters that would be awkward or impossible to enter in the source program directly. The escape characters come in two varieties: 'character escapes', which can be used to represent some particular formatting and special characters, and 'numeric escapes', which allow a character to be specified by its numeric encoding.

Escapes begin always with a backslash ''. If the following characters could not be treated as a valid escape the backslash is merely ignored.

The following character escapes are available in LPC (the code may differ from platform to platform):

| escape | code | name             |
|        |      |                  |
|--------|------|------------------|
| `\a`   | 007  | Bell             |
| `\b`   | 008  | Backspace        |
| `\e`   | 027  | Escape           |
| `\f`   | 012  | Formfeed         |
| `\n`   | 010  | Newline          |
| `\r`   | 013  | Carriage-Return  |
| `\t`   | 009  | Tabulator        |
| `\\`   | 092  | Backslash itself |
|        |      |                  |
| `\'`   | 039  | Single quote     |
| `\"`   | 034  | Double quote     |

The single quote may appear without preceding backslash in character constants, and the double quote may appear without a backslash in string constants.

The numeric escapes could be used to express a character directly by its code in binary, octal, decimal or hexadecimal notation.

`\0b`
Beginning of binary notation

`\0o`
Beginning of octal notation

`\0x`
Beginning of hexadecimal notation

`\x`
Beginning of hexadecimal notation

A backslash followed by a digit (`0-9`) which does not map to one of the above starts an escape in decimal notation.

A numeric escape terminates when N digits have been used up or when the first character that is not a valid digit in that notation is encountered. N is 2 for hexadeximals, 3 for decimals and octals and 8 for binarys.

If the specified code is greater than 255 a warning is issued and the value modulo 256 is used.

@usage{
Put a newline at the end of user output:

~~~{.c}
"You enter.\n"

~~~
Alert the user:

~~~{.c}
"Beeep.\a Wake up\n"

~~~
Put a double quote in a string:

~~~{.c}
"You say \"hello\"\n"

~~~
Write the line from above:

~~~{.c}
"\"You say \\\"hello\\\"\\n\""

~~~
Put a single quote in a string:

~~~{.c}
"You say 'hello'\n"

~~~
Some forms to write "abcde":

~~~{.c}
"abcde"
"ab\99de"              (with c's code being 99)
"ab\099de"
"ab\x63de"             (99 = 0x63)
"ab\0x63de"

~~~
The following string consists of two characters:

~~~{.c}
"\0111"                (\011 and 1)

~~~
The following string consists of three characters:

~~~{.c}
"\0o090"               (\000 and 9 and 0)

~~~

}
