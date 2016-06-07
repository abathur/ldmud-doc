public class efun {
   /**
    * @synopsis{
    * string implode(mixed *arr, string del)
    * }
    * 
   **/
   string implode(mixed *arr, string del);
}
Concatenate all strings found in array arr, with the string
del between each element. Only strings are used from the array.

EXAMPLES
function                                        returns
-------------------------------------------------------------------
implode(({ "foo", "bar", "" }), "*")            "foo*bar*"
implode(({ "a", 2, this_object(), "c" }), "b")  "abc"

Together with explode() this can be used as a search and replace
function of strings:
implode(explode("a short text", " "), "_")      "a_short_text"

But nowadays you can also use
   regreplace("a short text", " ", "_", 1)

instead.

   See Also: 
      efun::explode(), efun::regreplace()
