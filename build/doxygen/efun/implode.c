public class efun {
   /**
    * Concatenate all strings found in array \p arr, with the string \p del between each element. Only strings are used from the array.
    * 
    * @synopsis{
    * string implode(mixed *arr, string del)
    * }
    * 
    * @usage{
    * This basic example inserts an asterisk between each array element:
    * 
    * ~~~{.c}
    * implode(({ "foo", "bar", "" }), "*") // returns "foo*bar*"
    * 
    * ~~~
    * Because implode ignores non-string elements, the result below only includes a single "b":
    * 
    * ~~~{.c}
    * implode(({ "a", 2, this_object(), "c" }), "b") // returns "abc"
    * 
    * ~~~
    * Together with efun::explode() this can be used as a search-and-replace for strings:
    * 
    * ~~~{.c}
    * implode(explode("a short text", " "), "_") // returns "a_short_text"
    * 
    * ~~~
    * But nowadays you can also use:
    * 
    * ~~~{.c}
    * regreplace("a short text", " ", "_", 1)
    * 
    * ~~~
    * 
    * }
    * 
    * @see efun::explode(), efun::regreplace()
   **/
   string implode(mixed *arr, string del);
}
