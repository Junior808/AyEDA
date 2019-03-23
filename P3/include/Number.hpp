#pragma once
#include <iostream>
#include <cstdio>
#include <vector>
#include <math.h>
#include "../include/NumberException.hpp"
#include "../include/NumberBase.hpp"

template <size_t N, size_t B, class T = char>
class Number : public NumberBase
{
private:
  T *numbers;
  bool negativo;

  void to_base(int number);
  int get_number(int i) const;
  int get_int(int pos) const;
  char set_char(int &numero, int &carry = 0) const;
  int val_abs_(void) const;
  bool get_negativo(void) const;
  bool check_overflow(int val_number1, int val_number2, bool operacion) const;
  bool check_underflow(int val_number1, int val_number2) const;

  void reservar(void);
  void liberar(void);

  Number<N, B, T> Suma(const Number<N, B, T> &number1, Number<N, B, T> &SumaT) const;
  Number<N, B, T> Resta(const Number<N, B, T> &number1, Number<N, B, T> &RestaT) const;
  Number<N, B, T> Multiplicacion(const Number<N, B, T> &number1, Number<N, B, T> &MultiplicacionT) const;

public:
  Number(int number = 0);
  Number(const Number<N, B, T> &Number);
  ~Number();

  std::ostream &write(std::ostream &os) const;

  NumberBase *duplicate() const;

  Number<N, B, T> operator=(const Number<N, B, T> Number1);
  Number<N, B, T> operator+(const Number<N, B, T> number1) const;
  Number<N, B, T> operator-(const Number<N, B, T> number1) const;
  Number<N, B, T> operator*(const Number<N, B, T> number1) const;

  NumberBase &operator+(const NumberBase &Number1) const;
  NumberBase &operator-(const NumberBase &Number1) const;
  NumberBase &operator*(const NumberBase &Number1) const;
};

//#include "../include/Number_Bin.hpp"

template <class T>
class BinaryNumber : public Number<8, 2, T>
{
public:
  BinaryNumber(int number) : Number<8, 2, T>(number) {}
};

template <class T>
class OctalNumber : public Number<8, 8, T>
{
public:
  OctalNumber(int number) : Number<8, 8, T>(number) {}
};

template <class T>
class DecimalNumber : public Number<8, 10, T>
{
public:
  DecimalNumber(int number) : Number<8, 10, T>(number) {}
};

template <class T>
class HexaNumber : public Number<8, 16, T>
{
public:
  HexaNumber(int number) : Number<8, 16, T>(number) {}
};

template <size_t N, size_t B, class T>
Number<N, B, T>::Number(int number) : numbers(NULL), NumberBase(N, B)
{
  if (number < 0)
  {
    negativo = true;
    number = fabs(number);
  }
  else
    negativo = false;

  reservar();

  to_base(number);
}

template <size_t N, size_t B, class T>
Number<N, B, T>::Number(const Number<N, B, T> &Number1) : numbers(NULL), NumberBase(N, B), negativo(Number1.negativo)
{
  reservar();

  for (int i = 0; i < N; i++)
    numbers[i] = Number1.numbers[i];
}

template <size_t N, size_t B, class T>
Number<N, B, T>::~Number()
{
  liberar();
}

template <size_t N, size_t B, class T>
void Number<N, B, T>::reservar()
{
  numbers = new T[N];
}

template <size_t N, size_t B, class T>
void Number<N, B, T>::liberar()
{
  if (numbers)
    delete[] numbers;
}

template <size_t N, size_t B, class T>
NumberBase *Number<N, B, T>::duplicate() const
{
  return new Number<N, B, T>(*this);
}

template <size_t N, size_t B, class T>
Number<N, B, T> Number<N, B, T>::operator=(const Number<N, B, T> Number1)
{
  liberar();
  reservar();

  for (int i = 0; i < N; i++)
    numbers[i] = Number1.numbers[i];

  negativo = Number1.negativo;

  return *this;
}

