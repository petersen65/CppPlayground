#include "Distance.h"

unit::Distance::Distance(double cm)
    : cm(cm)
{
}

unit::Distance unit::operator+(const Distance &lhs, const Distance &rhs)
{
    return Distance(lhs.cm + rhs.cm);
}

unit::Distance unit::operator-(const Distance &lhs, const Distance &rhs)
{
    return Distance(lhs.cm - rhs.cm);
}

unit::Distance unit::operator""_cm(long double cm)
{
    return Distance(cm);
}

unit::Distance unit::operator""_dm(long double dm)
{
    return Distance(10 * dm);
}

unit::Distance unit::operator""_m(long double m)
{
    return Distance(100 * m);
}

unit::Distance unit::operator""_km(long double km)
{
    return Distance(100000 * km);
}