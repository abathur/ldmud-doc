The Mud Client Compression Protocol {#driver_topics_mccp}
=========================================================
Information and code taken from the @ref driver_topics_mccp "MCCP" Homepage @subpage driver_http:__www.randomly.org_projects_MCCP_ "http://www.randomly.org/projects/MCCP/"

@ref driver_topics_mccp "MCCP" is implemented as a Telnet option [RFC854, RFC855]. The server and client negotiate the use of @ref driver_topics_mccp "MCCP" as they would any other telnet option. Once agreement has been reached on the use of the option, option subnegotiation is used to determine acceptable compression methods to use, and to indicate the start of a compressed data stream.

If the driver is compiled with @ref driver_topics_mccp "MCCP" Support there is a define @ref driver_topics_predefined "__MCCP__".

The driver currently supports both versions of mccp. If your mud has a @ref driver_hook_no_echo "H_NOECHO" hook you have to find out if the client supports mccp. Without this hook you still have to start neogotiation.

All sub-negotiation is done by efun::start_mccp_compress() and efun::end_mccp_compress() whether you have this hook or not.

@par note: when the client uses compressions all binary_message calls are executed with flag=3. This is because writing to the socket would disturb zlib stream.

mccp-efuns:

- efun::start_mccp_compress() (only needed with @ref driver_hook_no_echo "H_NOECHO")
- efun::end_mccp_compress()   (only needed with @ref driver_hook_no_echo "H_NOECHO")
- efun::query_mccp()
- efun::query_mccp_stats()

Initiating @ref driver_topics_mccp "MCCP" without @ref driver_hook_no_echo "H_NOECHO" hook:

~~~{.c}
if(!query_mccp()){
  binary_message(({ IAC, WILL, TELOPT_COMPRESS2 }),1)
  binary_message(({ IAC, WILL, TELOPT_COMPRESS }),1)
}

~~~
the driver will parse the client's answers and start compression. (The connection might already be compressed, because although the documentation says clients should not negotiate from themselves, zmud e.g. does.)

You can start and stop compression manually by efuns when you are sure client supports compression :)

Initiating @ref driver_topics_mccp "MCCP" compression with @ref driver_hook_no_echo "H_NOECHO" hook:

~~~{.c}
If your mudlib uses the :hook:`H_NOECHO` driver-hook you decided to do
all the negotiation by yourself:

Server Commands
IAC WILL COMPRESS  indicates the sender supports version 1 of the
                   protocol, and is willing to compress data it sends.

IAC WILL COMPRESS2 indicates the sender supports version 2, and is
                   willing to compress data it sends.

IAC WONT COMPRESS  indicates the sender refuses to compress data using
                   version 1.

IAC WONT COMPRESS2 indicates the sender refuses to compress data
                   using version 2.

Client Commands
IAC DO COMPRESS    indicates the sender supports version 1 of the
                   protocol, and is willing to decompress data
                   received.

IAC DO COMPRESS2   indicates the sender supports version 2 or above,
                   and is willing to decompress data received.

IAC DONT COMPRESS  indicates the sender refuses to support version 1.
                   If compression was previously negotiated and is
                   currently being used, the server should terminate
                   compression.

IAC DONT COMPRESS2 indicates the sender refuses to support version 2.
                   If compression was previously negotiated and is
                   currently being used, the server should terminate
                   compression

After you found out whether the client supports mccp or not you can
start compression with start_mccp_compress(TELOPT_COMPRESS2) or
start_mccp_compress(TELOPT_COMPRESS). ( you could start it without
checking but some players would protest :) )

~~~
- author: Bastian Hoyer (@subpage driver_mailto:dafire@ff.mud.de "dafire@ff.mud.de") (some text taken from project page)

@history{
introduced (3.3.447)
backported (3.2.10)
}

@see efun::start_mccp_compress(), efun::end_mccp_compress(), efun::query_mccp(), efun::query_mccp_stats()
