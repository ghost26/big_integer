//
//  main.cpp
//  big_integer
//
//  Created by Руслан Абдулхаликов on 23.05.15.
//  Copyright (c) 2015 Руслан Абдулхаликов. All rights reserved.
//

#include "big_integer.h"
#include <iostream>     // std::cout
#include <algorithm>    // std::reverse
#include "myvector.h"

const int base_len = 32;
const long long base = (1LL << base_len);

big_integer::big_integer() {
    this->number.push_back(0);
    this->is_negative = 0;
}

big_integer::big_integer(big_integer const &other) {
    this->number = other.number;
    this->is_negative = other.is_negative;
}

big_integer::big_integer(int a) {
    this->number.clear();
    this->is_negative = (a < 0);
    this->number.push_back(std::abs(a));
}

big_integer::big_integer(std::string const &str) {
    std::string s;
    bool is_neg;
    if (str == "0" || str == "-0" || str == "+0") {
        is_neg = 0;
        s = str;
        if (s == "-0" || s == "+0")
            s.erase(0, 1);
    }
    else if (str[0] == '-') {
        is_neg = 1;
        s = str;
        s.erase(0, 1);
    }
    else {
        s = str;
        if (s[0] == '+')
            s.erase(0, 1);
        is_neg = 0;
    }

    for (size_t i = 0; i < s.size(); ++i)
        s[i] -= '0';

    is_negative = 0;
    number.push_back(0);
    for (size_t i = 0; i < s.size(); ++i) {

        this->multiply_short(10);
        big_integer p = (int(s[i]));
        *this += p;
    }
    is_negative = is_neg;
    while (number.size() > 1 && number.back() == 0)
        number.pop_back();

}

big_integer::~big_integer() {

}

big_integer big_integer::operator~() const {
    return -(*this + 1);
}

big_integer &big_integer::operator=(big_integer const &other) {
    this->number = other.number;
    this->is_negative = other.is_negative;
    return *this;
}

void big_integer::multiply_short(unsigned int b) {
    unsigned int cf = 0;
    for (size_t i = 0; i < number.size() || cf; ++i) {
        if (i == number.size()) {
            number.push_back(0);
        }
        long long t = (long long) number[i] * b + cf;
        number[i] = (unsigned int) t;//t % (base);
        cf = (unsigned int) (t >> base_len);
    }
    while (number.size() > 1 && number.back() == 0)
        number.pop_back();
    if (number.size() == 1 && number.back() == 0)
        is_negative = 0;
}

unsigned int big_integer::divide_short(unsigned int b) {
    unsigned int cf = 0;
    size_t n = number.size();
    for (size_t i = 0; i < n; ++i) {
        long long cur = (long long) number[n - i - 1] + cf * base;
        number[n - i - 1] = (unsigned int) (cur / b);
        cf = (unsigned int) (cur % b);
    }
    while (number.size() > 1 && number.back() == 0)
        number.pop_back();
    if (number.size() == 1 && number.back() == 0)
        is_negative = 0;
    return cf;
}


