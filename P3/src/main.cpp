#include "../include/Number.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include "../include/calculator.hpp"

using namespace std;

int main() {

  string expr_str( "5 4 + 1 -");
  istringstream expresion(expr_str);

  cout << expr_str << " =\n" << *calculador< Number<4,10> >(expresion) << endl;

  expresion.seekg(0, expresion.beg);
  cout << expr_str << " =\n" << *calculador< Number<8,2> >(expresion) << endl;

  expresion.seekg(0, expresion.beg);
  cout << expr_str << " =\n" << *calculador< Number<4,8> >(expresion) << endl;

  cout << "Postfix expresion = " << *calculador< Number<4,16> >(cin) << endl;

  return 0;
}

// int main()
// {

//     int a, b, base;
//     NumberBase *Number1;
//     NumberBase *Number2;

//     std::cout << "\nIntroduzca el primer número:";
//     std::cin >> a;
//     std::cout << "Introduzca el segundo número:";
//     std::cin >> b;

//     std::cout << "\nSeleccione una base:\n";
//     std::cout << "\n2 - Binario.\n";
//     std::cout << "\n8 - Octal.\n";
//     std::cout << "\n10 - Decimal.\n";
//     std::cout << "\n16 - Hexadecimal.\n";
//     std::cout << "\n0 - Salir.\n";
//     std::cin >> base;

//     switch (base)
//     {
//     case 0:
//         return 0;
//         break;
//     case 2:
//         Number1 = new BinaryNumber<char>(a);
//         Number2 = new BinaryNumber<char>(b);

//         break;

//     case 8:
//         Number1 = new OctalNumber<char>(a);
//         Number2 = new OctalNumber<char>(b);

//         break;

//     case 10:
//         Number1 = new DecimalNumber<char>(a);
//         Number2 = new DecimalNumber<char>(b);

//         break;

//     case 16:
//         Number1 = new HexaNumber<char>(a);
//         Number2 = new HexaNumber<char>(b);

//     default:
//         std::cout << "\nError. Base no aceptada.\n";
//         return 0;
//         break;
//     }

//     try
//     {
//         std::cout << "\nSuma:\n"
//                   << (*Number1) + (*Number2);
//     }
//     catch (overflow_set_exception &e)
//     {
//         std::cerr << e.what() << std::endl;
//     }

//     try
//     {
//         std::cout << "\nResta:\n"
//                   << (*Number1) - (*Number2);
//     }
//     catch (underflow_set_exception &e)
//     {
//         std::cerr << e.what() << std::endl;
//     }

//     try
//     {
//         std::cout << "\nMultiplicación:\n"
//                   << (*Number1) * (*Number2);
//     }
//     catch (overflow_set_exception &e)
//     {
//         std::cerr << e.what() << std::endl;
//     }

//     delete Number1;
//     delete Number2;

//     return 0;
// }