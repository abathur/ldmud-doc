public class efun {
   /**
    * Allocate an array of size elements. The number of elements must be >= 0 and not bigger than a system maximum (usually 1000).
    * 
    * If \p init_value is given, all array elements will be set to this value (if \p init_value is an array or mapping, a shallow copy will be created for each element), otherwise they all will be 0.
    * 
    * In the second form (using an array of sizes instead of one size), the efun will allocate a multidimensional array, that is an array of arrays.
    * 
    * @par obsolete: this function is hardly needed anymore, because arrays can be added by the + operator, and can be constructed and initialized by the `({ })` operator. The functions only use is to construct big empty arrays.
    * 
    * @synopsis{
    * mixed * allocate(int size)
    * mixed * allocate(int size, mixed init_value)
    * mixed * allocate(int *sizes)
    * mixed * allocate(int *sizes, mixed init_value)
    * }
    * 
    * @usage{
    * ~~~{.c}
    * string *buffer;
    * buffer = allocate(50);
    * buffer = allocate(50, "");
    * 
    * buffer = allocate( ({ 2, 3 }) )
    *   --> ({ ({ 0, 0, 0 }), ({ 0, 0, 0 }) })
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * changed (3.2.9) -- added the initialization value and the multi-dimensional allocation.
    * }
    * 
    * @see efun::sizeof()
   **/
   mixed * allocate(int *sizes, mixed init_value);
}
