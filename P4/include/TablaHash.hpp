#pragma once
#include <Celda.hpp>
#include <fDispersion.hpp>
#include <fD_aleatoria.hpp>
#include <fD_modulo.hpp>
#include <fD_suma.hpp>
#include <fExplorar.hpp>
#include <fE_lineal.hpp>
#include <fE_doble.hpp>
#include <fE_cuadratica.hpp>
#include <fE_redisp.hpp>
#include <Contador.hpp>
#include <DNI.hpp>


template <class CLAVE>
class TablaHash
{
  private:
    int nCeldas;
    int nBloques;

    Celda<CLAVE> **vCelda;

    fDispersion<CLAVE> *dispersion;
    fExplorar<CLAVE> *exploracion;

  public:
    TablaHash(int celdas, int bloques, fDispersion<CLAVE> *funcion_h, fExplorar<CLAVE> *funcion_g);
    ~TablaHash();

    bool buscar(const CLAVE clave) const;
    bool insertar(const CLAVE clave) const;
};

template <class CLAVE>
TablaHash<CLAVE>::TablaHash(int celdas, int bloques, fDispersion<CLAVE> *funcion_h, fExplorar<CLAVE> *funcion_g) : nCeldas(celdas), nBloques(bloques),
                                                                                                                   dispersion(funcion_h), exploracion(funcion_g)
{
    vCelda = new Celda<CLAVE> *[nCeldas];
    for (int i = 0; i < nCeldas; i++)
        vCelda[i] = new Celda<CLAVE>(nBloques);
}

template <class CLAVE>
TablaHash<CLAVE>::~TablaHash()
{
    if (vCelda != NULL)
    {
        for (int i = 0; i < nCeldas; i++)
        {
            if (vCelda[i] != NULL)
            {
                delete[] vCelda[i];
                vCelda[i] = NULL;
            }
        }
        delete[] vCelda;
        nBloques = 0;
        nCeldas = 0;
    }
}

template <class CLAVE>
bool TablaHash<CLAVE>::buscar(const CLAVE clave) const
{
    bool encontrado = false;
    int intento = 1;
    int posicion = dispersion->h(clave);
    ++contador;

    if (!vCelda[posicion]->buscar(clave))
    {
        while (!encontrado && intento < nCeldas)
        {
            int posicion2 = exploracion->g(clave, intento);
            encontrado = vCelda[posicion2]->buscar(clave);
            intento++;
            ++contador;
        }
        return encontrado;
    }

    else
        return true;
}

template <class CLAVE>
bool TablaHash<CLAVE>::insertar(const CLAVE clave) const
{
    int intento = 1;
    bool insertar = false;
    int posicion = dispersion->h(clave);
    ++contador;

    if (!vCelda[posicion]->insertar(clave))
    {
        while (insertar && intento <= nCeldas)
        {
            int posicion2 = exploracion->g(clave, intento);
            insertar = vCelda[posicion2]->insertar(clave);
            intento++;
            ++contador;
        }

        return insertar;
    }
    else
        return true;
}