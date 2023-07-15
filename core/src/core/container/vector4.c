#include "core/core.h"

#include <math.h>

V4F
v4f(f32 x, f32 y, f32 z, f32 w)
{
    V4F v;
    v.x = x;
    v.y = y;
    v.z = z;
    v.w = w;
    return v;
}

V4F
v4f_add(V4F left, V4F right)
{
    V4F v;
    v.x = left.x + right.x;
    v.y = left.y + right.y;
    v.z = left.z + right.z;
    v.w = left.w + right.w;
    return v;
}

V4F
v4f_sub(V4F left, V4F right)
{
    V4F v;
    v.x = left.x - right.x;
    v.y = left.y - right.y;
    v.z = left.z - right.z;
    v.w = left.w - right.w;
    return v;
}

V4F
v4f_mul(V4F left, V4F right)
{
    V4F v;
    v.x = left.x * right.x;
    v.y = left.y * right.y;
    v.z = left.z * right.z;
    v.w = left.w * right.w;
    return v;
}

V4F
v4f_mulf(V4F left, f32 right)
{
    V4F v;
    v.x = left.x * right;
    v.y = left.y * right;
    v.z = left.z * right;
    v.w = left.w * right;
    return v;
}

V4F
v4f_div(V4F left, V4F right)
{
    V4F v;
    v.x = left.x / right.x;
    v.y = left.y / right.y;
    v.z = left.z / right.z;
    v.w = left.w / right.w;
    return v;
}

V4F
v4f_divf(V4F left, f32 right)
{
    V4F v;
    v.x = left.x / right;
    v.y = left.y / right;
    v.z = left.z / right;
    v.w = left.w / right;
    return v;
}

f32
v4f_dot(V4F left, V4F right)
{
    return (left.x * right.x) + (left.y * right.y) + (left.z * right.z)
           + (left.w * right.w);
}

b32
v4f_eq(V4F left, V4F right)
{
    return left.x == right.x && left.y == right.y && left.z == right.z
           && left.w == right.w;
}

V4F
v4f_norm(V4F v)
{
    return v4f_mulf(v, 1.0f / sqrtf(v4f_dot(v, v)));
}

f32
v4f_sqrt_len(V4F v)
{
    return v4f_dot(v, v);
}

f32
v4f_len(V4F v)
{
    return sqrtf(v4f_sqrt_len(v));
}

V4F
v4f_lerp(V4F left, V4F right, f32 time)
{
    return v4f_add(v4f_mulf(left, 1.0f - time), v4f_mulf(right, time));
}
