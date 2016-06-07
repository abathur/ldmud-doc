public class efun {
   /**
    * Calculate the Hashed Message Authenication Code for <arg> based
    * on the digest <method> and the password <key>. Return the HMAC.
    * 
    * <method> is one of the >>TLS_HASH_<< constants defined in tls.h; not
    * all recognized methods may be supported for a given driven:
    * 
    * TLS_HASH_SHA1      (1)
    * TLS_HASH_SHA224    (2)
    * TLS_HASH_SHA256    (3)
    * TLS_HASH_SHA384    (4)
    * TLS_HASH_SHA512    (5)
    * TLS_HASH_MD5       (6)
    * TLS_HASH_RIPEMD160 (7)
    * 
    * If the driver is compiled without OpenSSL or GCrypt support
    * an error is thrown.
    * 
    * @headerfile <tls.h>
    * 
    * @synopsis{
    * string hmac(int method, string key, string arg)
    * string hmac(int method, string key, int *  arg)
    * }
    * 
    * @usage{
    * string s;
    * s = hmac(TLS_HASH_SHA1, "secret", "Hello");
    * s = hmac(TLS_HASH_SHA1, "secret", ({ 'H', 'e', 'l', 'l', 'o' }) )
    * }
    * 
   **/
   string hmac(int method, string key, int *  arg);
}
