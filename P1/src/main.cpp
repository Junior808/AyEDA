#include "../include/Number.hpp"

//#define N 10
//#define B 10

template<size_t N, size_t B>
void testNumber(int number1, int number2)
{
    auto rango = pow(B, N);

    std::cout << "\nSu rango es " << rango;
    std::cout << ". Si introduce números cercanos a él no se garantiza que las operaciones sean correctas.\n";

    Number<N, B> Numero1(number1);
    Number<N, B> Numero2(number2);

    Numero1.write(std::cout);
    Numero2.write(std::cout);

    Number<N, B> Operaciones;
    Operaciones = Numero1.Suma(Numero2);
    std::cout << "\nSuma:\n";
    Operaciones.write(std::cout);

    Operaciones = Numero1.Resta(Numero2);
    std::cout << "\nResta:\n";
    Operaciones.write(std::cout);

    Operaciones = Numero1.Multiplicacion(Numero2);
    std::cout << "\nMultiplicación:\n";
    Operaciones.write(std::cout);
}


int main()
{
    /*
    int a,b;

    auto rango = pow(B, N);

    std::cout << "\nSu rango es " << rango;
    std::cout << ". Si introduce números cercanos a él no se garantiza que las operaciones sean correctas.\n";

    std::cout << "\nIntroduzca el primer número:";
    std::cin >> a;
    std::cout << "Introduzca el segundo número:";
    std::cin >> b;
    */
   std::cout << "\nBinario.\n";
   testNumber<10, 2> (12, 5);

   std::cout << "\nOctal.\n";
   testNumber<10, 8> (12, 9);

   std::cout << "\nDecimal.\n";
   testNumber<10,10> (25, 5);

   std::cout << "\nHexadecimal.\n";
   testNumber<10,16> (28, 3);

    return 0;
}