template <size_t N, size_t B, class T>
Number<N, B, T> Number<N, B, T>::operator+(const Number<N, B, T> Number1) const
{
  Number<N, B, T> SumaT;

  int v_abs = val_abs_();
  int v_abs_number1 = Number1.val_abs_();

  if (check_overflow(v_abs, v_abs_number1, false))
    throw overflow_set_exception();

  if (get_negativo() != Number1.get_negativo())
  {
    if (val_abs_() < Number1.val_abs_())
    {
      SumaT.negativo = Number1.get_negativo();
      return Number1.Resta(*this, SumaT);
    }
    else
    {
      SumaT.negativo = get_negativo();
      return Resta(Number1, SumaT);
    }
  }
  else
  {
    SumaT.negativo = get_negativo();
    return Suma(Number1, SumaT);
  }
}

template <size_t N, size_t B, class T>
NumberBase &Number<N, B, T>::operator+(const NumberBase &Number1) const
{
  auto sumando = dynamic_cast<const Number<N, B, T> &>(Number1);
  auto resultado = dynamic_cast<Number<N, B, T> *>(duplicate());
  *resultado = *this + sumando;
  return *resultado;
}

template <size_t N, size_t B, class T>
Number<N, B, T> Number<N, B, T>::operator-(const Number<N, B, T> Number1) const
{
  Number<N, B, T> RestaT;

  int v_abs = val_abs_();
  int v_abs_number1 = Number1.val_abs_();

  if (check_underflow(v_abs, v_abs_number1))
    throw underflow_set_exception();

  if (get_negativo() != Number1.get_negativo())
  {
    if (val_abs_() < Number1.val_abs_())
    {
      RestaT.negativo = get_negativo();
      return Number1.Suma(*this, RestaT);
    }
    else
    {
      RestaT.negativo = get_negativo();
      return Suma(Number1, RestaT);
    }
  }
  else
  {
    if (val_abs_() < Number1.val_abs_())
    {
      RestaT.negativo = !get_negativo();
      return Number1.Resta(*this, RestaT);
    }
    else
    {
      RestaT.negativo = get_negativo();
      return Resta(Number1, RestaT);
    }
  }
}

template <size_t N, size_t B, class T>
NumberBase &Number<N, B, T>::operator-(const NumberBase &Number1) const
{
  auto minuendo = dynamic_cast<const Number<N, B, T> &>(Number1);
  auto resultado = dynamic_cast<Number<N, B, T> *>(duplicate());
  *resultado = *this - minuendo;
  return *resultado;
}

template <size_t N, size_t B, class T>
Number<N, B, T> Number<N, B, T>::operator*(const Number<N, B, T> Number1) const
{
  Number<N, B, T> MultiplicacionT;

  int signo_number = get_negativo(), signo_number1 = Number1.get_negativo();

  if (check_overflow(val_abs_(), Number1.val_abs_(), true))
    throw overflow_set_exception();

  if (negativo == 1 && Number1.negativo == 1) // (-)*(-) = +
    MultiplicacionT.negativo = !get_negativo();

  else if (negativo != Number1.negativo) // (+)*(-) = -
    MultiplicacionT.negativo = true;

  else if (negativo == 0 && Number1.negativo == 0) // (+)*(+) = +
    MultiplicacionT.negativo = get_negativo();

  return Multiplicacion(Number1, MultiplicacionT);
}

template <size_t N, size_t B, class T>
NumberBase &Number<N, B, T>::operator*(const NumberBase &Number1) const
{
  auto multiplicando = dynamic_cast<const Number<N, B, T> &>(Number1);
  auto resultado = dynamic_cast<Number<N, B, T> *>(duplicate());
  *resultado = *this * multiplicando;
  return *resultado;
}

template <size_t N, size_t B, class T>
void Number<N, B, T>::to_base(int number)
{
  int resto = 0;
  for (int i = 0; i < N; i++)
  {
    resto = number % B;
    if (resto >= 10)
      numbers[i] = resto - 10 + 'A';
    else
      numbers[i] = resto + '0';

    number /= B;
  }
}

