#include "core/core.h"

#include <math.h>

f32
m_degreesf(f32 radian)
{
    return radian * (180.0f / M_PI);
}
f64
m_radians(f64 degree)
{
    return degree * (M_PI / 180.0f);
}
f64
m_degrees(f64 radian)
{
    return radian * (180.0f / M_PI);
}
