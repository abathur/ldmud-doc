public class efun {
   /**
    * This efun is needed to create copies of mappings instead of
    * just passing a reference, like adding/subtraction from a
    * mapping do.
    * 
    * @synopsis{
    * mapping copy_mapping(mapping)
    * }
    * 
    * @history{
    * removed (3.3) -- superseded by copy()
    * }
    * 
    * @see @ref driver_LPC_mappings "mappings", efun::copy()
   **/
   mapping copy_mapping(mapping);
}
