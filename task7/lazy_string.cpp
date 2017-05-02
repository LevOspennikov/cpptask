//
// Created by ospen on 5/1/2017.
//
#include <memory>
#include <cstring>

#include "lazy_string.h"

lazy_string::char_ref & lazy_string::char_ref::operator=(char ch) {
    if (lz_str->ptr.use_count() > 1) {
        lz_str->ptr = std::make_shared<std::string>((*lz_str->ptr).substr(lz_str->start, lz_str->strlen));
        lz_str->start = 0;
    }
    (*lz_str->ptr)[lz_str->start + pos] = ch;
    return *this;
}

lazy_string::char_ref::operator char() const {
    return (*lz_str->ptr)[lz_str->start + this->pos];
}

lazy_string::char_ref::char_ref(lazy_string * lz_str, size_t num) {
    this->lz_str = lz_str;
    this->pos = num;
}

lazy_string::lazy_string() {
    ptr = std::make_shared<std::string>("");
    start = 0;
    strlen = 0;
}

lazy_string::lazy_string(const std::string & str) {
    ptr = std::make_shared<std::string>(str);
    start = 0;
    strlen = str.length();
}

lazy_string::operator std::string() const {
    return (*ptr).substr(start, strlen);
}

size_t lazy_string::size() const {
    return strlen;
}

size_t lazy_string::length() const {
    return strlen;
}

char lazy_string::at(size_t num) const {
    return (*ptr)[num];
}

lazy_string::char_ref lazy_string::at(size_t num) {
    return lazy_string::char_ref(this, num);
}

char lazy_string::operator[](size_t num) const {
    return (*ptr)[num];
}

lazy_string::char_ref lazy_string::operator[](size_t num) {
    return lazy_string::char_ref(this, num);
}

std::istream &operator>>(std::istream & istr, lazy_string & strn) {
    std::shared_ptr<std::string> str = std::make_shared<std::string>();
    istr >> *str;
    strn.ptr = str;
    strn.start = 0;
    strn.strlen = str->length();
    return istr;
}

std::ostream &operator<<(std::ostream & ostr, lazy_string & str) {
    ostr << (*str.ptr).substr(str.start, str.strlen);
    return ostr;
}

lazy_string lazy_string::substr(size_t st, size_t len) {
    lazy_string sbstr;
    sbstr.strlen = len;
    sbstr.ptr = this->ptr;
    sbstr.start = this->start + st;
    return sbstr;
}
