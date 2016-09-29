//
//  myvector.cpp
//  big_integer
//
//  Created by Руслан Абдулхаликов on 18.06.15.
//  Copyright (c) 2015 Руслан Абдулхаликов. All rights reserved.
//

#include <stdio.h>
#include <vector>
#include <iostream>
#include "myvector.h"



void myvector::make_my_copy()
{
    if (*count != 1)
    {
        --*count;
        std::vector<unsigned int> *copy = number;
        number = new std::vector<unsigned int>;
        count = new size_t;
        *number = *copy;
        *count = 1;
    }
}

myvector::myvector() {
    this->number = new std::vector<unsigned int>;
    this->count = new size_t;
    *count = 1;
}

myvector::~myvector() {
    if (*count == 1)
    {
        delete number;
        delete count;
    }
    else
    {
        --*count;
    }
}

myvector::myvector(myvector const& other)
{
    this->number = other.number;
    this->count = other.count;
    ++*count;
}

myvector::myvector(size_t t)
{
    this->number = new std::vector<unsigned int> (t);
    this->count = new size_t;
    *count = 1;
}

void myvector::clear()
{
    if (*count == 1)
    {
        this->number->clear();
    } else
    {
        --*count;
        this->number = new std::vector<unsigned int>;
        this->count = new size_t;
        *count = 1;
    }
}

void myvector::resize(size_t t)
{
    this->make_my_copy();
    this->number->resize(t);
}

void myvector::pop_back()
{
    this->make_my_copy();
    this->number->pop_back();
}

void myvector::push_back(unsigned int t)
{
    this->make_my_copy();
    this->number->push_back(t);
}

void myvector::reverse()
{
    this->make_my_copy();
    std::reverse(number->begin(), number->end());
}

unsigned int myvector::back() const
{
    return this->number->back();
}

size_t myvector::size() const
{
    return this->number->size();
}

myvector& myvector::operator=(myvector const& other)
{
    if (this == &other)
    {
        return *this;
    }
    --(*count);
    if ((*count) == 0)
    {
        delete number;
        delete count;
    }
    this->number = other.number;
    this->count = other.count;
    ++*count;
    return *this;
}

unsigned int& myvector::operator[](size_t t)
{
    this->make_my_copy();
    return number->operator[](t);
}

unsigned int const& myvector::operator[](size_t t) const
{
    return number->operator[](t);
}

