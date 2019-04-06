#pragma once
#include <iostream>

template <class CLAVE>
class Celda
{
  private:
    int nBloques;
    int lleno;
    CLAVE *V;

  public:
    Celda(void);
    Celda(int size);
    ~Celda(void);

    bool buscar(const CLAVE clave);
    bool insertar(const CLAVE clave);
    bool llena(void);
};

template <class CLAVE>
Celda<CLAVE>::Celda(void) : nBloques(0), V(NULL)
{
}

template <class CLAVE>
Celda<CLAVE>::Celda(int size) : nBloques(size), V(NULL)
{
    V = new CLAVE[nBloques];
    lleno = 0;
}

template <class CLAVE>
Celda<CLAVE>::~Celda()
{
    if (V != NULL)
    {
        delete[] V;
        V = NULL;
        nBloques = 0;
    }
}

template <class CLAVE>
bool Celda<CLAVE>::buscar(const CLAVE clave)
{
    for (int i = 0; i < nBloques; i++)
        if (V[i] == clave)
            return true;

    return false;
}

template <class CLAVE>
bool Celda<CLAVE>::insertar(const CLAVE clave)
{
   if(!llena() && !buscar(clave))
   {
       V[lleno] = clave;
       lleno++;
       return true;
   }

    return false;
}

template <class CLAVE>
bool Celda<CLAVE>::llena(void)
{
    if (lleno == nBloques)
            return true;

    return false;
}
