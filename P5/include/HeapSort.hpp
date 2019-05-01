#pragma once
#include "P_ordenar.hpp"

template <class CLAVE>
class HeapSort : public P_ordenar<CLAVE>
{
  public:
    HeapSort() {}
    ~HeapSort() {}
    void ordenar(CLAVE *vector, int n_);
    void floyd(CLAVE *vector, int i_, int n_);
};

template <class CLAVE>
void HeapSort<CLAVE>::ordenar(CLAVE *vector, int n_)
{
    CLAVE cambio;

    for (int i = (n_ / 2) - 1; i >= 0; i--)
        floyd(vector, i, n_);

    for (int i = n_ - 1; i >= 0; i--)
    {
        cambio = vector[0];
        vector[0] = vector[i];
        vector[i] = cambio;
        floyd(vector, 0, i - 1);
    }
}

template <class CLAVE>
void HeapSort<CLAVE>::floyd(CLAVE *vector, int i_, int n_)
{
    CLAVE cambio;
    cambio = vector[i_];
    int h = 0;
    while ((2 * i_) < n_)
    {
        int h1 = (2 * i_ + 1);
        int h2 = h1 + 1;

        if (h1 == n_)
            h = h1;
        else if ((h1 < n_) && (vector[h1] > vector[h2]))
            h = h1;
        else
            h = h2;

        if (vector[h] <= cambio)
            break;

        else
        {
            vector[i_] = vector[h];
            vector[h] = cambio;
            i_ = h;
        }
    }
}