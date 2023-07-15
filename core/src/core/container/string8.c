#include "core/core.h"

String8
str8(const char *c)
{
    String8 result;
    result.str = (uint8_t *)c;
    result.size = strlen(c);
    return result;
}

char *
str8_c(const String8 string)
{
    char *resutl = (char *)string.str;
    return resutl;
}

b8
str8_eq(const String8 left, const String8 right)
{
    bool result = !strcmp(str8_c(left), str8_c(right));
    return result;
}
