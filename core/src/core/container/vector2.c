#include "core/core.h"

#include <math.h>

V2F
v2f(f32 x, f32 y)
{
    V2F v;
    v.x = x;
    v.y = y;
    return v;
}

V2F
v2f_add(V2F left, V2F right)
{
    V2F v;
    v.x = left.x + right.x;
    v.y = left.y + right.y;
    return v;
}

V2F
v2f_addf(V2F left, f32 right)
{
    V2F v;
    v.x = left.x + right;
    v.y = left.y + right;
    return v;
}

V2F
v2f_sub(V2F left, V2F right)
{
    V2F v;
    v.x = left.x - right.x;
    v.y = left.y - right.y;
    return v;
}

V2F
v2f_subf(V2F left, f32 right)
{
    V2F v;
    v.x = left.x - right;
    v.y = left.y - right;
    return v;
}

V2F
v2f_mul(V2F left, V2F right)
{
    V2F v;
    v.x = left.x * right.x;
    v.y = left.y * right.y;
    return v;
}

V2F
v2f_mulf(V2F left, f32 right)
{
    V2F v;
    v.x = left.x * right;
    v.y = left.y * right;
    return v;
}

V2F
v2f_div(V2F left, V2F right)
{
    V2F v;
    v.x = left.x / right.x;
    v.y = left.y / right.y;
    return v;
}

V2F
v2f_divf(V2F left, f32 right)
{
    V2F v;
    v.x = left.x / right;
    v.y = left.y / right;
    return v;
}

f32
v2f_dot(V2F left, V2F right)
{
    return (left.x * right.x) + (left.y * right.y);
}

b32
v2f_eq(V2F left, V2F right)
{
    return left.x == right.x && left.y == right.y;
}

V2F
v2f_norm(V2F v)
{
    return v2f_mulf(v, 1.0f / sqrtf(v2f_dot(v, v)));
}

f32
v2f_sqrt_len(V2F v)
{
    return v2f_dot(v, v);
}

f32
v2f_len(V2F v)
{
    return sqrtf(v2f_sqrt_len(v));
}

V2F
v2f_lerp(V2F left, V2F right, f32 time)
{
    return v2f_add(v2f_mulf(left, 1.0f - time), v2f_mulf(right, time));
}
