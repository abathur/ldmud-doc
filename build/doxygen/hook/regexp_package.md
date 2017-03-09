regexp_package {#driver_hook_regexp_package}
============================================
@headerfile <sys/regexp.h>

@headerfile <sys/driver_hooks.h>

@synopsis{
set_driver_hook(H_REGEXP_PACKAGE, value)
}

@param value 0 | RE_PCRE | RE_TRADITIONAL

Optional hook to select the default regexp package to use for regular expression functions.

If set to 0, the default package determined by the driver's configuration/commandline options is used.

@history{
introduced (3.3.595)
}

@see @ref driver_hook_overview "hook", @ref driver_hook_default_prompt "default_prompt", @ref driver_admin_invocation "invocation"
