+++
title = "Should I Check If A Pointer Is NULL Before Deleting It?"
slug = "should-i-check-if-pointer-is-null-before-deleting-it"
date = 2013-02-11T01:52:00Z
tags = [ "C", "C++", "Clang", "G++", "GCC", "MSVC", "VC++", "Visual C++", "Visual Studio" ]
#template = "post.html"
+++

Most of the time I see some C++ programmers who check if a pointer is NULL before deleting it.

```cpp
if (ptr != NULL) {
    delete ptr;
    ptr = NULL;
}
```

Well, according to *C++03 [ISO/IEC IS 14882:2003] §5.3.5/2* which explicitly states:

{% quote(author="C++ Standard Core Language Defect Reports and Accepted Issues, Revision 82, delete and user-written deallocation function", href="http://www.open-std.org/jtc1/sc22/wg21/docs/cwg_defects.html#348") %}
...if the value of the operand of delete is the null pointer the operation has no effect.
{% end %}

Therefore, deleting a *NULL pointer* has no effect (if the deallocation function is one supplied in the standard library), so it is not necessary to check for a *NULL pointer* before calling delete.

```cpp
delete ptr;
ptr = NULL;
```

- _**Note**: Keep in mind that deleting a __void*__ pointer results in <strike>undefined behavior</strike> whether it's __NULL__ or not._

<!-- more -->
