#pragma once

namespace unit {
class Distance {
  public:
    explicit Distance(double cm);
    friend Distance operator+(const Distance &lhs, const Distance &rhs);
    friend Distance operator-(const Distance &lhs, const Distance &rhs);

  private:
    double cm;
};

Distance operator"" _cm(long double cm);
Distance operator"" _dm(long double dm);
Distance operator"" _m(long double m);
Distance operator"" _km(long double km);
} // namespace unit