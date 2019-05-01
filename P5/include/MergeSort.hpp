#pragma once
#include "P_ordenar.hpp"

template <class CLAVE>
class MergeSort : public P_ordenar<CLAVE>
{
  public:
    MergeSort() {}
    ~MergeSort() {}
    void ordenar(CLAVE *vector, int n_);
    void merge(CLAVE *vector, int inicio, int fin);
    void mezclar(CLAVE *vector, int inicio, int centinela, int fin);
};

template <class CLAVE>
void MergeSort<CLAVE>::ordenar(CLAVE *vector, int n_)
{
    merge(vector, 0, n_ - 1);
}

template <class CLAVE>
void MergeSort<CLAVE>::merge(CLAVE *vector, int inicio, int fin)
{
    if (inicio < fin)
    {
        int centinela = (inicio + fin) / 2;
        merge(vector, inicio, centinela);
        merge(vector, centinela + 1, fin);

        mezclar(vector, inicio, centinela, fin);
    }
}

template <class CLAVE>
void MergeSort<CLAVE>::mezclar(CLAVE *vector, int inicio, int centinela, int fin)
{
    int i = inicio, j = centinela + 1, k = inicio;
    CLAVE auxiliar[fin + 1];

    while ((i <= centinela) && (j <= fin))
    {
        if (vector[i] < vector[j])
        {
            auxiliar[k] = vector[i];
            i++;
        }
        else
        {
            auxiliar[k] = vector[j];
            j++;
        }
        k++;
    }

    if (i > centinela)
        while (j <= fin)
        {
            auxiliar[k] = vector[j];
            j++;
            k++;
        }
    else
        while (i <= centinela)
        {
            auxiliar[k] = vector[i];
            i++;
            k++;
        }

    for (int p = inicio; p <= fin; p++)
        vector[p] = auxiliar[p];
}