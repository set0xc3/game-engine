#include "core/core.h"

#include <math.h>

V3F
v3f(f32 x, f32 y, f32 z)
{
    V3F v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

V3F
v3f_add(V3F left, V3F right)
{
    V3F v;
    v.x = left.x + right.x;
    v.y = left.y + right.y;
    v.z = left.z + right.z;
    return v;
}

V3F
v3f_sub(V3F left, V3F right)
{
    V3F v;
    v.x = left.x - right.x;
    v.y = left.y - right.y;
    v.z = left.z - right.z;
    return v;
}

V3F
v3f_mul(V3F left, V3F right)
{
    V3F v;
    v.x = left.x * right.x;
    v.y = left.y * right.y;
    v.z = left.z * right.z;
    return v;
}

V3F
v3f_mulf(V3F left, f32 right)
{
    V3F v;
    v.x = left.x * right;
    v.y = left.y * right;
    v.z = left.z * right;
    return v;
}

V3F
v3f_div(V3F left, V3F right)
{
    V3F v;
    v.x = left.x / right.x;
    v.y = left.y / right.y;
    v.z = left.z / right.z;
    return v;
}

V3F
v3f_divf(V3F left, f32 right)
{
    V3F v;
    v.x = left.x / right;
    v.y = left.y / right;
    v.z = left.z / right;
    return v;
}

f32
v3f_dot(V3F left, V3F right)
{
    return (left.x * right.x) + (left.y * right.y) + (left.z * right.z);
}

b32
v3f_eq(V3F left, V3F right)
{
    return left.x == right.x && left.y == right.y && left.z == right.z;
}

V3F
v3f_norm(V3F v)
{
    return v3f_mulf(v, 1.0f / sqrtf(v3f_dot(v, v)));
}

f32
v3f_sqrt_len(V3F v)
{
    return v3f_dot(v, v);
}

f32
v3f_len(V3F v)
{
    return sqrtf(v3f_sqrt_len(v));
}

V3F
v3f_lerp(V3F left, V3F right, f32 time)
{
    return v3f_add(v3f_mulf(left, 1.0f - time), v3f_mulf(right, time));
}