template <size_t N, size_t B, class T>
std::ostream &Number<N, B, T>::write(std::ostream &os) const
{
  if (negativo)
    std::cout << "- ";
  else
    std::cout << "+ ";

  for (int i = N - 1; i >= 0; i--)
    std::cout << numbers[i] << ' ';

  std::cout << '\n';
  return os;
}

template <size_t N, size_t B, class T>
int Number<N, B, T>::get_number(int i) const
{
  return numbers[i];
}

template <size_t N, size_t B, class T>
int Number<N, B, T>::get_int(int pos) const
{
  char letra = numbers[pos];
  int conv;

  if (letra > 57)
    conv = letra - 65 + 10;
  else
  {
    conv = numbers[pos] - '0';
  }

  return conv;
}

template <size_t N, size_t B, class T>
char Number<N, B, T>::set_char(int &numero, int &carry) const
{
  char digito;
  if (B > 10)
  {
    if (numero >= B)
    {
      numero = numero - B;
      carry = 1;
      return digito = numero + '0';
    }
    if (numero >= 10)
    {
      numero -= 10;
      carry = 0;
      return digito = numero + 'A';
    }
    else
    {
      carry = 0;
      return digito = numero + '0';
    }
  }
  else
  {
    if (numero >= B)
    {
      numero = numero - B;
      carry = 1;
      return digito = numero + '0';
    }
    else
    {
      carry = 0;
      return digito = numero + '0';
    }
  }
}

template <size_t N, size_t B, class T>
int Number<N, B, T>::val_abs_() const
{
  //Saber cual es el mayor.
  //Diferente signo: al mayor le restamos el menor.
  int val_abs = 0;
  for (int i = 0; i < N; i++)
    val_abs += (get_int(i) * int(pow(B, i)));

  return val_abs;
}

template <size_t N, size_t B, class T>
bool Number<N, B, T>::get_negativo() const
{
  return negativo;
}

template <size_t N, size_t B, class T>
bool Number<N, B, T>::check_overflow(int val_number1, int val_number2, bool operacion) const
{
  //operacion = false ---> Suma
  //operacion = true  ---> Multiplicacion
  if (!operacion)
    return (pow(B, N) - 1 < (val_number1 + val_number2)) ? true : false;
  else
    return (pow(B, N) - 1 < (val_number1 * val_number2)) ? true : false;
}

template <size_t N, size_t B, class T>
bool Number<N, B, T>::check_underflow(int val_number1, int val_number2) const
{
  return (pow(B, N) < (val_number1 + val_number2)) ? true : false;
}

template <size_t N, size_t B, class T>
Number<N, B, T> Number<N, B, T>::Suma(const Number<N, B, T> &number1, Number<N, B, T> &SumaT) const
{
  int carry = 0, numero1, numero2, suma;
  for (int i = 0; i < N; i++)
  {
    numero1 = number1.get_int(i);
    numero2 = get_int(i);
    suma = numero2 + numero1 + carry;

    SumaT.numbers[i] = set_char(suma, carry);
  }
  return SumaT;
}

template <size_t N, size_t B, class T>
Number<N, B, T> Number<N, B, T>::Resta(const Number<N, B, T> &number1, Number<N, B, T> &RestaT) const
{
  int carry = 0, numero1, numero2, resta;
  for (int i = 0; i < N; i++)
  {
    numero1 = number1.get_int(i);
    numero2 = get_int(i);
    resta = numero2 - numero1 - carry;

    if (resta < 0)
    {
      resta = B - fabs(resta);
      RestaT.numbers[i] = set_char(resta, carry);
      carry = 1;
    }
    else
      RestaT.numbers[i] = set_char(resta, carry);
  }
  return RestaT;
}

template <size_t N, size_t B, class T>
Number<N, B, T> Number<N, B, T>::Multiplicacion(const Number<N, B, T> &number1, Number<N, B, T> &MultiplicacionT) const
{
  int multiplicador = number1.val_abs_();

  for (int i = 0; i < multiplicador; i++)
    MultiplicacionT = Suma(MultiplicacionT, MultiplicacionT);

  return MultiplicacionT;
}
