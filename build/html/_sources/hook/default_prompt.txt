.. hook:: H_DEFAULT_PROMPT

  :arg string value: <prompt>
  :arg closure value: string <closure>()

  Optional hook for the command prompt. If this hook is not used,
  the driver will use "> " as the command prompt.

  The hook can be given as string or as closure. If it is a
  closure, it is called with the commandgiver being the calling
  object. If the result is a string it will be printed,
  otherwise it will be ignored.

  :history 3.3.163 introduced:

  .. seealso:: :concept:`hooks`, :hook:`print_prompt`
