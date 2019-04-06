#pragma once
#include <fExplorar.hpp>
#include <fD_aleatoria.hpp>
#include <fD_modulo.hpp>
#include <fD_suma.hpp>

template <class CLAVE>
class fE_cuadratica : public fExplorar<CLAVE>
{
  private:
    int nCeldas;
    fDispersion<CLAVE> *hx;

  public:
    fE_cuadratica(int size, fDispersion<CLAVE> *funcion_h);
    ~fE_cuadratica();

    int g(const CLAVE clave, int i);
};

template <class CLAVE>
fE_cuadratica<CLAVE>::fE_cuadratica(int size, fDispersion<CLAVE> *funcion_h) : nCeldas(size), hx(funcion_h)
{
}

template <class CLAVE>
fE_cuadratica<CLAVE>::~fE_cuadratica()
{
}

template <class CLAVE>
int fE_cuadratica<CLAVE>::g(const CLAVE clave, int i)
{
    int cuadratica = hx->h(clave);
    return ((cuadratica + (i * i)) % nCeldas);
}
