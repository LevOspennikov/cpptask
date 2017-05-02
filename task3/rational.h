//
// Created by ospen on 4/30/2017.
//

#ifndef RATIONAL_H
#define RATIONAL_H


class rational {
public:
    rational(int);
    rational(int, int);
    int getNum() const;
    int getDenom() const;
    rational operator +(rational const &) const;
    rational operator -(rational const &) const;
    rational operator *(rational const &) const;
    rational operator /(rational const &) const;
private:
    rational normalize();
    int numerator, denominator;
};


#endif //RATIONAL_H
