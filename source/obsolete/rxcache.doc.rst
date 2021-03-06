.. topic:: regular expression cache
  :name: rxcache

  The rxcache acts as a wrapper around the regcomp() function
  in the regexp module. It keeps track of the recently compiled
  regular expression and stores both the expression string and
  regexp's internal representation. If an expression is found
  among the stored ones, the rxcache returns the stored internal
  representation compiled earlier.

  The interface is through the function regcomp_cache() which
  takes the same parameters as regcomp(). However, since the
  compiled expression is stored and managed by rxcache, the
  caller of regcomp_cache() must not deallocate the compiled
  expression after use.

  The expressions are stored in a fixed size table, with entries
  indexed by a hash over the pattern string. The table holds
  RXCACHE_TABLE entries, and every entry can hold RXCACHE_CHAIN
  expressions. Upon a hash collision, one of the stored expressions
  is removed (and deallocated) using a round-robin selection.
  This behaviour may not be optimal, but on the other hand
  eventually deallocates expressions which are no longer used.
  The two RXCACHE_ values are defined in config.h.

  Initial tests showed an acceleration of the regexp _setup_
  phase by factor 4. However, since the actual matching is as
  fast as before, the net savings will be lower.

  To install the rxcache, apply the diff file (use parameter
  '-p1' with patch) and reconfigure and recompile the driver.

  .. note:: Lars Duening; 17. Apr 1998
    Written 1998 by Lars Duening.
    Share and Enjoy!@

  :history 3.2 changed: Fully integrated into the driver
