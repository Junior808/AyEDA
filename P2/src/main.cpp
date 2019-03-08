#include "../include/Number.hpp"

template <size_t N, size_t B, typename T = char>
void testNumber(int number1, int number2)
{

    Number<N, B, T> Numero1(number1);
    Number<N, B, T> Numero2(number2);
    try
    {
        Numero1.write(std::cout);
        Numero2.write(std::cout);

        Number<N, B, T> Operaciones;

        std::cout << "\nSuma:\n";
        Operaciones = Numero1 + Numero2;
        Operaciones.write(std::cout);

        std::cout << "\nResta:\n";
        Operaciones = Numero1 - Numero2;
        Operaciones.write(std::cout);

        std::cout << "\nMultiplicación:\n";
        Operaciones = Numero1 * Numero2;
        Operaciones.write(std::cout);
        std::cout << '\n';
    }
    /*catch (number_t_exception_t &e)
    {
        std::cerr << e.what() << '\n';
    }*/
    catch (overflow_set_exception &e)
    {
        std::cerr << e.what() << '\n';
        //Comentado porque no funciona. :)
        //Number<N + 1, B> Overflow;
        //Overflow = (Number<N+1, B>)Numero1 + (Number<N+1, B>)Numero2;
        // Overflow.write(std::cout);
    }
}

int main()
{
    //
    // int a,b;

    // std::cout << "\nIntroduzca el primer número:";
    // std::cin >> a;
    // std::cout << "Introduzca el segundo número:";
    // std::cin >> b;
    //

    std::cout << "\nBinario.\n\n";
    testNumber<5, 2>(-7, 2);

    std::cout << "\nOctal.\n\n";
    testNumber<4, 8>(12, 9);

    std::cout << "\nDecimal.\n\n";
    testNumber<5, 10>(2, 5);

    std::cout << "\nHexadecimal.\n\n";
    testNumber<10, 16>(28, 3);

    return 0;
}