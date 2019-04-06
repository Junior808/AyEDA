#pragma once
#include <iostream>
#include <fExplorar.hpp>
#include <fD_aleatoria.hpp>
#include <fD_modulo.hpp>
#include <fD_suma.hpp>

template <class CLAVE>
class fE_redisp : public fExplorar<CLAVE>
{
  private:
    int nCeldas;
    fDispersion<CLAVE> *hx;

  public:
    fE_redisp(int size, fDispersion<CLAVE> *funcion_h);
    ~fE_redisp();

    virtual int g(CLAVE clave, int i);
};

template <class CLAVE>
fE_redisp<CLAVE>::fE_redisp(int size, fDispersion<CLAVE> *funcion_h) : nCeldas(size), hx(funcion_h)
{
}

template <class CLAVE>
fE_redisp<CLAVE>::~fE_redisp()
{
}

template <class CLAVE>
int fE_redisp<CLAVE>::g(CLAVE clave, int i)
{
    int redisp = hx->h(clave);

    fDispersion<CLAVE> *hx2;
    switch (i % 3)
    {
    case 0:
        hx2 = new fD_modulo<CLAVE>(clave);
        break;
    case 1:
        hx2 = new fD_suma<CLAVE>(clave);
        break;
    case 2:
        hx2 = new fD_aleatoria<CLAVE>(clave);
        break;
    default:
        std::cerr << "\nError en la función de redispersión.\n";
        hx2 = new fD_modulo<CLAVE>(clave);
        break;
    }
    int redisp2 = hx2->h(clave);

    return ((redisp + (i * redisp2)) % nCeldas);
}
