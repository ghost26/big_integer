//
//  main.cpp
//  big_integer
//
//  Created by Руслан Абдулхаликов on 06.06.15.
//  Copyright (c) 2015 Руслан Абдулхаликов. All rights reserved.
//
#include <iostream>
#include "big_integer.h"

using namespace std;

int main()
{
    big_integer a("2000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001");
    big_integer b("2");
    cout << a * b / b;
    return 0;
}