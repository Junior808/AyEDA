#pragma once
#include <iostream>

template <class CLAVE>
class fDispersion
{
public:
  virtual int h(const CLAVE clave) = 0;
};