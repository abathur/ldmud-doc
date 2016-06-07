public class applied {
   /**
    * The H_CREATE_SUPER/_OB/_CLONE hooks define the function or closure to be called when the driver creates a new object. In older drivers this was hardwired to the lfun create(), and a lot of hook implementations still follow this tradition.
    * 
    * This function will be called only once on creation of the object (this is when the object will be loaded or cloned). Inside this function all major initialization can be done. The current user and the previous object are defined but the object has no environment.
    * 
    * @synopsis{
    * void create()
    * }
    * 
    * @usage{
    * Initialize the global variable to hold the one who created/cloned the object:
    * object cloner;
    * void create() {
    *   cloner=this_player();
    * }
    * }
    * 
    * @history{
    * changed (3.2.1) -- the mudlib may be programmed to call other lfuns than create() on an object's creation.
    * }
    * 
    * @see applied::reset(), applied::init(), applied::__INIT(), @ref driver_concepts_native "native"
   **/
   void create();
}
