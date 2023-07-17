#include "core/core.h"

CString8
str8(const char *c)
{
    CString8 result;
    result.str  = (u8 *)c;
    result.size = strlen(c);
    return result;
}

b8
str8_eq(const CString8 left, const CString8 right)
{
    b8 result = !strcmp(str8_c(left), str8_c(right));
    return result;
}
