public class efun {
   /**
    * The given array, mapping or struct \p data is returned as a struct. If a \p template struct is given, the returned struct is of the same type. Without a template, an anonymous struct is returned in case of arrays and mappings and in case of structs \p data is returned unchanged.
    * 
    * If \p data is an array, its elements are assigned in order to the resulting struct. For an anonymous struct, all elements of \p data are assigned, for a templated struct only as many as fit into the struct.
    * 
    * If \p data is a mapping and no template is given, the resulting anonymous struct contains all elements from \p data with a string key; the key name is used as struct member name.
    * 
    * If \p data is a mapping and a template is given, the struct member names are used as keys for lookups in \p data; the found data is assigned to the struct members.
    * 
    * If \p data is a struct and a template is given, a struct of the type of template is created and all members from \p data are copied to the new struct, which exist in both structs. This conversion is only allowed between a struct and one of its base structs or a base struct and one of its children. Otherwise an error is raised.
    * 
    * Neither \p data nor \p template will be changed in this process - the result is a new struct value. The actual value of \p template does not matter, only its type.
    * 
    * Since the returned struct can't be known at compile time, the efun is declared to return 'mixed'.
    * 
    * @synopsis{
    * mixed to_struct(mixed *|mapping data)
    * mixed to_struct(mixed *|mapping data, struct template)
    * mixed to_struct(struct data)
    * mixed to_struct(struct data, struct template)
    * }
    * 
    * @history{
    * introduced (3.3.250)
    * changed (3.3.344) -- added the template argument.
    * changed (3.3.433) -- added the conversion from mappings.
    * changed (3.3.720) -- added the conversion of structs into another struct.
    * }
    * 
    * @see efun::to_array(), efun::to_string(), efun::mkmapping(), @ref driver_syntax_structs "struct"
   **/
   mixed to_struct(struct data, struct template);
}
