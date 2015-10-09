.. hook:: H_REGEXP_PACKAGE
  :include: <sys/regexp.h>

  :arg int value: 0, RE_PCRE, RE_TRADITIONAL

  Optional hook to select the default regexp package to use
  for regular expression functions.

  If set to 0, the default package determined by the driver's
  configuration/commandline options is used.

  :history 3.3.595 introduced:

  .. seealso:: :concept:`hooks`, :hook:`default_prompt`, :driver:`invocation`, :concept:`regexp`