big_integer big_integer::divide_long(big_integer val, big_integer &rem, bool need_rem) {
    big_integer a = *this;
    if (val.number.size() == 1) {
        rem = a.divide_short(val.number[0]);
        a.is_negative = a.is_negative ^ val.is_negative;
        if (a.number.back() == 0 && a.number.size() == 1)
            a.is_negative = 0;
        if (rem.number.size() == 1 && rem.number.back() == 0)
            rem.is_negative = 0;
        else
            rem.is_negative = is_negative;
        return a;
    }
    if (number.size() == 1 && number.back() == 0) {
        rem = 0;
        return big_integer();
    }
    big_integer b = val;
    bool is_neg = (is_negative ^ b.is_negative);
    a.is_negative = b.is_negative = 0;
    unsigned int dif = 1;
    while (2LL * b.number.back() < base) {
        a.multiply_short(2);
        b.multiply_short(2);
        dif *= 2;
    }
    size_t n = b.number.size();
    size_t m = a.number.size() - n;

    all_data q(m + 1);
    big_integer h;
    h = b;
//    std::reverse(h.number.begin(), h.number.end());
    h.number.reverse();
    for (int p = 0; p < m; p++)
        h.number.push_back(0);
//    std::reverse(h.number.begin(), h.number.end());
    h.number.reverse();
    if (a >= h) {
        q[m] = 1;
        a -= h;
    }

    for (int i = m - 1; i >= 0; --i) {
        unsigned long long x = ((int) a.number.size() > n + i ? a.number[n + i] : 0);
        unsigned long long y = ((int) a.number.size() > n + i - 1 ? a.number[n + i - 1] : 0);
        unsigned long long qj = ((unsigned long long) x * base + y) / b.number[n - 1];
        int cur_qj = (int) std::min(qj, (unsigned long long) base - 1LL);
        q[i] = cur_qj;
        if (q[i] == 0)
            continue;
        h = b;
        h.multiply_short(q[i]);
        h <<= i * base_len;
        a -= h;
        if (a.is_negative) {
            h = b;
            h <<= i * base_len;
            int cnt = 0;
            while (a.is_negative) {
                q[i]--;
                a += h;
            }
        }
    }

    while (q.size() > 1 && q.back() == 0)
        q.pop_back();

    if (need_rem) {
        a.divide_short(dif);
        rem = a;
    }
    big_integer ans;
    ans.number = q;

    if (ans.number.size() == 1 && ans.number.back() == 0)
        ans.is_negative = 0;
    else
        ans.is_negative = is_neg;

    if (rem.number.size() == 1 && rem.number.back() == 0)
        rem.is_negative = 0;
    else
        rem.is_negative = is_negative;
    return ans;
}

big_integer &big_integer::operator+=(big_integer const &rhs) {
    big_integer b = rhs;
    if (!is_negative && !rhs.is_negative) {
        unsigned int cf = 0;
        for (size_t i = 0; i < std::max(number.size(), rhs.number.size()) || cf; ++i) {
            if (i == number.size()) {
                number.push_back(0);
            }
            long long t = (long long) number[i] + cf + (i < rhs.number.size() ? rhs.number[i] : 0);
            cf = (unsigned int) (t >> base_len);
            number[i] = (unsigned int) t;
        }
    }
    else if (is_negative && b.is_negative) {
        b.is_negative = 0;
        is_negative = 0;
        *this += b;
        is_negative = 1;
    }
    else if (is_negative && !b.is_negative) {

        is_negative = 0;
        bool f = (*this > b);
        if (f)
            *this -= b;
        else
            *this = b - (*this);
        is_negative = f;
    }
    else if (!is_negative && b.is_negative) {

        b.is_negative = 0;
        bool f = (*this >= b);
        if (f)
            *this -= b;
        else
            *this = b - (*this);
        is_negative = !f;
    }
    return *this;
}

big_integer &big_integer::operator-=(big_integer const &rhs) {

    if (!is_negative && !rhs.is_negative && (*this >= rhs)) {
        bool cf = 0;
        for (size_t i = 0; i < rhs.number.size() || cf; ++i) {
            long long t = (long long) number[i] - cf - (i < rhs.number.size() ? rhs.number[i] : 0);
            cf = t < 0;
            if (cf) t += base;
            number[i] = (unsigned int) t;
        }
        while (number.size() > 1 && number.back() == 0)
            number.pop_back();
    }
    else {
        big_integer b = rhs;
        b.is_negative = !b.is_negative;
        *this += b;
    }
    return *this;
}


big_integer &big_integer::operator*=(big_integer const &rhs) {
    big_integer c;
    c.is_negative = is_negative ^ rhs.is_negative;
    c.number.resize(number.size() + rhs.number.size());
    for (size_t i = 0; i < number.size(); ++i) {
        unsigned int cf = 0;
        for (size_t j = 0; j < rhs.number.size() || cf; ++j) {
            unsigned long long cur = (unsigned long long) c.number[i + j] +
                                     (unsigned long long) number[i] * (j < rhs.number.size() ? rhs.number[j] : 0) + cf;
            c.number[i + j] = (unsigned int) cur;
            cf = (unsigned int) (cur >> base_len);
        }
    }
    while (c.number.size() > 1 && c.number.back() == 0)
        c.number.pop_back();
    if (c.number.back() == 0 && c.number.size() == 1) {
        c.is_negative = 0;
    }
    return *this = c;
}

