#pragma once
#include <deque>
#include "../include/NodoAVL.hpp"

template <class CLAVE>
class AVL
{
private:
    NodoAVL<CLAVE> *raiz;

    //Operaciones iniciales
    void podar(NodoAVL<CLAVE> *&nodo);

    //Tamano y altura
    const int size_rama(NodoAVL<CLAVE> *nodo);
    const int altura_nodo(NodoAVL<CLAVE> *nodo);

    //Busqueda
    NodoAVL<CLAVE> *buscar_rama(NodoAVL<CLAVE> *nodo, CLAVE clave);

    //Insertar
    void insertar_bal(NodoAVL<CLAVE> *&nodo, NodoAVL<CLAVE> *nuevo, bool &crece);
    void insertar_re_bal_izquierda(NodoAVL<CLAVE> *&nodo, bool &crece);
    void insertar_re_bal_derecha(NodoAVL<CLAVE> *&nodo, bool &crece);

    //Eliminar
    void eliminar_rama(NodoAVL<CLAVE> *&nodo, CLAVE clave, bool &decrece);
    void eliminar_re_bal_izquierda(NodoAVL<CLAVE> *&nodo, bool &decrece);
    void eliminar_re_bal_derecha(NodoAVL<CLAVE> *&nodo, bool &decrece);

    //Recorridos
    void preorden(NodoAVL<CLAVE> *nodo);
    void inorden(NodoAVL<CLAVE> *nodo);
    void postorden(NodoAVL<CLAVE> *nodo);
    void niveles(NodoAVL<CLAVE> *nodo);
    void mostrar(NodoAVL<CLAVE> *nodo);

public:
    AVL();
    ~AVL();
    bool hoja(NodoAVL<CLAVE> *nodo);
    bool vacio(NodoAVL<CLAVE> *nodo);

    //Tamano y altura
    const int size();
    const int altura();

    //Busqueda
    NodoAVL<CLAVE> *buscar(CLAVE clave);

    //Rotaciones
    void rotacion_II(NodoAVL<CLAVE> *&nodo);
    void rotacion_DD(NodoAVL<CLAVE> *&nodo);
    void rotacion_ID(NodoAVL<CLAVE> *&nodo);
    void rotacion_DI(NodoAVL<CLAVE> *&nodo);

    //Insertar
    void insertar(CLAVE clave);

    //Eliminar
    void eliminar(CLAVE clave);

    //Sustituir
    void sustituir(NodoAVL<CLAVE> *&eliminado, NodoAVL<CLAVE> *&sustituto, bool &decrece);

    //Recorridos
    void write(int recorrido);
};

template <class CLAVE>
AVL<CLAVE>::AVL() : raiz(nullptr)
{
}

template <class CLAVE>
AVL<CLAVE>::~AVL()
{
    podar(raiz);
}

template <class CLAVE>
void AVL<CLAVE>::podar(NodoAVL<CLAVE> *&nodo)
{
    if (nodo == nullptr)
        return;

    podar(nodo->izquierdo);
    podar(nodo->derecho);
    delete nodo;
    nodo = nullptr;
}

template <class CLAVE>
bool AVL<CLAVE>::hoja(NodoAVL<CLAVE> *nodo)
{
    return (!nodo->derecha && !nodo->izquierda);
}

template <class CLAVE>
bool AVL<CLAVE>::vacio(NodoAVL<CLAVE> *nodo)
{
    return (nodo == nullptr);
}

template <class CLAVE>
const int AVL<CLAVE>::size()
{
    return size_rama(raiz);
}

template <class CLAVE>
const int AVL<CLAVE>::size_rama(NodoAVL<CLAVE> *nodo)
{
    if (nodo == nullptr)
        return 0;

    return (1 + size_rama(nodo->izquierdo) + size_rama(nodo->derecho));
}

template <class CLAVE>
const int AVL<CLAVE>::altura()
{
    return altura_nodo(raiz);
}

template <class CLAVE>
const int AVL<CLAVE>::altura_nodo(NodoAVL<CLAVE> *nodo)
{
    if (nodo == nullptr)
        return 0;

    int alt_izquierda = altura_nodo(nodo->izquierdo);
    int alt_derecha = altura_nodo(nodo->derecho);

    if (alt_derecha > alt_izquierda)
        return alt_derecha++;
    else
        return alt_izquierda++;
}

template <class CLAVE>
NodoAVL<CLAVE> *AVL<CLAVE>::buscar(CLAVE clave)
{
    return buscar_rama(raiz, clave);
}

template <class CLAVE>
NodoAVL<CLAVE> *AVL<CLAVE>::buscar_rama(NodoAVL<CLAVE> *nodo, CLAVE clave)
{
    if (nodo == nullptr)
        return nullptr;

    if (clave == nodo->get_dato())
        return nodo;

    if (clave < nodo->get_dato())
        return buscar_rama(nodo->izquierdo, clave);

    return buscar_rama(nodo->derecho, clave);
}

