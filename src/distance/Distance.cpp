#include "Distance.h"

namespace unit {
// constructors and operators for Distance
Distance::Distance(double cm) : cm{cm} {}
Distance operator+(const Distance &lhs, const Distance &rhs) { return Distance(lhs.cm + rhs.cm); }
Distance operator-(const Distance &lhs, const Distance &rhs) { return Distance(lhs.cm - rhs.cm); }

// user-defined literals for Distance
Distance operator""_cm(long double cm) { return Distance(cm); }
Distance operator""_dm(long double dm) { return Distance(10 * dm); }
Distance operator""_m(long double m) { return Distance(100 * m); }
Distance operator""_km(long double km) { return Distance(100000 * km); }
} // namespace unit