#pragma once
#include "P_ordenar.hpp"

template <class CLAVE>
class ShellSort : public P_ordenar<CLAVE>
{
  private:
    float alfa;

  public:
    ShellSort(float alfa_) : alfa(alfa_) {}
    ~ShellSort() {}
    void ordenar(CLAVE *vector, int n_);
    void deltasort(CLAVE *vector, int delta, int n);
};

template <class CLAVE>
void ShellSort<CLAVE>::ordenar(CLAVE *vector, int n_)
{
    int delta = n_ * alfa;
    while (delta > 0)
    {
        delta = delta / 2;
        deltasort(vector, delta, n_);
    }
}

template <class CLAVE>
void ShellSort<CLAVE>::deltasort(CLAVE *vector, int delta, int n)
{
    bool chivato;
    CLAVE x;
    int j = 0;
    for (int i = delta; i < n; i++)
    {
        chivato = false;
        x = vector[i];
        j = i;
        while ((j >= delta) && (x < vector[j - delta]))
        {
            vector[j] = vector[j - delta];
            j = j - delta;
            chivato = true;
        }
        if (chivato)
        vector[j] = x;
    }
}