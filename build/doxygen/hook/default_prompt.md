default_prompt {#driver_hook_default_prompt}
============================================
Optional hook for the command prompt. If this hook is not used, the driver will use "> " as the command prompt.

The hook can be given as string or as closure. If it is a closure, it is called with the commandgiver being the calling object. If the result is a string it will be printed, otherwise it will be ignored.

@headerfile <sys/driver_hooks.h>

@synopsis{
set_driver_hook(H_DEFAULT_PROMPT, value)
}

@history{
introduced (3.3.163)
}

@see @ref driver_hook_print_prompt "print_prompt"
Arguments: 
- value (@ref driver_LPC_string "string") -- <prompt>
- value (@ref driver_LPC_closures "closure") -- string <closure>()
