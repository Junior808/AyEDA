#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <deque>
#include "NodoB.hpp"

using namespace std;

template <class CLAVE>
class ABB
{
  private:
    NodoB<CLAVE> *raiz;

    //Operaciones iniciales
    void podar(NodoB<CLAVE> *&nodo);

    //Tamano y altura
    const int size_rama(NodoB<CLAVE> *nodo);
    const int altura_nodo(NodoB<CLAVE> *nodo);

    //Métodos ABB
    NodoB<CLAVE> *buscar_rama(NodoB<CLAVE> *nodo, CLAVE clave);
    void insertar_rama(NodoB<CLAVE> *&nodo, CLAVE clave);
    void sustituir(NodoB<CLAVE> *&eliminado, NodoB<CLAVE> *&sustituto);
    void eliminar_rama(NodoB<CLAVE> *&nodo, CLAVE clave);

  public:
    //Operaciones Iniciales + Podar

    ABB();
    ~ABB();
    bool hoja(NodoB<CLAVE> *nodo);
    bool vacio(NodoB<CLAVE> *nodo);

    //Tamano y altura
    const int size();
    const int altura();

    //Métodos ABB
    NodoB<CLAVE> *buscar(CLAVE clave);
    void insertar(CLAVE clave);
    void eliminar(CLAVE clave);

    //Recorridos
    void preorden(NodoB<CLAVE> *nodo);
    void inorden(NodoB<CLAVE> *nodo);
    void postorden(NodoB<CLAVE> *nodo);
    void niveles(NodoB<CLAVE> *nodo);
    void mostrar(NodoB<CLAVE> *nodo);
    void write(int recorrido);
};

template <class CLAVE>
ABB<CLAVE>::ABB() : raiz(nullptr)
{
}

template <class CLAVE>
ABB<CLAVE>::~ABB()
{
    podar(raiz);
}

template <class CLAVE>
void ABB<CLAVE>::podar(NodoB<CLAVE> *&nodo)
{
    if (nodo == nullptr)
        return;

    podar(nodo->izquierda);
    podar(nodo->derecha);
    delete nodo;
    nodo = nullptr;
}

template <class CLAVE>
bool ABB<CLAVE>::hoja(NodoB<CLAVE> *nodo)
{
    return (!nodo->derecha && !nodo->izquierda);
}

template <class CLAVE>
bool ABB<CLAVE>::vacio(NodoB<CLAVE> *nodo)
{
    return (nodo == nullptr);
}

template <class CLAVE>
const int ABB<CLAVE>::size()
{
    return size_rama(raiz);
}

template <class CLAVE>
const int ABB<CLAVE>::size_rama(NodoB<CLAVE> *nodo)
{
    if (nodo == nullptr)
        return 0;

    return (1 + size_rama(nodo->izquierda) + size_rama(nodo->derecha));
}

template <class CLAVE>
const int ABB<CLAVE>::altura()
{
    return altura_nodo(raiz);
}

template <class CLAVE>
const int ABB<CLAVE>::altura_nodo(NodoB<CLAVE> *nodo)
{
    if (nodo == nullptr)
        return 0;

    int alt_izquierda = altura_nodo(nodo->izquierda);
    int alt_derecha = altura_nodo(nodo->derecha);

    if (alt_derecha > alt_izquierda)
        return alt_derecha++;
    else
        return alt_izquierda++;
}

template <class CLAVE>
NodoB<CLAVE> *ABB<CLAVE>::buscar(CLAVE clave)
{
    return buscar_rama(raiz, clave);
}

template <class CLAVE>
NodoB<CLAVE> *ABB<CLAVE>::buscar_rama(NodoB<CLAVE> *nodo, CLAVE clave)
{
    if (nodo == nullptr)
        return nullptr;

    if (clave == nodo->get_dato())
        return nodo;

    if (clave < nodo->get_dato())
        return buscar_rama(nodo->izquierda, clave);

    return buscar_rama(nodo->derecha, clave);
}

template <class CLAVE>
void ABB<CLAVE>::insertar(CLAVE clave)
{
    if (buscar(clave))
        return;

    insertar_rama(raiz, clave);
}

