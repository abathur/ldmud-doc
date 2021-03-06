.. hook:: H_PRINT_PROMPT

  :arg string value: void <name>(string prompt).
  :arg closure value: void <closure>(string prompt)

  Optional hook to print the current command prompt. If this hook is not set, the driver will just print the prompt to the user.

  The hook is called with the prompt string as single argument and has to print the prompt, e.g. using :efun:`write` or :efun:`binary_message`.

  If the hook is a string, it is the name of an lfun in the command giver. If the hook is a closure, it is called with the command giver as previous object.

  :history 3.3.163 introduced:

  .. seealso:: :overview:`hook`, :hook:`default_prompt`
