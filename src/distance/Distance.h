#pragma once

namespace unit {
  // declaration of the Distance class that represents a distance in centimeters
class Distance final {
  public:
    explicit Distance(double cm);

    friend Distance operator+(const Distance &lhs, const Distance &rhs);
    friend Distance operator-(const Distance &lhs, const Distance &rhs);

  private:
    double cm;
};

// operator overload declarations for class Distance
Distance operator+(const Distance &lhs, const Distance &rhs);
Distance operator-(const Distance &lhs, const Distance &rhs);

// declaration of user-defined literals for class Distance
Distance operator"" _cm(long double cm);
Distance operator"" _dm(long double dm);
Distance operator"" _m(long double m);
Distance operator"" _km(long double km);
} // namespace unit