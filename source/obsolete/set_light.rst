.. efun:: int set_light(int n)
  :optional:

  .. todo:: not clear what status should be indicated here; deprecated? removed? just optional? obsolete?

  An object is by default dark. It can be set to not dark by
  calling set_light(1). The environment will then also get this
  light. The returned value is the total number of lights in
  this room. So if you call set_light(0) it will return the
  light level of the current object.

  Note that the value of the argument is added to the light of
  the current object.

  .. subtopic:: BUGS

    This handling of light by the parser is inappropriate for most
    purposes: If you put a burning candle into a safe, the safe
    will start to emit light.
