public class efun {
   /**
    * Test if the type of struct \p b is a base of struct \p s (the values of \p b and \p s are irrelevant). Results are:
    * 
    * 0
    * \p b is not a base of \p s, nor is \p b of equal type as \p s (though \p s might be a base of \p b).
    * 
    * 1
    * \p b is a true base of \p s
    * 
    * 2
    * \p b and \p s are the same struct type
    * 
    * @synopsis{
    * int baseof(struct b, struct s)
    * }
    * 
    * @history{
    * introduced (3.3.344)
    * }
    * 
    * @see efun::structp(), @ref driver_syntax_structs "struct"
   **/
   int baseof(struct b, struct s);
}
