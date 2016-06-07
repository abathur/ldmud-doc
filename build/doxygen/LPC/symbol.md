symbol {#driver_LPC_symbol}
===========================
Identifier names, which in essence are quoted strings. They are used to compute lambda closures, e.g. instead of ({..., 'ident, ... }) you can write declare a 'symbol' variable foo, compute a value for it, and then create the closure as ({ ..., foo, ... })

@see @ref driver_LPC_closures "closures", @ref driver_LPC_types "types"
