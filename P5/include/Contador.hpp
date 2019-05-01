#pragma once

#define MAX 99999

class Contador
{
  private:
    int minimo;
    int media;
    int maximo;
    int acumulador;
    int num_pruebas;
    int cuenta;

  public:
    Contador();
    ~Contador();

    void reset();
    void start();
    void end();
    void mostar();

    int operator++();
};

Contador::Contador()
{
    reset();
}

Contador::~Contador()
{
}

void Contador::reset()
{
    minimo = MAX;
    media = 0;
    maximo = 0;
    acumulador = 0;
    num_pruebas = 0;
    cuenta = 0;
}

void Contador::start()
{
    //acumulador = 0;
    cuenta = 0;
}

void Contador::end()
{
    if (cuenta < minimo)
        minimo = cuenta;
    if (cuenta > maximo)
        maximo = cuenta;

    acumulador += cuenta;
    num_pruebas++;
}

void Contador::mostar()
{
    media = acumulador/num_pruebas;
    std::cout << "\t\t" << minimo << "\t\t" << media << "\t\t" << maximo << "\n";
}

int Contador::operator++()
{
    return cuenta++;
}