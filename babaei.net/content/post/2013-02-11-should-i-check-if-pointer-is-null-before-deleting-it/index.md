+++
title = "Should I Check if a Pointer Is NULL Before Deleting It?"
slug = "should-i-check-if-pointer-is-null-before-deleting-it"
date = 2013-02-11T01:52:00Z
tags = [ "C", "C++", "Clang", "G++", "GCC", "MSVC", "VC++", "Visual C++", "Visual Studio" ]
aliases = [ "/blog/2013/02/11/should-i-check-if-pointer-is-null-before-deleting-it/" ]
+++

Most of the time I see some C++ programmers who check if a pointer is NULL before deleting it.

{{< highlight cpp >}}
if (ptr != NULL) {
    delete ptr;
    ptr = NULL;
}
{{< /highlight >}}

Well, according to *C++03 [ISO/IEC IS 14882:2003] §5.3.5/2* which explicitly states:

{{< blockquote author="C++ Standard Core Language Defect Reports and Accepted Issues, Revision 82" link="http://www.open-std.org/jtc1/sc22/wg21/docs/cwg_defects.html#348" title="delete and user-written deallocation functions" >}}
...if the value of the operand of delete is the null pointer the operation has no effect.
{{< /blockquote >}}

Therefore, deleting a *NULL pointer* has no effect (if the deallocation function is one supplied in the standard library), so it is not necessary to check for a *NULL pointer* before calling delete.

{{< highlight cpp >}}
delete ptr;
ptr = NULL;
{{< /highlight >}}

- _**Note**: Keep in mind that deleting a __void*__ pointer results in <strike>undefined behavior</strike> whether it's __NULL__ or not._

<!--more-->
