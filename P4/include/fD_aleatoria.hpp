#pragma once
#include <iostream>
#include <fDispersion.hpp>

template <class CLAVE>
class fD_aleatoria : public fDispersion<CLAVE>
{
private:
  int nCeldas;

public:
  fD_aleatoria(int size);
  ~fD_aleatoria();

  int h(const CLAVE clave);
};

template <class CLAVE>
fD_aleatoria<CLAVE>::fD_aleatoria(int size) : nCeldas(size)
{
}

template <class CLAVE>
fD_aleatoria<CLAVE>::~fD_aleatoria()
{
}

template <class CLAVE>
int fD_aleatoria<CLAVE>::h(const CLAVE clave)
{
  srand(clave);
  return (rand() % nCeldas);
}
