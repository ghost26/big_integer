//
//  all_data.h
//  big_integer
//
//  Created by Руслан Абдулхаликов on 19.06.15.
//  Copyright (c) 2015 Руслан Абдулхаликов. All rights reserved.
//

#ifndef __big_integer__all_data__
#define __big_integer__all_data__

#include <stdio.h>
#include "myvector.h"

struct all_data {
    all_data();
    ~all_data();
    all_data(size_t t);
    all_data(all_data const& other);
    void clear();
    void reverse();
    void resize(size_t t);
    void pop_back();
    void push_back(unsigned int t);
    unsigned int back() const;
    size_t size() const;
    all_data& operator=(all_data const& other);
   // void make_my_copy();
    unsigned int& operator[](size_t t);
    unsigned int const& operator[](size_t t) const;
    myvector *number;
    unsigned int num[16];
    size_t sz;
    const size_t CAPACITY = 16;
};


#endif 
// defined(__big_integer__all_data__) 