template <class CLAVE>
void ABB<CLAVE>::insertar_rama(NodoB<CLAVE> *&nodo, CLAVE clave)
{
    if (nodo == nullptr)
        nodo = new NodoB<CLAVE>(clave);

    else if (clave < nodo->get_dato())
        insertar_rama(nodo->izquierda, clave);

    else
        insertar_rama(nodo->derecha, clave);
}

template <class CLAVE>
void ABB<CLAVE>::eliminar(CLAVE clave)
{
    eliminar_rama(raiz, clave);
}

template <class CLAVE>
void ABB<CLAVE>::eliminar_rama(NodoB<CLAVE> *&nodo, CLAVE clave)
{
    if (nodo == nullptr)
        return;

    if (clave < nodo->get_dato())
        eliminar_rama(nodo->izquierda, clave);

    else if (clave > nodo->get_dato())
        eliminar_rama(nodo->derecha, clave);

    else
    {
        NodoB<CLAVE> *eliminado = nodo;

        if (nodo->derecha == nullptr)
            nodo = nodo->izquierda;

        else if (nodo->izquierda == nullptr)
            nodo = nodo->derecha;

        else
            sustituir(eliminado, nodo->izquierda);

        delete (eliminado);
    }
}

template <class CLAVE>
void ABB<CLAVE>::sustituir(NodoB<CLAVE> *&eliminado, NodoB<CLAVE> *&sustituto)
{
    if (sustituto->derecha != nullptr)
        sustituir(eliminado, sustituto->derecha);

    else
    {

        eliminado->set_dato(sustituto->get_dato());
        eliminado = sustituto;

        sustituto = sustituto->izquierda;
    }
}

template <class CLAVE>
void ABB<CLAVE>::inorden(NodoB<CLAVE> *nodo)
{
    if (nodo == nullptr)
        return;

    inorden(nodo->izquierda);
    std::cout << "[";
    nodo->get_dato().write();
    std::cout << "]";
    inorden(nodo->derecha);
}

template <class CLAVE>
void ABB<CLAVE>::preorden(NodoB<CLAVE> *nodo)
{
    if (nodo == nullptr)
        return;

    std::cout << "[";
    nodo->get_dato().write();
    std::cout << "]";
    preorden(nodo->izquierda);
    preorden(nodo->derecha);
}

template <class CLAVE>
void ABB<CLAVE>::postorden(NodoB<CLAVE> *nodo)
{
    if (nodo == nullptr)
        return;

    postorden(nodo->izquierda);
    postorden(nodo->derecha);
    std::cout << "[";
    nodo->get_dato().write();
    std::cout << "]";
}

template <class CLAVE>
void ABB<CLAVE>::niveles(NodoB<CLAVE> *nodo)
{
    std::deque<std::pair<NodoB<CLAVE> *, int>> Q;
    NodoB<CLAVE> *aux;
    int nivel = 0, nivel_actual = 0;

    Q.push_back(std::pair<NodoB<CLAVE> *, int>(nodo, 0));

    std::cout << "\nNivel 0: ";

    while (!Q.empty())
    {
        aux = (Q.front()).first;
        nivel = (Q.front()).second;
        Q.pop_front();

        if (nivel > nivel_actual)
        {
            nivel_actual = nivel;
            std::cout << "\nNivel " << nivel_actual << ": ";
        }

        mostrar(aux);
        if (aux != nullptr)
        {
            Q.push_back(std::pair<NodoB<CLAVE> *, int>(aux->izquierda, nivel + 1));
            Q.push_back(std::pair<NodoB<CLAVE> *, int>(aux->derecha, nivel + 1));
        }
    }
}

template <class CLAVE>
void ABB<CLAVE>::mostrar(NodoB<CLAVE> *nodo)
{
    if (nodo == nullptr)
        std::cout << "[.]";
    else
    {
        std::cout << "[";
        nodo->get_dato().write();
        std::cout << "]";
    }
}

template <class CLAVE>
void ABB<CLAVE>::write(int recorrido)
{
    if (recorrido == 1)
        preorden(raiz);
    else if (recorrido == 2)
        inorden(raiz);
    else if (recorrido == 3)
        postorden(raiz);
    else
        niveles(raiz);
}