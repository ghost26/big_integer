//
//  all_data.cpp
//  big_integer
//
//  Created by Руслан Абдулхаликов on 19.06.15.
//  Copyright (c) 2015 Руслан Абдулхаликов. All rights reserved.
//

#include "all_data.h"


all_data::all_data() {
    sz = 0;
    for(size_t i = 0; i < CAPACITY; i++)
        num[i] = 0;
}

all_data::~all_data() {
    if (sz > CAPACITY)
        delete number;
}

all_data::all_data(all_data const& other)
{
    if(other.sz <= CAPACITY) {
        for(size_t i = 0; i < other.sz; i++)
            this->num[i] = other.num[i];
    } else {
        this-> number = new myvector;
        *(this->number) = *other.number;
    }
    this->sz = other.sz;
}

all_data::all_data(size_t t)
{
    for(size_t i = 0; i < CAPACITY; i++)
        num[i] = 0;
    if (t > CAPACITY)
    {
        this->number = new myvector(t);
    }
    sz = t;
}

void all_data::clear()
{
    if (sz > CAPACITY)
    {
        delete this->number;
    }
    for(int i = 0; i < sz; i++)
        this->num[i] = 0;
    sz = 0;
}

void all_data::resize(size_t t)
{
    if (sz <= CAPACITY)
    {

        if (t > CAPACITY)
        {
            this->number = new myvector(t);
            for(size_t i = 0; i < sz; i++)
                this->num[i] = this->number->operator[](i);
        }
        //  this->number->resize(t);
    }
    else
    {
        if (t > CAPACITY)
        {
            this->number->resize(t);
        } else {
            for (size_t i = 0; i < t; i++) {
                num[i] = this -> number -> operator[](i);
            }
        }
    }
    sz = t;
}

void all_data::pop_back()
{
    if (sz > CAPACITY)
    {
        --sz;
        this->number->pop_back();
        if (sz == CAPACITY)
        {
            for(size_t i = 0; i < sz; i++)
                this->num[i] = this->number->operator[](i);
            delete number;
        }
    } else {
        --sz;
    }
}

void all_data::push_back(unsigned int t)
{
    if (sz == CAPACITY)
    {
        this->number = new myvector(sz);
        for(size_t i = 0; i < sz; i++)
            this->number->operator[](i) = this->num[i];
        //this->number->push_back(this->num[i]);

//        ++sz;
        push_back(t);
    } else if (sz < CAPACITY) {
        this->num[sz] = t;
    } else {
        this->number->push_back(t);
//        sz++;
    }
    ++sz;
}

void all_data::reverse()
{
    if (sz <= CAPACITY)
    {
        for (size_t i = 0; i < sz / 2; i++)
            std::swap(this->num[i], this->num[sz - i - 1]);
    }
    else {
        this->number->reverse();
    }
}

unsigned int all_data::back() const
{
    if (sz <= CAPACITY)
    {
        return this->num[sz - 1];
    }
    else {
        return this->number->back();
    }
}

size_t all_data::size() const
{
    return sz;
}

all_data& all_data::operator=(all_data const& other)
{
    if (this == &other)
    {
        return *this;
    }
    if (sz > CAPACITY && other.sz <= CAPACITY)
    {
        delete number;
    }
    else if (sz <= CAPACITY && other.sz > CAPACITY){
        number = new myvector();
    }

    if (other.sz <= CAPACITY)
    {
        for (size_t i = 0; i < other.sz; i++)
        {
            num[i] = other.num[i];
        }
    } else {
        *number = *other.number;
    }
    sz = other.sz;
    return *this;
}

unsigned int& all_data::operator[](size_t t)
{
    if (sz <= CAPACITY)
    {
        return this->num[t];
    } else {
        return this->number->operator[](t);
    }
}

unsigned int const& all_data::operator[](size_t t) const
{
    if (sz <= CAPACITY)
    {
        return this->num[t];
    } else {
        return this->number->operator[](t);
    }
}