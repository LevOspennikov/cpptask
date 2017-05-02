//
// Created by ospen on 5/1/2017.
//

#ifndef UNTITLED2_LAZY_STRING_H
#define UNTITLED2_LAZY_STRING_H

#include <cstring>
#include <memory>

class lazy_string {
    struct char_ref {
    public:
        char_ref &operator =(char);

        operator char() const;

        friend class lazy_string;
    private:
        char_ref(lazy_string*, size_t);
        lazy_string * lz_str;
        size_t pos;
    };

public:
    lazy_string();

    lazy_string(const std::string &);

    operator std::string() const;

    size_t size() const;
    size_t length() const;

    char at(size_t) const;
    char_ref at(size_t);

    char operator[](size_t) const;
    lazy_string::char_ref operator[](size_t);

    friend std::istream &operator>>(std::istream &, lazy_string &);
    friend std::ostream &operator<<(std::ostream &, lazy_string &);
    lazy_string substr(size_t, size_t);

private:
    std::shared_ptr<std::string> ptr;
    size_t start, strlen;


};




#endif //UNTITLED2_LAZY_STRING_H
