#include "../include/NumberBase.hpp"

NumberBase::NumberBase(int base, int digito) : base_(base), digito_(digito)
{
    //Comprobar que son mayor que 1.
    if (base < 1 || digito < 1)
        throw wrong_number_exception();
}

NumberBase::NumberBase(NumberBase &Number) : base_(Number.base_), digito_(Number.digito_)
{
}

NumberBase::~NumberBase()
{
}
