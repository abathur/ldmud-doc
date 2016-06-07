escape {#driver_LPC_escape}
===========================
@usage{
Put a newline at the end of user output:
"You enter.\n"
Alert the user:
"Beeep.\a Wake up\n"
Put a double quote in a string:
"You say \"hello\"\n"
Write the line from above:
"\"You say \\\"hello\\\"\\n\""
Put a single quote in a string:
"You say 'hello'\n"
Some forms to write "abcde":
"abcde"
"ab\99de"              (with c's code being 99)
"ab\099de"
"ab\x63de"             (99 = 0x63)
"ab\0x63de"
The following string consists of two characters:
"\0111"                (\011 and 1)
The following string consists of three characters:
"\0o090"               (\000 and 9 and 0)
}
