#include <iostream>
#include <vector>
#include "../include/AVL.hpp"
#include "../include/DNI.hpp"
#include "../include/Contador.hpp"

void ayuda()
{
    std::cout << "\n\tAYUDA\n";
    std::cout << "\nCompilar el programa:\n";
    std::cout << "Modo Demostración: g++ -D DEMO main.cpp\n";
    std::cout << "Modo Estadístico: g++ -D ESTA main.cpp\n";
    std::cout << "Ejecución del programa en modo demostración:\n";
    std::cout << "./main\n";
    std::cout << "Ejecución del programa en modo estadístico:\n";
    std::cout << "./main    Tamaño_del_banco    Nº_Pruebas     Semilla\n";
}

int main(int argc, char const *argv[])
{
    int N = 0, nPruebas = 0, seed = 0;
    AVL<DNI> arbol;
    DNI clave;

#ifdef DEMO
    bool salir = false;
    int operacion = 0, dato = 0, imprimir = 4;
    while (!salir)
    {
        std::cout << "\n¿Qué desea hacer?\n";
        std::cout << "[0] Salir.\n";
        std::cout << "[1] Insertar clave.\n";
        std::cout << "[2] Eliminar clave.\n";
        std::cout << "[3] Mostrar arbol.\n";
        std::cin >> operacion;
        switch (operacion)
        {
        case 0:
            salir = true;
            break;
        case 1:
            std::cout << "\nInsertar: ";
            std::cin >> dato;
            clave = dato;

            arbol.insertar(clave);
            arbol.write(4);
            break;
        case 2:
            std::cout << "\nEliminar: ";
            std::cin >> dato;
            clave = dato;

            arbol.eliminar(clave);
            arbol.write(4);
            break;
        case 3:
            std::cout << "\n[1] Preorden.\n";
            std::cout << "[2] Inorden.\n";
            std::cout << "[3] Postorden.\n";
            std::cout << "[4] Por niveles.\n";
            std::cin >> imprimir;
            arbol.write(imprimir);
            break;
        default:
            std::cout << "\nOperación incorrecta.\n";
            return 0;
        }
    }
#endif

#ifdef ESTA

    if (argc != 4)
    {
        ayuda();
        return 1;
    }
    else
    {
        N = atoi(argv[1]);
        nPruebas = atoi(argv[2]);
        seed = atoi(argv[3]);
    }

    std::vector<DNI> banco;
    srand(seed);

    for (int i = 0; i < N * 2; i++)
        banco.push_back(DNI(10000000 + (rand() % 60000000)));

    for (int i = 0; i < N; i++)
        arbol.insertar(banco[i]);

    arbol.write(4);

    contador.reset();

    for (int i = 0; i < nPruebas; i++)
    {
        contador.start();
        arbol.buscar(banco[rand() % N]);
        contador.end();
    }

    std::cout << "\n\nTamaño del banco: " << N;
    std::cout << "\tNº de pruebas: " << nPruebas << "\n";

    std::cout << "\n\t\t\tBúsqueda.\n";
    contador.mostrar();

    contador.reset();

    for (int i = 0; i < nPruebas; i++)
    {
        contador.start();
        arbol.buscar(banco[N + rand() % N]);
        contador.end();
    }

    std::cout << "\n\t\t\tInsercción.\n";
    contador.mostrar();

#endif
}