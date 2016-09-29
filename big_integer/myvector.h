//
//  myvector.h
//  big_integer
//
//  Created by Руслан Абдулхаликов on 18.06.15.
//  Copyright (c) 2015 Руслан Абдулхаликов. All rights reserved.
//

#ifndef big_integer_myvector_h
#define big_integer_myvector_h
#include <vector>
struct myvector {
    myvector();
    ~myvector();
    myvector(size_t t);
    myvector(myvector const& other);
    void clear();
    void reverse();
    void resize(size_t t);
    void pop_back();
    void push_back(unsigned int t);
    unsigned int back() const;
    size_t size() const;
    myvector& operator=(myvector const& other);
    void make_my_copy();
    unsigned int& operator[](size_t t);
    unsigned int const& operator[](size_t t) const;
    std::vector<unsigned int> *number;
    size_t *count;
};

#endif
