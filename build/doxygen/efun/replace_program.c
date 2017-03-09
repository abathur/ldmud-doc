public class efun {
   /**
    * Substitutes a program with the inherited program \p program. If the object inherits only one program, the argument may be omitted and the efun will automatically select the one inherited program.
    * 
    * This efun is useful if you consider the performance and memory consumption of the driver. A program which doesn't need any additional variables and functions (except during creation) can call efun::replace_program() to increase the function-cache hit-rate of the driver which decreases with the number of programs in the system.
    * 
    * @par warning: Replacing an object's program removes all of its shadows.
    * 
    * Rooms are a good example for the application of this function, as many rooms just consist of an inherit statement and the configure function. Any object can call efun::replace_program() but looses all extra variables and functions which are not defined by the inherited program.
    * 
    * It is not possible to replace the program of an object after (lambda) closures have been bound to it. It is of course possible to first replace the program and then bind lambda closures to it.
    * 
    * The program replacement does not take place with the call to the efun, but is merely scheduled to be carried out at the end of the backend cycle. This may cause closures to have references to then vanished lfuns of the object. This poses no problem as long as these references are never executed after they became invalid.
    * 
    * @par limit: If the replacement program contains virtually inherited variables, it must be the first inherited program. Without this restriction, the wrong variables would survive the replacement process.
    * 
    * @synopsis{
    * void replace_program()
    * void replace_program(string program)
    * }
    * 
    * @history{
    * changed (3.2@166) -- removes shadows from the object
    * changed (3.2.9) -- allowed to omit the argument if only one inherit exists.
    * }
    * 
   **/
   void replace_program(string program);
}
