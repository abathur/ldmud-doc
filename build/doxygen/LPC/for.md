for {#driver_LPC_for}
=====================
@usage{
Examples for legal <init> expressions are:
for (i = 0; ...
for (i = 0, j = 0; ...
for (i = 0, int j = i; ...
for (int j = 4; ...
Illegal <init> expressions are:
for (int i; ...      : no value assigned
for (int i += 4; ... : only plain assignments allowed
A 'break' in the 'statement' will terminate the loop. A 'continue' will continue the execution from the beginning of the loop.
}

@see 
