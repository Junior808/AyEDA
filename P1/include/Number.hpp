#pragma once
#include <iostream>
#include <cstdio>
#include <vector>
#include <math.h>

template<size_t N, size_t B, typename T = char>
class Number
{
private:

    std::vector<T> numbers;

    void to_base(int number);
    int get_int(int pos) const;
    char set_char(int& numero, int& carry = 0) const;

public:

    Number(int number = 0);
    ~Number();

    std::ostream& write(std::ostream& os) const;

    Number<N,B,T> Suma(Number<N,B,T>& number1) const;
    Number<N,B,T> Resta(Number<N,B,T>& number1) const;
    Number<N,B,T> Division(Number<N,B,T>& number1) const;
    Number<N,B,T> Multiplicacion(Number<N,B,T>& number1) const;
};

#include "../src/Number.tpp"