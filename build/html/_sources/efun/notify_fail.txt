.. efun:: int notify_fail(string str)
int notify_fail(closure cl)

DESCRIPTION
Store str as the error message given instead of the default
message ``What ?''. The result is always 0.

If a closure is given, it is executed to return the error
message string, but not before all attempts to execute the
commandline failed (read: not at the time of the call to
notify_fail()). The closure receives as argument the original
commandgiver; usually it is identical to this_player(), unless
the modify_cmd hook changed that.

If notify_fail() is called more than once for this command, only the
last call will be used. However, calls to notify_fail() in nested
commands have no effect on this command.

The idea of this function is to give better error messages
instead of simply 'What ?'.

It is also better to use
        return notify_fail(message);
instead of
        write(message); return 1;

Other objects will get the chance to evaluate the verb.

.. history
Returntype changed in LDMud 3.2.6 from void to int.
Since LDMud 3.2.7, notify-fail settings are saved over nested
commands, and NPCs can see their notify-fail messages.

  .. seealso:: :efun:`add_action`, :efun:`command`, :efun:`query_verb`, :efun:`query_command`, :efun:`query_notify_fail`, :concept:`hooks`
