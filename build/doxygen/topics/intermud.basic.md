intermud.basic {#driver_topics_intermud.basic}
==============================================
Here is how intermud data is sent across the internet - specific for Zebedee Intermud (aka Intermud 2).

## ADVANCED PROTOCOL #

This file was originally written as a brief outline of the intermud protocol for use by developers interested in incorperating similar, compatible intermud protocols into their own mud systems. It is included here as it provides a much more detailed description of the intermud protocol than that provided by the original PROTOCOL file, and hence may be of use to LpMud developers.

## PACKET PROTOCOL / FORMAT #

All information is transferred as a string via a UDP port (each mud has 1 send and 1 receive port). This kindof transfer is inherently unreliable, but it's fast and doesn't use up file descriptors. The format of the strings (packets) is as follows:

header1:body1|headerN:bodyN|DATA:body-data

In other words, a header name, followed by a : and then the data associated with this header. Each header/body pair is separated by the | character. This means that headers and their body cannot contain the | character. You should check for this in outgoing packets to aviod decoding errors at the recieving end. The exception to this is the DATA field. If it is present, it is ALWAYS positioned at the end of the packet. Once a DATA header is found, everything following it is interpreted as the body of the DATA field. This means it can contain special characters without error and it is used to carry the main body or data of all packets.

By convention, predefined system fields will use capital letters for field headers and custom headers used by specific applications will use lowercase names to avoid clashes. The defined system fields are generally refered to by a set of macros which are defined in a common header file for clarity.

There is one exception to this header format; If the data is too large to be transmitted in one single packet, it will be split into packets of convenient size, each with a special unique packet header to enable them to be reassembled at the receiving end. These headers are of the format:

~~~{.c}
PKT:mudname:packet-id:packet-number/total-packets|rest-of-packet

~~~
In this case, the mudname and packet-id combine to form a unique id for the packet. The packet-number and total-packets information is used to determine when all buffered packets have been received. The rest-of-packet part is not parsed, but is stored while the receiver awaits the other parts of the packet. When/if all parts have been received they are concatenated and decoded as a normal packet.

## PACKET ENCODING / DECODING #

Only 2 generic data types are fully suported within the inetd code itself (namely strings and integers), though others can easily be used by converting them to one of the supported data types before transfer and converting back again in receipt. The LpMud "object" data type is converted to a string automatically by the inetd on encoding, but no such conversion is carried out on decoding.

On encoding integers are simply converted to a corresponding string. Strings are left untouched as long as there is no ambiguity as to wether they should be decoded as a string or an integer. In this case of ambiguity, the string is prepended with a $ character. If the first character of a string is the $ character, it is escaped by prepending another $ character. On decoding, any string with a $ as its first character will have it removed and will then be treated as a string. Any remaining strings that can be converted to an integer and then back to a string with no loss of information are considered to be integers. Any remaining strings are treated as such and are left unaltered.

## DEFINED SYSTEM HEADERS #

"RCPNT" (RECIPIENT)
The body of this field should contiain the recipient the message is to be sent to if applicable.

"REQ" (REQUEST)
The name of the intermud request that is being made of the receiving mud. Standard requests that should be supported by all systems are "ping" (PING), "query" (QUERY), and "reply" (REPLY). The PING request is used to determine wether or not a mud is active. The QUERY request is used to query a remote mud for information about itself (look at the udp/query module for details of what information can be requested). The REPLY request is special in that it is the request name used for all replies made to by mud B to an initial request made by a mud A. It is mud A's responsibility to keep track of the original request type so that the reply can be handled appropriately.

"SND" (SENDER)
The name of the person or object which sent the request or to whom replies should be directed. This is essential if a reply is expected.

"DATA" (DATA)
This field should contain the main body of any packet. It is the only field that can contain special delimiting characters without error.

The following headers are used internally by the inetd and should not be used by external objects:
"HST" (HOST)

The IP address of the host from which a request was received. This is set by the receiving mud and is not contained in outgoing packets.

"ID" (ID)
The packet id. This field is simply an integer which is set by the sending inetd. The number is incremented each time a packet is sent (zero is never used). This field is only needed if a reply is expected. REPLY packets _must_ include the original request id. This is _not_ done by the inetd.

"NAME" (NAME)
The name of the local mud. Used for security checking and to update host list information.

"PKT" (PACKET)
A special header reserved for packets which have been split. See PACKET PROTOCOL / FORMAT.

"UDP" (UDP_PORT)
The UDP port the local mud is receiving on. Used for security checking and updating host list information.

"SYS" (SYSTEM)
Contains special system flags. The only system flag used at present is TIME_OUT. This is included in packets returned due to an expected reply timing out to differentiate it from an actual reply.

## UDP REQUESTS / MODULES #

The following are standard request types that must be supported by all systems:
"ping" (PING)

This module should return a REPLY packet that contains the original requests ID in it's ID field and the SENDER in it's RECIPIENT field. It should also include an appropriate string in the DATA field, eg. "Mud-Name is alive.n"

"query" (QUERY)
This module expects the type of query requested to appear in the recieved DATA field. It should return a REPLY packet containing the original ID in the ID field, the SENDER in it's RECIPIENT field, and the query type in a QUERY field. The DATA field should contain the information requested.

For details of how other intermud requests operate, look at the relevant module code.

AUTHOR:

~~~{.c}
Information taken from Outerspaces documentation to be found on http://mud.stack.nl/intermud/

~~~

@see 
