#pragma once
#include <iostream>

template <class CLAVE>
class NodoB
{
private:
  CLAVE dato;

public:
  NodoB *izquierda;
  NodoB *derecha;

  NodoB(CLAVE dato_, NodoB *izq = NULL, NodoB *der = NULL) : dato(dato_), izquierda(izq), derecha(der) {}
  ~NodoB() {}

  CLAVE get_dato() { return dato; }
  void set_dato(CLAVE dato_) { dato = dato_; }
};