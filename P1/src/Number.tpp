#include "../include/Number.hpp"

template<size_t N, size_t B, typename T>
Number<N, B, T>::Number(int number)
{
    numbers.resize(N);
    to_base(number);
}

template<size_t N, size_t B, typename T>
Number<N, B, T>::~Number()
{}

template<size_t N, size_t B, typename T>
void Number<N, B, T>::to_base(int number)
{
    int resto = 0;
    for(int i = 0; i < N; i++)
    {
        resto = number % B;
        if(resto >= 10)
            numbers[i] = resto - 10 + 'A';
        else
            numbers[i] = resto + '0';

        number /= B;
    }
}

template<size_t N, size_t B, typename T>
std::ostream& Number<N, B, T>::write(std::ostream& os) const
{
    for(int i = N-1; i >= 0; i--)
        std::cout << numbers[i] << ' ';

    std::cout << '\n';
    return os;
}

template<size_t N, size_t B, typename T>
int Number<N,B,T>::get_int(int pos) const
{
    char letra = numbers[pos];
    int conv;

    if(letra > 57)
        conv = letra - 65 + 10;
    else
    {
        conv = numbers[pos] - '0';
    }

    return conv;
}
template<size_t N, size_t B, typename T>
char Number<N,B,T>::set_char(int& numero, int& carry) const
{
    char digito;
    if(B > 10)
    {
        if(numero >= B)
        {
            numero = numero - B;
            carry = 1;
            return digito = numero  + '0';
        }
        if(numero >= 10)
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
        if(numero >= B)
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

template<size_t N, size_t B, typename T>
Number<N,B,T> Number<N, B, T>::Suma(Number<N,B,T>& number1) const
{
    Number<N, B, T> SumaT;
    int carry = 0, numero1, numero2, suma;
    for(int i = 0; i < N; i++)
    {
        numero1 = number1.get_int(i);
        numero2 = get_int(i);
        suma = numero2 + numero1 + carry;

        if(suma >= 10)
            SumaT.numbers[i] = set_char(suma, carry);
        else
            SumaT.numbers[i] = set_char(suma, carry);

    }
    return SumaT;
}

template<size_t N, size_t B, typename T>
Number<N,B,T> Number<N, B, T>::Resta(Number<N,B,T>& number1) const
{
    Number<N, B, T> RestaT;
    int carry = 0, numero1, numero2, resta;
    for(int i = 0; i < N; i++)
    {
        numero1 = number1.get_int(i);
        numero2 = get_int(i);
        resta = numero2 - numero1 - carry;

        if(resta < 0)
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

template<size_t N, size_t B, typename T>
Number<N,B,T> Number<N, B, T>::Division(Number<N,B,T>& number1) const
{
    /*Number<N, B, T> DivisionT;
    int divisor = 0;

    for(int i = 0; i < N; i++)
        divisor += (number1.get_int(i) * int(pow(B,i)));

    std::vector<T> copia_numbers = numbers;

    for(int i = 0; i < divisor; i++)
        numbers = Resta(number1);

    DivisionT.numbers = numbers;
    numbers = copia_numbers;

    No funciona :)

   return DivisionT;*/
}

template<size_t N, size_t B, typename T>
Number<N,B,T> Number<N, B, T>::Multiplicacion(Number<N,B,T>& number1) const
{
    Number<N, B, T> MultiplicacionT;
    int multiplicador = 0;

    for(int i = 0; i < N; i++)
        multiplicador += (number1.get_int(i) * int(pow(B,i)));

    for(int i = 0; i < multiplicador; i++)
        MultiplicacionT = Suma(MultiplicacionT);

    return MultiplicacionT;
}
