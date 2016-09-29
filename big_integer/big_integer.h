//
//  big_integer.h
//  big_integer
//
//  Created by Руслан Абдулхаликов on 23.05.15.
//  Copyright (c) 2015 Руслан Абдулхаликов. All rights reserved.
//

#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

#include <iosfwd>
#include <algorithm>
#include "myvector.h"
#include "all_data.h"
#include <cstdlib>

struct big_integer
{
    big_integer();
    big_integer(big_integer const& other);
    big_integer(int a);
    explicit big_integer(std::string const& str);
    ~big_integer();
    
    big_integer& operator=(big_integer const& other);
    
    big_integer& operator+=(big_integer const& rhs);
    big_integer& operator-=(big_integer const& rhs);
    big_integer& operator*=(big_integer const& rhs);
    big_integer& operator/=(big_integer const& rhs);
    big_integer& operator%=(big_integer const& rhs);
    
    big_integer& operator&=(big_integer const& rhs);
    big_integer& operator|=(big_integer const& rhs);
    big_integer& operator^=(big_integer const& rhs);
    
    big_integer& operator<<=(int rhs);
    big_integer& operator>>=(int rhs);
    
    big_integer operator+() const;
    big_integer operator-() const;
    big_integer operator~() const;
    
    big_integer& operator++();
    big_integer operator++(int);
    
    unsigned int divide_short(unsigned int b);
    void multiply_short(unsigned int b);
    big_integer divide_long(big_integer b, big_integer& rem, bool need_rem);
    
    big_integer& operator--();
    big_integer operator--(int);
    
    friend bool operator==(big_integer const& a, big_integer const& b);
    friend bool operator!=(big_integer const& a, big_integer const& b);
    friend bool operator<(big_integer const& a, big_integer const& b);
    friend bool operator>(big_integer const& a, big_integer const& b);
    friend bool operator<=(big_integer const& a, big_integer const& b);
    friend bool operator>=(big_integer const& a, big_integer const& b);
    
    friend std::string to_string(big_integer const& a);
    
private:
    all_data number;
    bool is_negative;
    int cmpr(const big_integer &b) const;
    void additionalCode();
    void inverse(int lenbit);
    big_integer& executeBit(big_integer b, unsigned int (*f)(unsigned int, unsigned int));
    static unsigned int myOr(unsigned int x, unsigned int y);
    static unsigned int myAnd(unsigned int x, unsigned int y);
    static unsigned int myXor(unsigned int x, unsigned int y);
};

big_integer operator+(big_integer a, big_integer const& b);
big_integer operator-(big_integer a, big_integer const& b);
big_integer operator*(big_integer a, big_integer const& b);
big_integer operator/(big_integer a, big_integer const& b);
big_integer operator%(big_integer a, big_integer const& b);

big_integer operator&(big_integer a, big_integer const& b);
big_integer operator|(big_integer a, big_integer const& b);
big_integer operator^(big_integer a, big_integer const& b);

big_integer operator<<(big_integer a, int b);
big_integer operator>>(big_integer a, int b);

bool operator==(big_integer const& a, big_integer const& b);
bool operator!=(big_integer const& a, big_integer const& b);
bool operator<(big_integer const& a, big_integer const& b);
bool operator>(big_integer const& a, big_integer const& b);
bool operator<=(big_integer const& a, big_integer const& b);
bool operator>=(big_integer const& a, big_integer const& b);

std::string to_string(big_integer const& a);
std::ostream& operator<<(std::ostream& s, big_integer const& a);

#endif // BIG_INTEGER_H
