#pragma once
#include <iostream>
#include "../include/NumberException.hpp"

// Usar dynamic_cast para saber de que tipo es el Number
// Falta incluir en ficheros correspondientes.

class NumberBase
{
private:
  int base_;
  int digito_;

protected:
  virtual void to_base(int number) = 0;
  virtual NumberBase *duplicate(void) const = 0;

public:
  NumberBase(int base, int digito);
  NumberBase(NumberBase &Number);
  virtual ~NumberBase();

  virtual std::ostream &write(std::ostream &os) const = 0;
  virtual NumberBase &operator+(const NumberBase &Number) const = 0;
  virtual NumberBase &operator-(const NumberBase &Number) const = 0;
  virtual NumberBase &operator*(const NumberBase &Number) const = 0;
  friend std::ostream &operator<<(std::ostream &os, NumberBase &Number)
  {
    Number.write(os);
    return os;
  }
};