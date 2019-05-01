#include <iostream>
#include <unistd.h>
#include <vector>
#include "../include/Seleccion.hpp"
#include "../include/ShakeSort.hpp"
#include "../include/HeapSort.hpp"
#include "../include/MergeSort.hpp"
#include "../include/ShellSort.hpp"
#include "../include/DNI.hpp"

void ayuda()
{
    std::cout << "\nMétodos de ordenación.\n";
    std::cout << " 1 - Seleccion.\n";
    std::cout << " 2 - ShakeSort.\n";
    std::cout << " 3 - HeapSort.\n";
    std::cout << " 4 - MergeSo)rt.\n";
    std::cout << " 5 - ShellSort.\n";

    std::cout << "Ejecutando el programa en modo demostración:\n";
    std::cout << "./main    -algoritmo      secuencia\n";
    std::cout << "En caso de que se seleccione el ShellSort habrá que indicar un alfa entre 0 y 1.\n";
    std::cout << "./main    -5      secuencia       alfa\n";
    std::cout << "La secuencia tiene que ser igual o menor que 25.\n";

    std::cout << "Ejecuntado el programa en modo estadístico:\n";
    std::cout << "./main    secuencia       alfa        Nº Pruebas\n";
}

int main(int argc, char *argv[])
{
    int secuencia = 0, pruebas = 0;
    float alfa = 0.0;
#ifdef DEMO
    int command_line;
    P_ordenar<DNI> *metodo;
    while ((command_line = getopt(argc, argv, "1:2:3:4:5:")) != -1)
    {

        switch (command_line)
        {
        case '1':
            std::cout << "\nSeleccion.\n";
            metodo = new Seleccion<DNI>();
            secuencia = atoi(optarg);
            break;
        case '2':
            std::cout << "\nShakeSort.\n";
            metodo = new ShakeSort<DNI>();
            secuencia = atoi(optarg);
            break;
        case '3':
            std::cout << "\nHeapSort.\n";
            metodo = new HeapSort<DNI>();
            secuencia = atoi(optarg);
            break;
        case '4':
            std::cout << "\nMergeSort.\n";
            metodo = new MergeSort<DNI>();
            secuencia = atoi(optarg);
            break;
        case '5':
            secuencia = atoi(argv[2]);
            alfa = atof(argv[3]);
            metodo = new ShellSort<DNI>(alfa);
            std::cout << "\nShellSort con alfa " << alfa << ".\n";
            break;
        default:
            ayuda();
            return 0;
        }
    }

    if (secuencia > 25)
    {
        std::cout << "La secuencia tiene que ser igual o menor que 25. ";
        std::cout << "Se ha reducido a su valor máximo.\n";
        secuencia = 25;
    }

    DNI *vector = new DNI[secuencia];
    for (unsigned i = 0; i < secuencia; i++)
        vector[i] = DNI(i * 20);

    std::cout << "\nVector desordenado.\n";
    for (unsigned i = 0; i < secuencia; i++)
    {
        vector[i].write();
        std::cout << '\t';
    }

    metodo->ordenar(vector, secuencia);

    std::cout << "\nVector ordenado.\n";
    for (unsigned i = 0; i < secuencia; i++)
    {
        vector[i].write();
        std::cout << '\t';
    }

#endif

#ifdef ESTA

    if (argc != 4)
    {
        std::cerr << "No se ha especificado los parámetros necesarios para la ejecución del programa.\n";
        ayuda();
        return 0;
    }
    else
    {

        secuencia = atoi(argv[1]);
        alfa = atof(argv[2]);
        pruebas = atoi(argv[3]);
    }

    std::vector<P_ordenar<DNI> *> metodo_;

    std::vector<std::string> nombres = {"Selección", "SkakeSort", "HeapSort", "MergeSort", "ShellSort"};
    metodo_.resize(nombres.size());

    metodo_[0] = new Seleccion<DNI>;
    metodo_[1] = new ShakeSort<DNI>;
    metodo_[2] = new HeapSort<DNI>;
    metodo_[3] = new MergeSort<DNI>;
    metodo_[4] = new ShellSort<DNI>(alfa);

    std::cout << "\n\t\tPrograma en modo estadística.\n";
    std::cout << "\n\t\t\tMínimo\t\tMedia\t\tMáximo\n";
    for (int bucle_metodos = 0; bucle_metodos < 5; bucle_metodos++)
    {
        contador.reset();
        for (int bucle_pruebas = 0; bucle_pruebas < pruebas; bucle_pruebas++)
        {
            DNI *vector = new DNI[secuencia];
            for (unsigned i = 0; i < secuencia; i++)
                vector[i] = DNI(i);

            contador.start();
            metodo_[bucle_metodos]->ordenar(vector, secuencia);
            contador.end();
        }
        std::cout << nombres[bucle_metodos] << ':';
        contador.mostar();
    }
#endif
}