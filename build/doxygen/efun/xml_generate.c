public class efun {
   /**
    * Converts the given <xml> array into an XML conformant string, if
    * possible. The <xml> argument array must have the following structure:
    * 
    * It must contain tag arrays of three elements, with the following
    * indices:
    * 
    * string XML_TAG_NAME
    *    The name of the XML tag.
    *    
    * mapping XML_TAG_ATTRIBUTES
    *    All attributes given to the XML tag as a mapping where the key
    *    is the attribute name and the value is its string value.
    *    
    *    If the xml tag does not contain any attributes, this element
    *    is set to 0:
    *    
    * mixed * XML_TAG_CONTENTS
    *    The contents of this xml tag as an array. This array may
    *    contain either strings, or arrays of sub-tags again with
    *    three elements. (see example)
    *    
    *    If the xml tag does not contain anything, the element is
    *    set to 0.
    *    
    * In case the parameter does not follow these rules, errors are raised.
    * The method returns a valid XML string otherwise.
    * 
    * The function is available only if the driver is compiled with Iksemel
    * support. In that case, __XML_DOM__ is defined.
    * 
    * @headerfile <xml.h>
    * 
    * @synopsis{
    * string xml_generate(mixed *xml)
    * }
    * 
   **/
   string xml_generate(mixed *xml);
}
EXAMPLES
   xml_generate(({ "abc", 0, 0 })) -> "<abc/>"
   xml_generate(({ "abc", ([ "xyz" : "cde" ]), 0 })) -> "<abc xyz="cde"/>"

   mixed >>*<<xml = ({ "book"
         , ([ "language" : "common" ])
         , ({ ({ "title"

                     , 0
                     , ({ "This is a title" })

                  })

               , ({ "chapter"
                     , 0
                     , ({ "This is a chapter" })

                  })

               , ({ "chapter"
                     , 0
                     , ({ "We want "

                           , ({ "b"
                                 , 0
                                 , ({ "bold" })

                              })

                           , "here"

                        })

                  })

            })

      })

   xml_generate(xml)
      -> "<book language="common"><title>This is the title</title>"
         "<chapter>This is a chapter</chapter><chapter>We want "
         "<b>bold</b> here.</chapter></book>"
