public class efun {
   /**
    * Parses the given string \p xml as an XML conformant string. The string must have only one root tag, subsequent root tags are ignored.
    * 
    * If the xml string is correct, an array of three elements is returned, where the following indices are defined:
    * 
    * string `XML_TAG_NAME`
    * The name of the XML tag.
    * 
    * mapping `XML_TAG_ATTRIBUTES`
    * All attributes given to the XML tag as a mapping where the key is the attribute name and the value is its string value.
    * 
    * If the xml tag does not contain any attributes, this element is set 0.
    * 
    * mixed * `XML_TAG_CONTENTS`
    * The contents of this xml tag as an array. This array may contain either strings, or arrays of sub-tags again with three elements. (see example)
    * 
    * If the xml tag does not contain anything, the element is set to 0.
    * 
    * If the XML string is not well formed, or there is not enough memory to parse the whole XML structure into the array an error is raised.
    * 
    * The function is available only if the driver is compiled with Iksemel support. In that case, @ref driver_topics_predefined "__XML_DOM__" is defined.
    * 
    * @headerfile <xml.h>
    * 
    * @synopsis{
    * mixed * xml_parse(string xml)
    * }
    * 
    * @usage{
    * Parse a simple self-terminating tag:
    * 
    * ~~~{.c}
    * xml_parse("<abc/>")           // ({ "abc", 0, 0 })
    * 
    * ~~~
    * Parse a self-terminating tag with a property:
    * 
    * ~~~{.c}
    * xml_parse("<abc xyz="cde"/>") // ({ "abc", ([ "xyz" : "cde" ]), 0 })
    * 
    * ~~~
    * Parse a small nested data structure:
    * 
    * ~~~{.c}
    * xml_parse("<book language="common">" +
    *           "    <title>This is the title</title>" +
    *           "    <chapter>This is a chapter</chapter>" +
    *           "    <chapter>We want <b>bold</b> here.</chapter>" +
    *           "</book>");
    * /*
    *    ({ "book"
    *     , ([ "language" : "common" ])
    *     , ({ ({ "title"
    *           , 0
    *           , ({ "This is a title" })
    *          })
    *        , ({ "chapter"
    *           , 0
    *           , ({ "This is a chapter" })
    *          })
    *        , ({ "chapter"
    *           , 0
    *           , ({ "We want "
    *              , ({ "b"
    *                 , 0
    *                 , ({ "bold" })
    *                })
    *              , "here"
    *             })
    *          })
    *       })
    *    })
    * */
    * 
    * ~~~
    * 
    * }
    * 
    * @see efun::xml_generate()
   **/
   mixed * xml_parse(string xml);
}
