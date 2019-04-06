#include <iostream>
#include <math.h>
#include "../include/TablaHash.hpp"
#include "../include/DNI.hpp"

#define eps 10E-3
#define nCeldas_ 1000
#define nBloques_ 5
#define factor_ 0.8
#define pruebas_ 5

//Para probar todas las funciones a la vez con los mismos valores
void test_(int nCeldas, int nBloques, int opcion_h, int opcion_g)
{
    fDispersion<DNI> *hx;
    fExplorar<DNI> *gx;
    std::cout << "\n-------------------------------------------------------------------------------------------------------------------------------------------------------\n";

    switch (opcion_h)
    {
    case 1:
        std::cout << "\nMódulo - ";
        hx = new fD_modulo<DNI>(nCeldas);
        break;
    case 2:
        std::cout << "\nSuma - ";
        hx = new fD_suma<DNI>(nCeldas);
        break;
    case 3:
        std::cout << "\nAleatoria - ";
        hx = new fD_aleatoria<DNI>(nCeldas);
        break;
    default:
        std::cerr << "\n\nMétodo de dispersión erróneo.\n";
        return;
        break;
    }

    switch (opcion_g)
    {
    case 1:
        std::cout << "Lineal\n";
        gx = new fE_lineal<DNI>(nCeldas, hx);
        break;
    case 2:
        std::cout << "Cuadrática\n";
        gx = new fE_cuadratica<DNI>(nCeldas, hx);
        break;
    case 3:
        std::cout << "Doble\n";
        gx = new fE_doble<DNI>(nCeldas, hx);
        break;
    case 4:
        std::cout << "Redispersión\n";
        gx = new fE_redisp<DNI>(nCeldas, hx);
        break;
    default:
        std::cerr << "\n\nMétodo de exploración erróneo.\n";
        return;
        break;
    }

    TablaHash<DNI> *Hashing = new TablaHash<DNI>(nCeldas, nBloques, hx, gx);

    int nPruebas = pruebas_, N = 0;
    double factor1 = factor_, factor2 = 0.0;

    N = 2 * (factor1 * nCeldas * nBloques);

    srand(time(NULL));
    DNI *banco = new DNI[N];
    for (int i = 0; i < N; i++)
        banco[i] = (rand() % 1000000 + 99999999);

    int i = 0, x = 0;

    while ((Hashing->insertar(banco[i])) && (fabs(factor2 - factor1) > eps))
    {
        i++;
        factor2 = (double(i) / double(nCeldas * nBloques));
    }

    std::cout << "\nCeldas  Bloques\t\tDispersión\tExploración\tF.Carga\t\tPruebas\n";
    std::cout << nCeldas << "\t" << nBloques << "\t\t" << opcion_h << "\t\t" << opcion_g;
    std::cout << "\t\t" << factor1 << "\t\t" << nPruebas << "\n\n";

    i = 0;
    contador.reset();
    while (i < nPruebas)
    {
        x = rand() % N;
        contador.start();
        Hashing->buscar(banco[x]);
        i++;

        contador.end();
    }

    std::cout << "\t\t\tMínimo\t\tMedio\t\tMáximo\n";
    std::cout << "Busquedas";
    contador.mostar();

    i = 0;
    contador.reset();
    while (i < nPruebas)
    {
        x = rand() % (N - 1);
        //contador.start();
        Hashing->insertar(banco[x + N]);
        i++;

        contador.end();
    }

    std::cout << "Inserción";
    contador.mostar();
}

int main()
{
    int nCeldas = 1000, nBloques = 5, opcion_h = 0, opcion_g = 0;

    //Para probar todas las funciones a la vez con los mismos valores
    // for (int i = 1; i < 4; i++)
    //     for (int j = 1; j < 4; j++)
    //         test_(nCeldas_, nBloques_, i, j);

    fDispersion<DNI> *hx;
    fExplorar<DNI> *gx;

    std::cout << "\nIntroduzca el nº de celdas de la tabla:\n";
    std::cin >> nCeldas;

    std::cout << "Introduzca el nº de bloques por celda:\n";
    std::cin >> nBloques;

    std::cout << "Elija una función de dispersión:\n";
    std::cout << "1 - Módulo.\n";
    std::cout << "2 - Suma.\n";
    std::cout << "3 - Aleatoria.\n";
    std::cin >> opcion_h;

    std::cout << "Elija una función de exploración:\n";
    std::cout << "1 - Lineal.\n";
    std::cout << "2 - Cuadrática.\n";
    std::cout << "3 - Dispersión doble.\n";
    std::cout << "4 - Re-Dispersión.\n";
    std::cin >> opcion_g;

    switch (opcion_h)
    {
    case 1:
        hx = new fD_modulo<DNI>(nCeldas);
        break;
    case 2:
        hx = new fD_suma<DNI>(nCeldas);
        break;
    case 3:
        hx = new fD_aleatoria<DNI>(nCeldas);
        break;
    default:
        std::cerr << "\n\nMétodo de dispersión erróneo.\n";
        return 0;
        break;
    }

    switch (opcion_g)
    {
    case 1:
        gx = new fE_lineal<DNI>(nCeldas, hx);
        break;
    case 2:
        gx = new fE_cuadratica<DNI>(nCeldas, hx);
        break;
    case 3:
        gx = new fE_doble<DNI>(nCeldas, hx);
        break;
    case 4:
        gx = new fE_redisp<DNI>(nCeldas, hx);
        break;
    default:
        std::cerr << "\n\nMétodo de exploración erróneo.\n";
        return 0;
        break;
    }

    TablaHash<DNI> *Hashing = new TablaHash<DNI>(nCeldas, nBloques, hx, gx);

    int nPruebas = 0, N = 0;
    double factor1 = 0.0, factor2 = 0.0;

    std::cout << "\nIntroduzca el factor un factor de carga entre 0 y 1:\n";
    std::cin >> factor1;
    while (factor1 < 0 || factor1 > 1)
    {
        std::cerr << "\nEl factor de carga tiene que estar entre 0 y 1.\n";
        std::cin >> factor1;
    }

    std::cout << "\nIntroduzca el nº de pruebas a realizar:\n";
    std::cin >> nPruebas;

    N = 2 * (factor1 * nCeldas * nBloques);

    srand(time(NULL));
    DNI *banco = new DNI[N];
    for (int i = 0; i < N; i++)
        banco[i] = (rand() % 1000000 + 99999999);

    int i = 0, x = 0;

    while ((Hashing->insertar(banco[i])) && (fabs(factor2 - factor1) > eps))
    {
        i++;
        factor2 = (double(i) / double(nCeldas * nBloques));
    }

    i = 0;
    contador.reset();
    while (i < nPruebas)
    {
        x = rand() % N;
        contador.start();
        Hashing->buscar(banco[x]);
        i++;

        contador.end();
    }

    std::cout << "\t\t\tMínimo\t\tMedio\t\tMáximo\n";
    std::cout << "Busquedas";
    contador.mostar();

    i = 0;
    contador.reset();
    while (i < nPruebas)
    {
        x = rand() % (N - 1);
        //contador.start();         //Hace que se muestren los mismos valores.
        Hashing->insertar(banco[x + N]);
        i++;

        contador.end();
    }

    std::cout << "Inserción";
    contador.mostar();
}
