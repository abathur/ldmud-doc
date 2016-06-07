regexp_package {#driver_hook_regexp_package}
============================================
Optional hook to select the default regexp package to use for regular expression functions.

If set to 0, the default package determined by the driver's configuration/commandline options is used.

@headerfile <sys/regexp.h>

@headerfile <sys/driver_hooks.h>

@synopsis{
set_driver_hook(H_REGEXP_PACKAGE, value)
}

@history{
introduced (3.3.595)
}

@see @ref driver_hook_default_prompt "default_prompt", @ref driver_driver_invocation "invocation", @ref driver_concepts_regexp "regexp"
Arguments: 
- value (@ref driver_LPC_int "int") -- 0 | RE_PCRE | RE_TRADITIONAL
