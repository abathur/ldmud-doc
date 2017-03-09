InterMUD Message Protocol {#driver_topics_imp}
==============================================
This document describes IMP, the intermud message protocol, also known as Intermud-1.

Imp messages are exchanged between muds using UDP (unreliable datagram protocol) packets. Each mud provides a connection endpoint which is given by the ip host address and the UDP port number. Muds may then send messages to this port by using `send_imp`. The applied function receive_imp will be called by the driver in the master object if a imp message arrives at the mud's UDP port.

Imp message packets have the following format: `<em>password</em>@<em>objectname</em>@<em>functionname</em>[[@<em>argument</em>]...]`

<em>password</em>
The connection password to verify incoming imp packets. It is encoded using efun::crypt() and compared to the stored password. Each mud participating in the imp network has a secret password which is encoded by the admin and distributed to remote muds with which the mud should have direct connection. Encryted passwords may also propagated to other muds over already secure channels.

<em>objectname</em>
A logical name which is not to be confused with mudlib object filenames. It is used by receive_msg in the master object to route the message to another object by associating the logical object name with a real mudlib file name. A good idea would be to reserve a special directory for imp objects, e.g. `/secure/net/<em>objectname</em>`.

<em>functionname</em>
The function which is called by the master object in the object described by <em>objectname</em>.

<em>argument</em>
are additional arguments which are handed to the function <em>functionname</em>. The exact definition of functions and arguments are left to the imp applications.

@par misleading: The above is only partially correct nowadays. Recently a package name "inetd" was published, that is based on the IMP mechanism in the driver (efun::send_udp() and master::receive_udp()), but it uses a different message format. That package seems to enjoy much publicity and is installed in a number of muds. For details look into the inetd description.Another method of inter mud connection is the Mudlink package, which uses a normal user connection that is connected to a special user object, and an auxiliary process that does the connection to other muds.

Author

- Deepthought

Last Updated

- Deepthought, 10-Nov-92
- Pepel, 18-Nov-93

@see efun::send_udp(), master::receive_udp()
