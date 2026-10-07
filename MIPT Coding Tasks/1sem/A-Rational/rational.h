#include <iostream>
#include <stdexcept>

#ifndef RATIONAL_H
#define RATIONAL_H

class RationalDivisionByZero : public std::runtime_error {
 public:
  RationalDivisionByZero() : std::runtime_error("RationalDivisionByZero") {
  }
};

class Rational {
 private:
  int p_;
  int q_;
 public:
  void MakeRational();
  Rational();
  Rational(int);  // NOLINT
  Rational(int, int);
  int GetNumerator() const;
  int GetDenominator() const;
  void SetNumerator(int);
  void SetDenominator(int);
};

Rational& operator++(Rational&);
Rational& operator--(Rational&);
Rational operator++(Rational&, int);
Rational operator--(Rational&, int);
Rational& operator+=(Rational&, const Rational&);
Rational& operator-=(Rational&, const Rational&);
Rational& operator*=(Rational&, const Rational&);
Rational& operator/=(Rational&, const Rational&);
Rational operator+(const Rational&);
Rational operator-(const Rational&);
Rational operator+(const Rational&, const Rational&);
Rational operator-(const Rational&, const Rational&);
Rational operator*(const Rational&, const Rational&);
Rational operator/(const Rational&, const Rational&);

bool operator==(const Rational, const Rational);
bool operator!=(const Rational, const Rational);
bool operator<(const Rational, const Rational);
bool operator>(const Rational, const Rational);
bool operator<=(const Rational, const Rational);
bool operator>=(const Rational, const Rational);

std::ostream& operator<<(std::ostream&, const Rational&);
std::istream& operator>>(std::istream&, Rational&);

#endif /* RATIONAL_H */