#include "rational.h"
#include <iostream>
#include <cmath>
#include <numeric>

Rational::Rational() : p_(0), q_(1) {
}
Rational::Rational(int p) : p_(p), q_(1) {
}
Rational::Rational(int p, int q) : p_(p), q_(q) {
  MakeRational();
}

void Rational::MakeRational() {
  if (q_ == 0) {
    throw RationalDivisionByZero{};
  }
  if (q_ < 0) {
    p_ = -p_;
    q_ = -q_;
  }
  int gcd = std::gcd(p_, q_);
  p_ = p_ / gcd;
  q_ = q_ / gcd;
}

int Rational::GetNumerator() const {
  return p_;
}

int Rational::GetDenominator() const {
  return q_;
}

void Rational::SetNumerator(int x) {
  p_ = x;
  MakeRational();
}

void Rational::SetDenominator(int y) {
  q_ = y;
  MakeRational();
}

Rational& operator++(Rational& rat) {
  int numerator = rat.GetNumerator();
  int denominator = rat.GetDenominator();
  rat.SetNumerator(numerator + denominator);
  rat.MakeRational();
  return rat;
}

Rational& operator--(Rational& rat) {
  int numerator = rat.GetNumerator();
  int denominator = rat.GetDenominator();
  rat.SetNumerator(numerator - denominator);
  rat.MakeRational();
  return rat;
}

Rational operator++(Rational& rat, int) {
  Rational temp = rat;
  int numerator = rat.GetNumerator();
  int denominator = rat.GetDenominator();
  rat.SetNumerator(numerator + denominator);
  return temp;
}

Rational operator--(Rational& rat, int) {
  Rational temp = rat;
  int numerator = rat.GetNumerator();
  int denominator = rat.GetDenominator();
  rat.SetNumerator(numerator - denominator);
  return temp;
}

Rational& operator+=(Rational& rat1, const Rational& rat2) {
  Rational& temp = rat1;
  temp = temp + rat2;
  return temp;
}

Rational& operator-=(Rational& rat1, const Rational& rat2) {
  Rational& temp = rat1;
  temp = temp - rat2;
  return temp;
}

Rational& operator*=(Rational& rat1, const Rational& rat2) {
  Rational& temp = rat1;
  temp = temp * rat2;
  return temp;
}

Rational& operator/=(Rational& rat1, const Rational& rat2) {
  Rational& temp = rat1;
  temp = temp / rat2;
  return temp;
}

Rational operator+(const Rational& rat) {
  int p = rat.GetNumerator();
  int q = rat.GetDenominator();
  return {p, q};
}

Rational operator-(const Rational& rat) {
  int p = -rat.GetNumerator();
  int q = rat.GetDenominator();
  return {p, q};
}

Rational operator+(const Rational& rat1, const Rational& rat2) {
  int p = rat1.GetNumerator() * rat2.GetDenominator() + rat2.GetNumerator() * rat1.GetDenominator();
  int q = rat1.GetDenominator() * rat2.GetDenominator();
  return {p, q};
}

Rational operator-(const Rational& rat1, const Rational& rat2) {
  int p = rat1.GetNumerator() * rat2.GetDenominator() - rat2.GetNumerator() * rat1.GetDenominator();
  int q = rat1.GetDenominator() * rat2.GetDenominator();
  return {p, q};
}

Rational operator*(const Rational& rat1, const Rational& rat2) {
  int p = rat1.GetNumerator() * rat2.GetNumerator();
  int q = rat1.GetDenominator() * rat2.GetDenominator();
  return {p, q};
}

Rational operator/(const Rational& rat1, const Rational& rat2) {
  int p = rat1.GetNumerator() * rat2.GetDenominator();
  int q = rat1.GetDenominator() * rat2.GetNumerator();
  return {p, q};
}

bool operator==(const Rational rat1, const Rational rat2) {
  int numerator1 = rat1.GetNumerator();
  int numerator2 = rat2.GetNumerator();
  int denominator1 = rat1.GetDenominator();
  int denominator2 = rat2.GetDenominator();
  return (numerator1 == numerator2 && denominator1 == denominator2);
}

bool operator!=(const Rational rat1, const Rational rat2) {
  int numerator1 = rat1.GetNumerator();
  int numerator2 = rat2.GetNumerator();
  int denominator1 = rat1.GetDenominator();
  int denominator2 = rat2.GetDenominator();
  return (numerator1 != numerator2 || denominator1 != denominator2);
}

bool operator<(const Rational rat1, const Rational rat2) {
  int numerator1 = rat1.GetNumerator();
  int numerator2 = rat2.GetNumerator();
  int denominator1 = rat1.GetDenominator();
  int denominator2 = rat2.GetDenominator();
  return (numerator1 * denominator2 < denominator1 * numerator2);
}

bool operator>(const Rational rat1, const Rational rat2) {
  int numerator1 = rat1.GetNumerator();
  int numerator2 = rat2.GetNumerator();
  int denominator1 = rat1.GetDenominator();
  int denominator2 = rat2.GetDenominator();
  return (numerator1 * denominator2 > denominator1 * numerator2);
}

bool operator<=(const Rational rat1, const Rational rat2) {
  int numerator1 = rat1.GetNumerator();
  int numerator2 = rat2.GetNumerator();
  int denominator1 = rat1.GetDenominator();
  int denominator2 = rat2.GetDenominator();
  return (numerator1 * denominator2 <= denominator1 * numerator2);
}

bool operator>=(const Rational rat1, const Rational rat2) {
  int numerator1 = rat1.GetNumerator();
  int numerator2 = rat2.GetNumerator();
  int denominator1 = rat1.GetDenominator();
  int denominator2 = rat2.GetDenominator();
  return (numerator1 * denominator2 >= denominator1 * numerator2);
}

std::istream& operator>>(std::istream& rin, Rational& rat) {
  int32_t p = 0;
  int32_t q = 1;
  char c = 0;
  rin >> p;
  if (rin.peek() != '/') {
    rat = Rational(p);
    return rin;
  }
  rin >> c;
  rin >> q;
  rat = Rational(p, q);
  return rin;
}

std::ostream& operator<<(std::ostream& rout, const Rational& rat) {
  if (rat.GetDenominator() == 1) {
    rout << rat.GetNumerator();
    return rout;
  }
  rout << rat.GetNumerator() << "/" << rat.GetDenominator();
  return rout;
}