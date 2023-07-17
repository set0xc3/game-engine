#include "core/core.h"

#include <math.h>

CVector2
v2(f32 x, f32 y)
{
    CVector2 v;
    v.x = x;
    v.y = y;
    return v;
}

CVector2
v2_add(CVector2 left, CVector2 right)
{
    CVector2 v;
    v.x = left.x + right.x;
    v.y = left.y + right.y;
    return v;
}

CVector2
v2_addf(CVector2 left, f32 right)
{
    CVector2 v;
    v.x = left.x + right;
    v.y = left.y + right;
    return v;
}

CVector2
v2_sub(CVector2 left, CVector2 right)
{
    CVector2 v;
    v.x = left.x - right.x;
    v.y = left.y - right.y;
    return v;
}

CVector2
v2_subf(CVector2 left, f32 right)
{
    CVector2 v;
    v.x = left.x - right;
    v.y = left.y - right;
    return v;
}

CVector2
v2_mul(CVector2 left, CVector2 right)
{
    CVector2 v;
    v.x = left.x * right.x;
    v.y = left.y * right.y;
    return v;
}

CVector2
v2_mulf(CVector2 left, f32 right)
{
    CVector2 v;
    v.x = left.x * right;
    v.y = left.y * right;
    return v;
}

CVector2
v2_div(CVector2 left, CVector2 right)
{
    CVector2 v;
    v.x = left.x / right.x;
    v.y = left.y / right.y;
    return v;
}

CVector2
v2_divf(CVector2 left, f32 right)
{
    CVector2 v;
    v.x = left.x / right;
    v.y = left.y / right;
    return v;
}

f32
v2_dot(CVector2 left, CVector2 right)
{
    return (left.x * right.x) + (left.y * right.y);
}

b8
v2_eq(CVector2 left, CVector2 right)
{
    return left.x == right.x && left.y == right.y;
}

CVector2
v2_norm(CVector2 v)
{
    return v2_mulf(v, 1.0f / sqrtf(v2_dot(v, v)));
}

f32
v2_sqrt_len(CVector2 v)
{
    return v2_dot(v, v);
}

f32
v2_len(CVector2 v)
{
    return sqrtf(v2_sqrt_len(v));
}

CVector2
v2_lerp(CVector2 left, CVector2 right, f32 time)
{
    return v2_add(v2_mulf(left, 1.0f - time), v2_mulf(right, time));
}
