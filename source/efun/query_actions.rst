.. efun:: mixed * query_actions(object ob, mixed mask_or_verb)
  :include: <commands.h>
    <sent.h>

  Takes either an object or a filename as first argument and a bitmask (int) or string as a second argument. If the second argument is a string, the function  returns an array containing information (see below) on the verb or zero if the living object "ob" cannot use the verb. If the second argument is a bitmask, the function returns a flat array containing information on all verbs added to ob. The second argument is optional (default is :macro:`QA_VERB`).

      :macro:`QA_VERB`       ( 1):  the verb
      :macro:`QA_TYPE`       ( 2):  type
      :macro:`QA_SHORT_VERB` ( 4):  short_verb
      :macro:`QA_OBJECT`     ( 8):  object
      :macro:`QA_FUNCTION`   (16): function

  .. todo:: doesn't the above imply that we should list at least two function ignatures/forms?

  "type" is one of the values defined in <sent.h> (which is provided with the parser source).

  :macro:`SENT_PLAIN`        added with add_action (fun, cmd);
  :macro:`SENT_SHORT_VERB`   added with add_action (fun, cmd, :macro:`AA_SHORT`);
  :macro:`SENT_NO_SPACE`     added with add_action (fun, :macro:`AA_NOSPACE`);
  :macro:`SENT_MARKER`       internal, won't be in the returned array negative value: The verb given by the player has to match only the leading *-value* characters of the action's verb.

  .. seealso:: :efun:`add_action`, :applied:`init`
