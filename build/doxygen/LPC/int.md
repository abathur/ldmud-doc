int {#driver_LPC_int}
=====================
An integer. Normally full 32 bits signed, yielding a range of at least -2,147,483,648 to 2,147,483,647. The exact available range is given by the predefined macros __INT_MIN__ and __INT_MAX__.

## SYNTAX #

integer        ::= decimalinteger | octinteger | hexinteger | bininteger | char
decimalinteger ::= nonzerodigit digit* | "0"+
nonzerodigit   ::= "1"..."9"
digit          ::= "0"..."9"
octinteger     ::= "0" ("o" | "O") octdigit+
hexinteger     ::= "0" ("x" | "X") hexdigit+
bininteger     ::= "0" ("b" | "B") bindigit+
octdigit       ::= "0"..."7"
hexdigit       ::= digit | "a"..."f" | "A"..."F"
bindigit       ::= "0" | "1"
char           ::= "'" unicode_char "'"

@usage{
Integer values can be specified in decimal, in sedecimal when preceeded by 0x (e.g. 0x11), binary when preceeded by 0b (e.g. 0b00010001), octal when preceeded by 0o (e.g. 0o21) and as character yielding the charset value for the character as the number to use (e.g. '0' yields 48 on ASCII machines).
Character values are enclosed in single-quotes ('), with the sequence ''' returning the single-quote itself. Instead of the literal character an escape-sequence can be written between the single-quotes:
\<CR>     : Carriage Return (0x0d)

\<CR><LF> : ignored

\<LF>     : ignored

\<LF><CR> : ignored

\"   : The double quote (")
\N

the character code N in decimal

\0xN

the character code N in sedecimal

\xN

the character code N in sedecimal

\0oN

the character code N in octal

\0bN

the character code N in binary

\a

BEL (0x07)

\b

Backspace (0x08)

\t

Tab (0x09)

\e

Escape (0x1b)

\n

Newline (0x0a)

\f

Formfeed (0x0c)

\r

Carriage Return (0x0d)

\<other character>

the given character
}

@see @ref driver_LPC_types "types", @ref driver_LPC_float "float", @ref driver_LPC_string "string", @ref driver_LPC_modifiers "public"
