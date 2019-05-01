#pragma once
#include "P_ordenar.hpp"

template <class CLAVE>
class Seleccion : public P_ordenar<CLAVE>
{
  public:
    Seleccion() {}
    ~Seleccion() {}
    void ordenar(CLAVE *vector, int n_);
};

template <class CLAVE>
void Seleccion<CLAVE>::ordenar(CLAVE *vector, int n_)
{
    CLAVE cambio;
    for (int i = 0; i < n_; i++)
    {
        int min = i;
        for (int j = i + 1; j < n_; j++)
            if (vector[j] < vector[min])
                min = j;

        cambio = vector[min];
        vector[min] = vector[i];
        vector[i] = cambio;
    }
}