print_prompt {#driver_hook_print_prompt}
========================================
Optional hook to print the current command prompt. If this hook is not set, the driver will just print the prompt to the user.

The hook is called with the prompt string as single argument and has to print the prompt, e.g. using write() or binary_message().

If the hook is a string, it is the name of an lfun in the command giver. If the hook is a closure, it is called with the command giver as previous object.

@headerfile <sys/driver_hooks.h>

@synopsis{
set_driver_hook(H_PRINT_PROMPT, value)
}

@history{
introduced (3.3.163)
}

@see @ref driver_hook_default_prompt "default_prompt"
Arguments: 
- value (@ref driver_LPC_string "string") -- void <name>(string prompt).
- value (@ref driver_LPC_closures "closure") -- void <closure>(string prompt)
