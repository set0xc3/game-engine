#include "core/core.h"

#include <math.h>

CVector4
v4(f32 x, f32 y, f32 z, f32 w)
{
    CVector4 v;
    v.x = x;
    v.y = y;
    v.z = z;
    v.w = w;
    return v;
}

CVector4
v4_add(CVector4 left, CVector4 right)
{
    CVector4 v;
    v.x = left.x + right.x;
    v.y = left.y + right.y;
    v.z = left.z + right.z;
    v.w = left.w + right.w;
    return v;
}

CVector4
v4_sub(CVector4 left, CVector4 right)
{
    CVector4 v;
    v.x = left.x - right.x;
    v.y = left.y - right.y;
    v.z = left.z - right.z;
    v.w = left.w - right.w;
    return v;
}

CVector4
v4_mul(CVector4 left, CVector4 right)
{
    CVector4 v;
    v.x = left.x * right.x;
    v.y = left.y * right.y;
    v.z = left.z * right.z;
    v.w = left.w * right.w;
    return v;
}

CVector4
v4_mulf(CVector4 left, f32 right)
{
    CVector4 v;
    v.x = left.x * right;
    v.y = left.y * right;
    v.z = left.z * right;
    v.w = left.w * right;
    return v;
}

CVector4
v4_div(CVector4 left, CVector4 right)
{
    CVector4 v;
    v.x = left.x / right.x;
    v.y = left.y / right.y;
    v.z = left.z / right.z;
    v.w = left.w / right.w;
    return v;
}

CVector4
v4_divf(CVector4 left, f32 right)
{
    CVector4 v;
    v.x = left.x / right;
    v.y = left.y / right;
    v.z = left.z / right;
    v.w = left.w / right;
    return v;
}

f32
v4_dot(CVector4 left, CVector4 right)
{
    return (left.x * right.x) + (left.y * right.y) + (left.z * right.z)
           + (left.w * right.w);
}

b32
v4_eq(CVector4 left, CVector4 right)
{
    return left.x == right.x && left.y == right.y && left.z == right.z
           && left.w == right.w;
}

CVector4
v4_norm(CVector4 v)
{
    return v4_mulf(v, 1.0f / sqrtf(v4_dot(v, v)));
}

f32
v4_sqrt_len(CVector4 v)
{
    return v4_dot(v, v);
}

f32
v4_len(CVector4 v)
{
    return sqrtf(v4_sqrt_len(v));
}

CVector4
v4_lerp(CVector4 left, CVector4 right, f32 time)
{
    return v4_add(v4_mulf(left, 1.0f - time), v4_mulf(right, time));
}
