#pragma once

template <class CLAVE>
class NodoAVL
{
private:
    CLAVE dato;
    int bal;

public:
    NodoAVL<CLAVE> *izquierdo;
    NodoAVL<CLAVE> *derecho;

    NodoAVL(CLAVE dato_, NodoAVL<CLAVE> *iz = nullptr, NodoAVL<CLAVE> *der = nullptr) : dato(dato_), bal(0), izquierdo(iz), derecho(der) {}
    ~NodoAVL() {}

    CLAVE get_dato() { return dato; }
    int get_bal() { return bal; }
    void set_dato(CLAVE dato_) { dato = dato_; }
    void set_bal(int bal_) { bal = bal_; }
};