template <class CLAVE>
void AVL<CLAVE>::rotacion_II(NodoAVL<CLAVE> *&nodo)
{
    NodoAVL<CLAVE> *nodo1 = nodo->izquierdo;
    nodo->izquierdo = nodo1->derecho;
    nodo1->derecho = nodo;

    if (nodo1->get_bal() == 1)
    {
        nodo->set_bal(0);
        nodo1->set_bal(0);
    }
    else
    {
        nodo->set_bal(1);
        nodo1->set_bal(-1);
    }

    nodo = nodo1;
}

template <class CLAVE>
void AVL<CLAVE>::rotacion_DD(NodoAVL<CLAVE> *&nodo)
{
    NodoAVL<CLAVE> *nodo1 = nodo->derecho;
    nodo->derecho = nodo1->izquierdo;
    nodo1->izquierdo = nodo;

    if (nodo1->get_bal() == -1)
    {
        nodo->set_bal(0);
        nodo1->set_bal(0);
    }
    else
    {
        nodo->set_bal(-1);
        nodo1->set_bal(1);
    }

    nodo = nodo1;
}

template <class CLAVE>
void AVL<CLAVE>::rotacion_ID(NodoAVL<CLAVE> *&nodo)
{
    NodoAVL<CLAVE> *nodo1 = nodo->izquierdo;
    NodoAVL<CLAVE> *nodo2 = nodo1->derecho;

    nodo->izquierdo = nodo2->derecho;
    nodo2->derecho = nodo;
    nodo1->derecho = nodo2->izquierdo;
    nodo2->izquierdo = nodo1;

    if (nodo2->get_bal() == -1)
        nodo1->set_bal(1);
    else
        nodo1->set_bal(0);

    if (nodo2->get_bal() == 1)
        nodo->set_bal(-1);
    else
        nodo->set_bal(0);

    nodo2->set_bal(0);
    nodo = nodo2;
}

template <class CLAVE>
void AVL<CLAVE>::rotacion_DI(NodoAVL<CLAVE> *&nodo)
{
    NodoAVL<CLAVE> *nodo1 = nodo->derecho;
    NodoAVL<CLAVE> *nodo2 = nodo1->izquierdo;

    nodo->derecho = nodo2->izquierdo;
    nodo2->izquierdo = nodo;
    nodo1->izquierdo = nodo2->derecho;
    nodo2->derecho = nodo1;

    if (nodo2->get_bal() == 1)
        nodo1->set_bal(-1);
    else
        nodo1->set_bal(0);

    if (nodo2->get_bal() == -1)
        nodo->set_bal(1);
    else
        nodo->set_bal(0);

    nodo2->set_bal(0);
    nodo = nodo2;
}

template <class CLAVE>
void AVL<CLAVE>::insertar(CLAVE clave)
{
    if (buscar(clave))
        return;

    NodoAVL<CLAVE> *nuevo = new NodoAVL<CLAVE>(clave);
    bool crece = false;
    insertar_bal(raiz, nuevo, crece);
}

template <class CLAVE>
void AVL<CLAVE>::insertar_bal(NodoAVL<CLAVE> *&nodo, NodoAVL<CLAVE> *nuevo, bool &crece)
{
    if (nodo == nullptr)
    {
        nodo = nuevo;
        crece = true;
    }
    else if (nuevo->get_dato() < nodo->get_dato())
    {
        insertar_bal(nodo->izquierdo, nuevo, crece);
        if (crece)
            insertar_re_bal_izquierda(nodo, crece);
    }
    else
    {
        insertar_bal(nodo->derecho, nuevo, crece);
        if (crece)
            insertar_re_bal_derecha(nodo, crece);
    }
}

template <class CLAVE>
void AVL<CLAVE>::insertar_re_bal_izquierda(NodoAVL<CLAVE> *&nodo, bool &crece)
{
    NodoAVL<CLAVE> *nodo1;
    switch (nodo->get_bal())
    {
    case -1:
        nodo->set_bal(0);
        crece = false;
        break;

    case 0:
        nodo->set_bal(1);
        break;
    case 1:
        nodo1 = nodo->izquierdo;
        if (nodo1->get_bal() == 1)
            rotacion_II(nodo);
        else
            rotacion_ID(nodo);
        crece = false;
        break;
    }
}

template <class CLAVE>
void AVL<CLAVE>::insertar_re_bal_derecha(NodoAVL<CLAVE> *&nodo, bool &crece)
{
    NodoAVL<CLAVE> *nodo1;
    switch (nodo->get_bal())
    {
    case 1:
        nodo->set_bal(0);
        crece = false;
        break;
    case 0:
        nodo->set_bal(-1);
        break;
    case -1:
        nodo1 = nodo->derecho;
        if (nodo1->get_bal() == -1)
            rotacion_DD(nodo);
        else
            rotacion_DI(nodo);
        crece = false;
        break;
    }
}

template <class CLAVE>
void AVL<CLAVE>::eliminar(CLAVE clave)
{
    bool decrece = false;
    eliminar_rama(raiz, clave, decrece);
}