big_integer &big_integer::operator/=(big_integer const &rhs) {
    big_integer rem;
    return *this = this->divide_long(rhs, rem, false);
}

big_integer &big_integer::operator%=(big_integer const &rhs) {
    big_integer rem;
    this->divide_long(rhs, rem, true);
    return *this = rem;
}

void big_integer::inverse(int lenbit = -1) {
    additionalCode();
    if (lenbit != -1)
        while ((int) number.size() < lenbit)
            number.push_back(0);
    for (size_t i = 0; i < number.size(); ++i)
        number[i] = ~number[i];
}

unsigned int big_integer::myOr(unsigned int x, unsigned int y) { return x | y; }

unsigned int big_integer::myAnd(unsigned int x, unsigned int y) { return x & y; }

unsigned int big_integer::myXor(unsigned int x, unsigned int y) { return x ^ y; }

big_integer &big_integer::executeBit(big_integer curb, unsigned int (*f)(unsigned int, unsigned int)) {
    big_integer cura = *this;

    big_integer res;
    res.number.pop_back();
    res.number.resize(std::max(number.size(), curb.number.size()));
    bool neg1 = (is_negative == 1);
    bool neg2 = (curb.is_negative == 1);
    while (cura.number.size() < res.number.size()) cura.number.push_back(0);
    while (curb.number.size() < res.number.size()) curb.number.push_back(0);

    if (neg1)
        cura.inverse(res.number.size());
    if (neg2)
        curb.inverse(res.number.size());

    for (size_t i = 0; i < res.number.size(); ++i)
        res.number[i] = f(cura.number[i], curb.number[i]);

    if (f(neg1, neg2)) res.is_negative = 1;
    else res.is_negative = 0;

    int sv = res.is_negative;
    if (res.is_negative == 1)
        res.inverse();
    res.is_negative = sv;
    while (res.number.size() > 1 && res.number.back() == 0)
        res.number.pop_back();
    if (res.number.size() == 1 && res.number.back() == 0)
        res.is_negative = 0;
    return *this = res;
}

big_integer &big_integer::operator|=(big_integer const &value) {
    return executeBit(value, myOr);
}

big_integer &big_integer::operator&=(big_integer const &value) {
    return executeBit(value, myAnd);
}

big_integer &big_integer::operator^=(big_integer const &value) {
    return executeBit(value, myXor);
}

big_integer operator|(big_integer a, big_integer const &b) {
    return a |= b;
}

big_integer operator&(big_integer a, big_integer const &b) {
    return a &= b;
}

big_integer operator^(big_integer a, big_integer const &b) {
    return a ^= b;
}

big_integer &big_integer::operator<<=(int rhs) {
//    std::reverse(number.begin(), number.end());
    number.reverse();
    for (int i = 0; i < rhs / base_len; ++i)
        number.push_back(0);
     number.reverse();
//    std::reverse(number.begin(), number.end());

    rhs %= base_len;
    if (rhs != 0) {
        unsigned int carry = number[0] >> (base_len - rhs);
        number[0] <<= rhs;
        for (size_t i = 1; i < number.size(); ++i) {
            unsigned int newcarry = number[i] >> (base_len - rhs);
            number[i] <<= rhs;
            number[i] |= carry;
            carry = newcarry;
        }
        if (carry) number.push_back(carry);
        while (number.size() > 1 && number.back() == 0) number.pop_back();
    }
    return *this;
}

void big_integer::additionalCode() {
    is_negative = !is_negative;
    big_integer d(1);
    *this -= d;
}

