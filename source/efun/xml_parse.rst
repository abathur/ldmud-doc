.. efun:: mixed * xml_parse(string xml)
  :optional:
  :experimental:
  :include: <xml.h>

  Parses the given string :arg:`xml` as an XML conformant string. The string must have only one root tag, subsequent root tags are ignored.

  If the xml string is correct, an array of three elements is returned, where the following indices are defined:

  .. todo:: the below section (and the matching one in xml_generate) probably needs to be recast. It's trying to use the defines in xml.h to tell us that array index 0 will be a string containing the tagname, index 1 will be a mapping with its attributes, and 2 will be a nested mixed * array of parsed subtags. One possibility is that the :macro: role is updated to actually pull in the value?

  string :macro:`XML_TAG_NAME`
    The name of the XML tag.

  mapping :macro:`XML_TAG_ATTRIBUTES`
    All attributes given to the XML tag as a mapping where the key is the attribute name and the value is its string value.

    If the xml tag does not contain any attributes, this element is set 0.

  mixed * :macro:`XML_TAG_CONTENTS`
    The contents of this xml tag as an array. This array may contain either strings, or arrays of sub-tags again with three elements. (see example)

    If the xml tag does not contain anything, the element is set to 0.

  If the XML string is not well formed, or there is not enough memory to parse the whole XML structure into the array an error is raised.

  The function is available only if the driver is compiled with Iksemel support. In that case, :macro:`__XML_DOM__` is defined.

  .. usage::

    Parse a simple self-terminating tag::

      xml_parse("<abc/>")           // ({ "abc", 0, 0 })

    Parse a self-terminating tag with a property::

      xml_parse("<abc xyz="cde"/>") // ({ "abc", ([ "xyz" : "cde" ]), 0 })

    Parse a small nested data structure::

      xml_parse("<book language="common">" +
                "    <title>This is the title</title>" +
                "    <chapter>This is a chapter</chapter>" +
                "    <chapter>We want <b>bold</b> here.</chapter>" +
                "</book>");
      /*
         ({ "book"
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
      */

  :version 3.3.718 introduced:

  .. seealso:: :efun:`xml_generate`
