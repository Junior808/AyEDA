#pragma once
#include <iostream>
#include "../include/Contador.hpp"

static Contador contador;

class DNI
{
private:
  unsigned numero;

public:
  DNI();
  DNI(unsigned num);
  ~DNI();

  unsigned get_num() const;
  void write() const;

  bool operator==(const DNI &dni) const;
  void operator=(const int n);
  bool operator<(const DNI &dni) const;
  bool operator>(const DNI &dni) const;

  int operator%(const int n) const;
  operator unsigned long() const { return get_num(); }
};

DNI::DNI()
{
  numero = 00000000;
  // srand(time(NULL));
  // for (int i = 0; i < 8; i++)
  //   numero[i] = rand() % 10;
}

DNI::DNI(unsigned num)
{
  numero = num;
  // srand(num);
  // for (int i = 0; i < 8; i++)
  //   numero[i] = rand() % 10;
}

DNI::~DNI()
{
}

unsigned DNI::get_num() const
{
  // int aux = 1, num = 0;
  // for (int i = 7; i >= 0; i--)
  // {
  //   num += numero[i] * aux;

  //   aux *= 10;
  // }
  return numero;
}

bool DNI::operator==(const DNI &dni) const
{
  ++contador;
  return (get_num() == dni.get_num());
}

void DNI::operator=(const int n)
{
  //++contador;
  numero = n;
  // unsigned aux = n, i = 0;
  // while (aux < 10)
  // {
  //   numero[i] = (aux % 10);
  //   aux /= 10;
  //   i++;
  // }
}

int DNI::operator%(const int n) const
{
  return get_num() % n;
}

bool DNI::operator>(const DNI &dni) const
{
  ++contador;
  return (get_num() > dni.get_num());
}

bool DNI::operator<(const DNI &dni) const
{
  ++contador;
  return (get_num() < dni.get_num());
}

void DNI::write() const
{
  // for (unsigned i = 0; i < 8; i++)
  std::cout << numero;
}