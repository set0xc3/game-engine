#include "core/core.h"

CString8
str8(const char *c)
{
    CString8 result;
    result.str = (uint8_t *)c;
    result.size = strlen(c);
    return result;
}

char *
str8_c(const CString8 string)
{
    char *resutl = (char *)string.str;
    return resutl;
}

b8
str8_eq(const CString8 left, const CString8 right)
{
    bool result = !strcmp(str8_c(left), str8_c(right));
    return result;
}
