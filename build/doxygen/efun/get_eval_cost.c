public class efun {
   /**
    * Returns the remaining evaluation cost the current execution (the current command) may use up.
    * 
    * It starts at a driver given high value and is reduced with each executed statement.
    * 
    * @synopsis{
    * int get_eval_cost()
    * }
    * 
    * @history{
    * changed (3.2.6) -- the initial value was made available as macro.
    * }
    * 
    * @see efun::rusage(), efun::command(), efun::query_limits()
   **/
   int get_eval_cost();
}
