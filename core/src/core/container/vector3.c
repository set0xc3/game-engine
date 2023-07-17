#include "core/core.h"

#include <math.h>

CVector3
v3(f32 x, f32 y, f32 z)
{
    CVector3 v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

CVector3
v3_add(CVector3 left, CVector3 right)
{
    CVector3 v;
    v.x = left.x + right.x;
    v.y = left.y + right.y;
    v.z = left.z + right.z;
    return v;
}

CVector3
v3_sub(CVector3 left, CVector3 right)
{
    CVector3 v;
    v.x = left.x - right.x;
    v.y = left.y - right.y;
    v.z = left.z - right.z;
    return v;
}

CVector3
v3_mul(CVector3 left, CVector3 right)
{
    CVector3 v;
    v.x = left.x * right.x;
    v.y = left.y * right.y;
    v.z = left.z * right.z;
    return v;
}

CVector3
v3_mulf(CVector3 left, f32 right)
{
    CVector3 v;
    v.x = left.x * right;
    v.y = left.y * right;
    v.z = left.z * right;
    return v;
}

CVector3
v3_div(CVector3 left, CVector3 right)
{
    CVector3 v;
    v.x = left.x / right.x;
    v.y = left.y / right.y;
    v.z = left.z / right.z;
    return v;
}

CVector3
v3_divf(CVector3 left, f32 right)
{
    CVector3 v;
    v.x = left.x / right;
    v.y = left.y / right;
    v.z = left.z / right;
    return v;
}

f32
v3_dot(CVector3 left, CVector3 right)
{
    return (left.x * right.x) + (left.y * right.y) + (left.z * right.z);
}

b8
v3_eq(CVector3 left, CVector3 right)
{
    return left.x == right.x && left.y == right.y && left.z == right.z;
}

CVector3
v3_norm(CVector3 v)
{
    return v3_mulf(v, 1.0f / sqrtf(v3_dot(v, v)));
}

f32
v3_sqrt_len(CVector3 v)
{
    return v3_dot(v, v);
}

f32
v3_len(CVector3 v)
{
    return sqrtf(v3_sqrt_len(v));
}

CVector3
v3_lerp(CVector3 left, CVector3 right, f32 time)
{
    return v3_add(v3_mulf(left, 1.0f - time), v3_mulf(right, time));
}
