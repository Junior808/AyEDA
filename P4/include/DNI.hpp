#pragma once
#include <iostream>
#include <Contador.hpp>

static Contador contador;

class DNI
{
private:
  int numero;

public:
  DNI();
  DNI(int num);
  DNI(DNI &dni);
  ~DNI();

  bool operator==(const DNI &dni);
  bool operator>(DNI& dni);
  int operator%(int n);
  operator unsigned long() const { return numero; }
};

DNI::DNI() : numero(0)
{
}

DNI::DNI(int num) : numero(num)
{
}

DNI::DNI(DNI &dni) : numero(dni.numero)
{
}

DNI::~DNI()
{
}

bool DNI::operator==(const DNI &dni)
{
    ++contador;
    return (numero == dni.numero);
}

int DNI::operator%(int n)
{
    return numero % n;
}

bool DNI::operator>(DNI& dni)
{
    return (numero > dni.numero);
}