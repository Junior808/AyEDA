#pragma once
#include <iostream>
#include <cstdio>
#include <vector>
#include <math.h>
#include <exception>

template <size_t N, size_t B, typename T = char>
class Number
{
private:
  T *numbers;
  bool negativo;

  void to_base(int number);
  int get_number(int i) const;
  char set_char(int &numero, int &carry = 0) const;
  int val_abs_(void) const;
  bool get_negativo(void) const;
  bool check_overflow(int val_number1, int val_number2, bool operacion) const;
  bool check_underflow(int val_number1, int val_number2) const;

  void reservar(void);
  void liberar(void);

  Number<N, B, T> Suma(Number<N, B, T> &number1, Number<N, B, T> &SumaT) const;
  Number<N, B, T> Resta(Number<N, B, T> &number1, Number<N, B, T> &RestaT) const;
  Number<N, B, T> Multiplicacion(Number<N, B, T> &number1, Number<N, B, T> &MultiplicacionT) const;

public:
  Number(int number = 0);
  Number(const Number<N, B, T> &Number);
  Number(const Number<N-1,B,T> &Number);
  ~Number();

  std::ostream &write(std::ostream &os) const;
  int get_int(int pos) const;

  Number<N, B, T> operator=(Number<N, B, T> Number1);
  Number<N, B, T> operator+(Number<N, B, T> number1);
  Number<N, B, T> operator-(Number<N, B, T> number1);
  Number<N, B, T> operator*(Number<N, B, T> number1);
  Number<N+1, B, T> operator()();
};


//Especialización binario

template <size_t N, typename T>
class Number<N,2,T>
{
private:
  T *numbers;
  bool negativo;

  void complemento2(int number) const;
  void complemento2(void) const;
  int get_int(int pos) const;
  char set_char(int &numero, int &carry = 0) const;
  int val_abs_(void) const;
  bool get_negativo(void) const;
  bool check_overflow(int val_number1, int val_number2, bool operacion) const;
  bool check_underflow(int val_number1, int val_number2) const;

  void reservar(void);
  void liberar(void);

  Number<N, 2, T> Suma(Number<N, 2, T> &number1, Number<N, 2, T> &SumaT) const;
  Number<N, 2, T> Resta(Number<N, 2, T> &number1, Number<N, 2, T> &RestaT) const;
  Number<N, 2, T> Multiplicacion(Number<N, 2, T> &number1, Number<N, 2, T> &MultiplicacionT) const;

public:
  Number(int number = 0);
  Number(const Number<N, 2, T> &Number);
  ~Number();

  std::ostream &write(std::ostream &os) const;

  Number<N, 2, T> operator=(Number<N, 2, T> Number1);
  Number<N, 2, T> operator+(Number<N, 2, T> number1);
  Number<N, 2, T> operator-(Number<N, 2, T> number1);
  Number<N, 2, T> operator*(Number<N, 2, T> number1);
};

class number_t_exception_t : public std::exception
{
};

class overflow_set_exception : public number_t_exception_t
{
public:
  virtual const char *what(void) const throw()
  {
    return "\nSe ha producido overflow en la operación.\n";
  }
};

class underflow_set_exception : public number_t_exception_t
{
public:
  virtual const char *what(void) const throw()
  {
    return "\nSe ha producido underflow en la operación.\n";
  }
};

#include "../src/Number.tpp"
