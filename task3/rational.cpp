//
// Created by ospen on 4/30/2017.
//

#include "rational.h"
#include <algorithm>

rational::rational(int numerator) {
    this->numerator = numerator;
    this->denominator = 1;
}

rational::rational(int numerator, int denominator) {
    this->numerator = numerator;
    this->denominator = denominator;
    this->normalize();
}

int rational::getNum() const {
    return numerator;
}

int rational::getDenom() const {
    return denominator;
}

rational rational::operator+(rational const &rvalue) const {
    return rational(denominator * rvalue.numerator + numerator * rvalue.denominator, denominator * rvalue.denominator).normalize();
}

rational rational::operator-(rational const &rvalue) const {
    return rational(numerator * rvalue.denominator - denominator * rvalue.numerator, denominator * rvalue.denominator).normalize();
}

rational rational::operator*(rational const &rvalue) const {
    return rational(numerator * rvalue.numerator, denominator * rvalue.denominator).normalize();
}

rational rational::operator/(rational const &rvalue) const {
    return rational(numerator * rvalue.denominator, denominator * rvalue.numerator).normalize();
}

rational rational::normalize() {
    int gcd = std::__gcd(numerator, denominator);
    if (gcd < 0) {
        gcd = abs(gcd);
    }
    numerator = numerator / gcd;
    denominator = denominator / gcd;
    return *this;
}
