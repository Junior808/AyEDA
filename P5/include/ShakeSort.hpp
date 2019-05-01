#pragma once
#include "P_ordenar.hpp"

template <class CLAVE>
class ShakeSort : public P_ordenar<CLAVE>
{
  public:
    ShakeSort() {}
    ~ShakeSort() {}
    void ordenar(CLAVE *vector, int n_);
};

template <class CLAVE>
void ShakeSort<CLAVE>::ordenar(CLAVE *vector, int n_)
{
    int inicio = 0, fin = n_ - 1, cam = n_;
    CLAVE cambio;

    while (inicio <= fin)
    {
        for (int i = fin; i >= inicio; i--)
            if (vector[i] < vector[i - 1])
            {
                cambio = vector[i - 1];
                vector[i - 1] = vector[i];
                vector[i] = cambio;
                cam = i;
            }

        inicio = cam + 1;
        for (int j = inicio; j <= fin; j++)
            if (vector[j] < vector[j - 1])
            {
                cambio = vector[j - 1];
                vector[j - 1] = vector[j];
                vector[j] = cambio;
                cam = j;
            }

        fin = cam - 1;
    }
}
