#pragma once

#define MAX 99999

class Contador
{
  private:
    int minimo;
    int media;
    int maximo;
    int acumulador;

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
}

void Contador::start()
{
    acumulador = 0;
}

void Contador::end()
{
    if (acumulador < minimo)
        minimo = acumulador;
    if (acumulador > maximo)
        maximo = acumulador;
    media = (minimo + maximo) / 2;
}

void Contador::mostar()
{
    std::cout << "\t\t" << minimo << "\t\t" << media << "\t\t" << maximo << "\n";
}

int Contador::operator++()
{
    return acumulador++;
}