There are some differences between 3.3 and 3.5 concerning compilation and
installation you should keep in mind while updating. This is (hopefully) a
complete list of them:

- PCRE
  In 3.3 the driver had a built-in PCRE package and optionally you could usethe system supplied libpcre. In 3.5 the built-in package was removed. If youwant to use PCREs in your mud, you must have a libpcre installed on yoursystem.
- ptmalloc
  The ptmalloc memory allocator was removed. Please use one of the others. Formore information, please see Issue #552 in our bug tracker.
