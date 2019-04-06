#pragma once

template <class CLAVE>
class fExplorar
{
public:
  virtual int g(const CLAVE clave, int i) = 0;
};