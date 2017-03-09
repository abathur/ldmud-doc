public class efun {
   /**
    * Searches string \p str for occurences of a "value by function call", which is an implicit function call surrounded by `@@`. The value should contain a string like this:
    * 
    * ~~~{.c}
    * @@function[:filename][|arg|arg]@@
    * 
    * ~~~
    * `function` must return a string or else the string which should be processed will be returned unchanged. Both the filename and the args are optional.
    * 
    * Caution: This does not recurse over returned replacement values. If a function returns another function description, that description will not be replaced.
    * Consecutive function calls can be written adjacent:
    * 
    * ~~~{.c}
    * @@function1@@function2@@
    * 
    * ~~~
    * @par security: Using efun::process_string() can lead to severe security problems.
    * 
    * @synopsis{
    * string process_string(string str)
    * }
    * 
    * @usage{
    * Given the below example, calling `func()` will print out the string "abcdef":
    * 
    * ~~~{.c}
    * string foo(string str) {
    *    return "ab"+str+"ef";
    * }
    * void func() {
    *    write(process_string("@@foo|cd@@")+"\n");
    * }
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * changed (3.2.1@34) -- Because of the security problems, process_string() is an optional efun.
    * changed (3.3.160) -- removed the undocumented 'feature' that a function call declaration could be terminated by a space. In turn this now allows the use of arguments with spaces.
    * }
    * 
    * @see efun::notify_fail(), @ref driver_syntax_closures "closure", master::get_bb_uid()
   **/
   string process_string(string str);
}