big_integer &big_integer::operator>>=(int rhs) {
    if (is_negative == 0) {
        int leng = ((int) number.size() - 1) * base_len;
        unsigned int x = number.back();
        for (; x; leng++, x >>= 1);

        if (rhs >= leng) {
            while (number.size() > 0) number.pop_back();
            is_negative = 0;
            number.push_back(0);
        } else {
      //      reverse(number.begin(), number.end());
            number.reverse();
            for (int i = 0; i < rhs / base_len; ++i) number.pop_back();
            rhs %= base_len;
            number.reverse();
//            reverse(number.begin(), number.end());

            if (rhs != 0) {
                number[0] >>= rhs;
                for (size_t i = 1; i < number.size(); ++i) {
                    unsigned int rem = number[i] & ((1 << rhs) - 1);
                    number[i - 1] |= rem << (base_len - rhs);
                    number[i] >>= rhs;
                }
                while (number.size() > 1 && number.back() == 0) number.pop_back();
            }
        }
    } else {
        this->additionalCode();
        *this >>= rhs;
        this->additionalCode();
    }
    return *this;
}

big_integer big_integer::operator+() const {
    return *this;
}

big_integer big_integer::operator-() const {
    if (number.size() == 1 && number.back() == 0)
        return *this;
    big_integer a(*this);
    a.is_negative = !a.is_negative;
    return a;
}

big_integer &big_integer::operator++() {
    *this += big_integer(1);
    return *this;
}

big_integer big_integer::operator++(int) {
    big_integer a(*this);
    *this += big_integer(1);
    return a;
}

big_integer &big_integer::operator--() {
    *this -= big_integer(1);
    return *this;
}

big_integer big_integer::operator--(int) {
    big_integer a(*this);
    *this -= big_integer(1);
    return a;
}

big_integer operator+(big_integer a, big_integer const &b) {
    return a += b;
}

big_integer operator-(big_integer a, big_integer const &b) {
    return a -= b;
}

big_integer operator*(big_integer a, big_integer const &b) {
    return a *= b;
}

big_integer operator/(big_integer a, big_integer const &b) {
    return a /= b;
}

big_integer operator%(big_integer a, big_integer const &b) {
    return a %= b;
}

big_integer operator<<(big_integer a, int b) {
    return a <<= b;
}

big_integer operator>>(big_integer a, int b) {
    return a >>= b;
}


int big_integer::cmpr(const big_integer &b) const {
    int sign1 = !is_negative;
    int sign2 = !b.is_negative;

    if (sign1 == sign2) {
        if (number.size() < b.number.size())
            return -sign1;
        if (number.size() > b.number.size())
            return sign1;

        for (int i = (int) number.size() - 1; i >= 0; --i)
            if (number[i] < b.number[i])
                return -sign1;
            else if (number[i] > b.number[i])
                return sign1;
        return 0;
    } else
        return (sign1 < sign2 ? -1 : 1);
}

bool operator<(big_integer const &a, big_integer const &b) {
    return a.cmpr(b) < 0;
}

bool operator<=(big_integer const &a, big_integer const &b) {
    return a.cmpr(b) <= 0;
}

bool operator>(big_integer const &a, big_integer const &b) {
    return a.cmpr(b) > 0;
}

bool operator>=(big_integer const &a, big_integer const &b) {
    return a.cmpr(b) >= 0;
}

bool operator==(big_integer const &a, big_integer const &b) {
    return a.cmpr(b) == 0;
}

bool operator!=(big_integer const &a, big_integer const &b) {
    return a.cmpr(b) != 0;
}

std::string to_string(const big_integer &a) {
    std::string res;
    bool is_neg = false;
    big_integer b = a;
    if (b.is_negative == true) {
        is_neg = true;
        b.is_negative = false;
    } else if (b.number.size() == 1 && b.number.back() == 0) return "0";
    while (b.number.size() > 1 || b.number.back() != 0)
        res += char(b.divide_short(10) + '0');
    reverse(res.begin(), res.end());
    if (is_neg)
        return "-" + res;
    return res;
}

std::ostream &operator<<(std::ostream &s, big_integer const &a) {
    return s << to_string(a);
}

