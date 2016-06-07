public class efun {
   /**
    * @synopsis{
    * string process_string(string str)
    * }
    * 
   **/
   string process_string(string str);
}
Searches string str for occurences of a "value by function
call", which is an implicit function call surrounded by @@. See
"value_by_function_call" in the principles section.

The value should contain a string like this:
@@function[:filename][>>|<<arg|arg]@@

<function> must return a string or else the string which should be
processed will be returned unchanged.

process_string() does not recurse over returned
replacement values. If a function returns another function
description, that description will not be replaced.

Both the filename and the args are optional.

Consecutive function calls can be written adjacent:

   @@function1@@function2@@

EXAMPLES
string foo(string str) {

   return "ab"+str+"ef";

}
void func() {

   write(process_string("@@foo|cd@@")+"n");

}

The function func() will print out the string "abcdef".

BUGS
Using process_string() can lead to severe security problems.

Because of the security problems, process_string() is an
optional efun since @subpage driver_mailto:3.2.1@34 "3.2.1@34"
LDMud 3.3.160 removed the undocumented 'feature' that a function call
declaration could be terminated by a space. In turn this now allows
the use of arguments with spaces.

   See Also: 
      efun::notify_fail(), @ref driver_LPC_closures "closures", master::get_bb_uid()
