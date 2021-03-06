Intermud communication {#driver_topics_intermud}
================================================
There are several intermud protocols which define how (players on) different muds can communicate with each other. The protocols are in general not muddriver or mudlib dependant, though the number of implementations is limited.

This text is about the rather old widely spread 'Zebedee Intermud', which is also called 'Intermud 2' although it differs quite a lot from the real Intermud 2 protocol.

Full information on the newer Intermud 3 could be found on the web at @subpage driver_http:__www.imaginary.com_protocols_intermud3.html "http://www.imaginary.com/protocols/intermud3.html" so there is no discussion here - the following is just about Zebedee Intermud (aka Intermud 2).

Zebedee Intermud communication is handled by the /secure/inetd object, originally written by Nostradamus for Zebedee with some extensions that are discussed in >>:concept:`inetd`<<. How the data is actually sent across the network is described in intermud.basic(C).

## Services #

Note that the fields "NAME" and "UDP_PORT" should be present in every message. Very common are the fields "ID" (used whenever an reply is expected) and "SND" (the sender: he should receive the reply). These fields will not be mentioned in the list below.

Request types are listed on the leftmost row (e.g. "REQ=channel"), associated header are listed indented.

"channel"
The channel-request is used for sending a message on any channel. The "CMD" field is optional and may be omitted for normal messages. Note that you should not send an history or list request to _all_ known muds!

"CHANNEL"
   The channel on which a message is send (the standard channels are "intermud", "intercode", "interadm", "d-chat", "d-code" and "d-adm"; on the d-channels German is spoken)
   
"DATA"
   The message to be send (not used with history/list request)
   
"CMD"
   The body of this header may be:
   ""        for normal intermud messages,
   "emote"   if the message is an emote/gemote,
   "history" for an history request: the last 20 lines of this channel will be shown.
   "list"    to list all remote users listening to this channel
   
"EMOTE"     (optional)
   The body is 1 if the message is an emote.
   The body is 2 if the message is a gemote.
   
"finger"
Retreive information about a player or creator on a remote mud.

"DATA"
   The player of whom information is requested
   
"locate"
Check whether a certain player is logged on at a remote mud. This request is usually send to all known muds at the same time.

"user"
   Name of the person who requests the information. This is used by the sending mud only and has to be included in the reply.
   
"vbs"
   The verbose option has only two pre-defined values:
   
      1: 
         Even report when the result was negative
         
      2: 
         Don't do timeouts, but keep waiting
         
   This is used by the sending mud only and has to be included in the reply.
   
   "fnd"
      The found option is only used in the reply and it's value is either 1 (success) or 0 (failure). The absence of a found parameter indicates failure as well.
      
   "DATA"
      The player to find.
      
"man"
Retreive a manual page from a remote mud. Many muds don't support this feature...

"DATA"
   The name of the requested manual page
   
"mail"
An extension to the standard protocol, by @subpage driver_mailto:Alvin@Sushi "Alvin@Sushi". This is used to send mails from one mud to another.

"udpm_status"
   This field should only be used in the reply and indicates how mail is handled. Currently there are four pre-defined values for the status field:
   0 time out
   1 delivered ok
   2 unknown player
   3 in spool (will be delivered later)
   
"udpm_writer"
   Name of the person who wrote this mail
   
"udpm_spool_name"
   Should be returned as sent, this value is used to remove the mail from the spool directory after it has been delivered (or refused)
   
"udpm_subject"
   Subject of the mail message
   
"DATA"
   The body of the mail (the actual message)
   
"ping"
A ping request has only the standard fields, the reply is usually a short string like " is alive."

"query"
Get standard information about another mud. This is the only command of which the reply may not include a load of rubbish, but should only hold the requested information, so that it can be parsed by the server.

"DATA"
   The following queries are pretty much standard:
   "commands" List all commands that are supported by the inetd
   "email"    The email-address of the mud administrator(s)
   "hosts"    A listing of all hosts in a special format [t.b.d.]
   "inetd"    The version number of the inetd used
   "list"     The list of all items which can be queried
   "info"     A short human-readable string with practically
   
      "query" information
      
   "mud_port" The portnumber that players connect to on login
   "time"     The local time for this mud
   "users"    A list of the people that are active in this mud
   "version"  The version of the mud-driver (and library)
   "www"      The URL of the mud's web page (e.g.
   
      @subpage driver_http:__mud.stack.nl_ "http://mud.stack.nl/")
      
"reply"
This request method is used for _all_ replies.

"DATA"
   A human-readable string, containing the reply to a given query
   
"RCPNT"
   The same name as in the "SND" field or the query; Usually this is the name of the player who initiated the query
   
"QUERY"
   This field is only used in a response to a "query" request and should be equal to the "DATA" field of that request
   
"vbs"
   This field is only used in a response to a "locate" request and should be equal to the "vbs" field of that request
   
"user"
   This field is only used in a response to a "locate" request and should be equal to the "user" field of that request
   
"fnd"
   This field is only used in a response to a "locate" request and should be 1 if the player was located and 0 otherwise
   
"tell"
Say something to a player on another mud.

"RCPNT"
   Name of the player to whom you are talking
   
"DATA"
   Whatever you wish to say to this person
   
Optional emote-tos are handles are also handled as tells, so muds without emote-to support display them as reasonable readable tell message.

"RCPNT"
   Name of the player to whom you are talking
   
"METHOD"
   The body of this header may be:
   "emote"   if the message is an emote
   "gemote"  if the message is a genitiv emote
   
"DATA"
   The text to be emoted prepended with "*" and appended with "* ". If you display the emote you have to cut the stars off. Muds that do not process emote-tos display the emote as tell message with the stars as indication of the message's emote meaning.
   
"who"
List the people that are active on a remote mud. The anwer usually contains some active information about the players, like titles, levels or age.

"DATA"
   Not supported by many muds. Introduced August 1997. Additional switch(es) (blanc separated) that change the appearence of the resulting list. The switches normally resemble the switches used inside of that mud for the 'who' command.  Typical values include:
   "short" "s" "-short" "-s" "kurz":
   
      Return a concise listing.
      
   "alpha" "a" "alphabetisch" "-alpha" "-a"
      Sort the players alphabetically.
      
Author

Information taken from Outerspaces documentation to be found
on @subpage driver_http:__mud.stack.nl_intermud_ "http://mud.stack.nl/intermud/"

@see 