template <class CLAVE>
void AVL<CLAVE>::eliminar_rama(NodoAVL<CLAVE> *&nodo, CLAVE clave, bool &decrece)
{
    if (nodo == nullptr)
        return;
    if (clave < nodo->get_dato())
    {
        eliminar_rama(nodo->izquierdo, clave, decrece);
        if (decrece)
            eliminar_re_bal_izquierda(nodo, decrece);
    }
    else if (clave > nodo->get_dato())
    {
        eliminar_rama(nodo->derecho, clave, decrece);
        if (decrece)
            eliminar_re_bal_derecha(nodo, decrece);
    }
    else
    {
        NodoAVL<CLAVE> *eliminado = nodo;
        if (nodo->izquierdo == nullptr)
        {
            nodo = nodo->derecho;
            decrece = true;
        }
        else if (nodo->derecho == nullptr)
        {
            nodo = nodo->izquierdo;
            decrece = true;
        }
        else
        {
            sustituir(eliminado, nodo->izquierdo, decrece);
            if (decrece)
                eliminar_re_bal_izquierda(nodo, decrece);
        }

        delete eliminado;
    }
}

template <class CLAVE>
void AVL<CLAVE>::eliminar_re_bal_izquierda(NodoAVL<CLAVE> *&nodo, bool &decrece)
{
    NodoAVL<CLAVE> *nodo1;
    switch (nodo->get_bal())
    {
    case -1:
        nodo1 = nodo->derecho;
        if (nodo1->get_bal() > 0)
            rotacion_DI(nodo);
        else
        {
            if (nodo1->get_bal() == 0)
                decrece = false;
            rotacion_DD(nodo);
        }
        break;

    case 0:
        nodo->set_bal(-1);
        decrece = false;
        break;
    case 1:
        nodo->set_bal(0);
        break;
    }
}

template <class CLAVE>
void AVL<CLAVE>::eliminar_re_bal_derecha(NodoAVL<CLAVE> *&nodo, bool &decrece)
{
    NodoAVL<CLAVE> *nodo1;
    switch (nodo->get_bal())
    {
    case 1:
        nodo1 = nodo->izquierdo;
        if (nodo->get_bal() < 0)
            rotacion_ID(nodo);
        else
        {
            if (nodo1->get_bal() == 0)
                decrece = false;
            rotacion_II(nodo);
        }
        break;

    case 0:
        nodo->set_bal(1);
        decrece = false;
        break;

    case -1:
        nodo->set_bal(0);
        break;
    }
}

template <class CLAVE>
void AVL<CLAVE>::sustituir(NodoAVL<CLAVE> *&eliminado, NodoAVL<CLAVE> *&sustituto, bool &decrece)
{
    if (sustituto->derecho != nullptr)
    {
        sustituir(eliminado, sustituto->derecho, decrece);
        if (decrece)
            eliminar_re_bal_derecha(sustituto, decrece);
    }
    else
    {
        eliminado->set_dato(sustituto->get_dato());
        eliminado = sustituto;
        sustituto = sustituto->izquierdo;
        decrece = true;
    }
}

template <class CLAVE>
void AVL<CLAVE>::inorden(NodoAVL<CLAVE> *nodo)
{
    if (nodo == nullptr)
        return;

    inorden(nodo->izquierdo);
    std::cout << "[";
    nodo->get_dato().write();
    std::cout << "]";
    inorden(nodo->derecho);
}

template <class CLAVE>
void AVL<CLAVE>::preorden(NodoAVL<CLAVE> *nodo)
{
    if (nodo == nullptr)
        return;

    std::cout << "[";
    nodo->get_dato().write();
    std::cout << "]";
    preorden(nodo->izquierdo);
    preorden(nodo->derecho);
}

template <class CLAVE>
void AVL<CLAVE>::postorden(NodoAVL<CLAVE> *nodo)
{
    if (nodo == nullptr)
        return;

    postorden(nodo->izquierdo);
    postorden(nodo->derecho);
    std::cout << "[";
    nodo->get_dato().write();
    std::cout << "]";
}

template <class CLAVE>
void AVL<CLAVE>::niveles(NodoAVL<CLAVE> *nodo)
{
    std::deque<std::pair<NodoAVL<CLAVE> *, int>> Q;
    NodoAVL<CLAVE> *aux;
    int nivel = 0, nivel_actual = 0;

    Q.push_back(std::pair<NodoAVL<CLAVE> *, int>(nodo, 0));

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
            Q.push_back(std::pair<NodoAVL<CLAVE> *, int>(aux->izquierdo, nivel + 1));
            Q.push_back(std::pair<NodoAVL<CLAVE> *, int>(aux->derecho, nivel + 1));
        }
    }
}

template <class CLAVE>
void AVL<CLAVE>::mostrar(NodoAVL<CLAVE> *nodo)
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
void AVL<CLAVE>::write(int recorrido)
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