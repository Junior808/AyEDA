#pragma once
#include <iostream>
#include <fDispersion.hpp>

template <class CLAVE>
class fD_suma : public fDispersion<CLAVE>
{
  private:
    int nCeldas;

  public:
    fD_suma(int size);
    ~fD_suma();

    int h(CLAVE clave);
};

template <class CLAVE>
fD_suma<CLAVE>::fD_suma(int size) : nCeldas(size)
{
}

template <class CLAVE>
fD_suma<CLAVE>::~fD_suma()
{
}

template <class CLAVE>
int fD_suma<CLAVE>::h(CLAVE clave)
{
    int d = 0, y = 0, x = 0;
    x = clave;

    while (x > 0)
    {
        y = x % 10;
        d = d + y;
        x = x / 10;
    }

    return (d % nCeldas);
}
