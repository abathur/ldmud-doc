public class efun {
   /**
    * Calculate the Hashed Message Authenication Code for \p value based on the digest \p method and the password \p key. Return the HMAC.
    * 
    * \p method is one of the >>TLS_HASH_<< constants defined in tls.h; not all recognized methods may be supported for a given driven:
    * 
    * TLS_HASH_SHA1      (1)
    * TLS_HASH_SHA224    (2)
    * TLS_HASH_SHA256    (3)
    * TLS_HASH_SHA384    (4)
    * TLS_HASH_SHA512    (5)
    * TLS_HASH_MD5       (6)
    * TLS_HASH_RIPEMD160 (7)
    * 
    * If the driver is compiled without OpenSSL or GCrypt support an error is thrown.
    * 
    * @headerfile <tls.h>
    * 
    * @synopsis{
    * string hmac(int method, string key, string value)
    * string hmac(int method, string key, int *  arg)
    * }
    * 
    * @usage{
    * The example below shows how to compute the SHA1 hmac of a string and an array of characters:
    * 
    * ~~~{.c}
    * string s;
    * 
    * s = hmac(TLS_HASH_SHA1, "secret", "Hello");
    * s = hmac(TLS_HASH_SHA1, "secret", ({ 'H', 'e', 'l', 'l', 'o' }) );
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * introduced (3.3.714)
    * }
    * 
    * @see efun::crypt(), efun::md5(), efun::md5_crypt(), efun::sha1(), efun::hmac()
   **/
   string hmac(int method, string key, int *  arg);
}
