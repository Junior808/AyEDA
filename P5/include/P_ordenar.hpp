#pragma once

template <class CLAVE>
class P_ordenar
{
  public:
    virtual void ordenar(CLAVE *vector, int n_) = 0;
};

// ● Selección
// ● Por Intercambio: Método de la Sacudida
// ● HeapSort
// ● MergeSort
// ● Por Incrementos Decrecientes (ShellSort): debe permitir seleccionar la constante de
// reducción alfa, siendo 0 < alfa < 1