#include "../include/Number.hpp"

template <size_t N, size_t B, typename T>
Number<N, B, T>::Number(int number) : numbers(NULL)
{
    if (number < 0)
    {
        negativo = true;
        number = fabs(number);
    }
    else
        negativo = false;

    reservar();

    to_base(number);
}

template <size_t N, size_t B, typename T>
Number<N, B, T>::Number(const Number<N, B, T> &Number1) : numbers(NULL),
                                                          negativo(Number1.negativo)
{
    reservar();

    for (int i = 0; i < N; i++)
        numbers[i] = Number1.numbers[i];
}

template <size_t N, size_t B, typename T>
Number<N, B, T>::Number(const Number<N - 1, B, T> &Number1) : numbers(NULL)
{
    reservar();

    for (int i = 0; i < N; i++)
        numbers[i] = Number1.get_number(i);
}

template <size_t N, size_t B, typename T>
Number<N, B, T>::~Number()
{
    liberar();
}

template <size_t N, size_t B, typename T>
void Number<N, B, T>::reservar()
{
    numbers = new T[N];
}

template <size_t N, size_t B, typename T>
void Number<N, B, T>::liberar()
{
    if (numbers)
        delete[] numbers;
}

template <size_t N, size_t B, typename T>
Number<N, B, T> Number<N, B, T>::operator=(Number<N, B, T> Number1)
{
    liberar();
    reservar();

    for (int i = 0; i < N; i++)
        numbers[i] = Number1.numbers[i];

    negativo = Number1.negativo;

    return *this;
}

template <size_t N, size_t B, typename T>
Number<N, B, T> Number<N, B, T>::operator+(Number<N, B, T> Number1)
{
    Number<N, B, T> SumaT;

    int v_abs = val_abs_();
    int v_abs_number1 = Number1.val_abs_();

    if (check_overflow(v_abs, v_abs_number1, false))
        throw overflow_set_exception();

    if (get_negativo() != Number1.get_negativo())
    {
        if (val_abs_() < Number1.val_abs_())
        {
            SumaT.negativo = Number1.get_negativo();
            return Number1.Resta(*this, SumaT);
        }
        else
        {
            SumaT.negativo = get_negativo();
            return Resta(Number1, SumaT);
        }
    }
    else
    {
        SumaT.negativo = get_negativo();
        return Suma(Number1, SumaT);
    }
}

template <size_t N, size_t B, typename T>
Number<N, B, T> Number<N, B, T>::operator-(Number<N, B, T> Number1)
{
    Number<N, B, T> RestaT;

    int v_abs = val_abs_();
    int v_abs_number1 = Number1.val_abs_();

    if (check_underflow(v_abs, v_abs_number1))
        throw underflow_set_exception();

    if (get_negativo() != Number1.get_negativo())
    {
        if (val_abs_() < Number1.val_abs_())
        {
            RestaT.negativo = get_negativo();
            return Number1.Suma(*this, RestaT);
        }
        else
        {
            RestaT.negativo = get_negativo();
            return Suma(Number1, RestaT);
        }
    }
    else
    {
        if (val_abs_() < Number1.val_abs_())
        {
            RestaT.negativo = !get_negativo();
            return Number1.Resta(*this, RestaT);
        }
        else
        {
            RestaT.negativo = get_negativo();
            return Resta(Number1, RestaT);
        }
    }
}

template <size_t N, size_t B, typename T>
Number<N, B, T> Number<N, B, T>::operator*(Number<N, B, T> Number1)
{
    Number<N, B, T> MultiplicacionT;

    int signo_number = get_negativo(), signo_number1 = Number1.get_negativo();

    if (check_overflow(val_abs_(), Number1.val_abs_(), true))
        throw overflow_set_exception();

    if (negativo == 1 && Number1.negativo == 1) // (-)*(-) = +
        MultiplicacionT.negativo = !get_negativo();

    else if (negativo != Number1.negativo) // (+)*(-) = -
        MultiplicacionT.negativo = true;

    else if (negativo == 0 && Number1.negativo == 0) // (+)*(+) = +
        MultiplicacionT.negativo = get_negativo();

    return Multiplicacion(Number1, MultiplicacionT);
}

template <size_t N, size_t B, typename T>
Number<N + 1, B, T> Number<N, B, T>::operator()()
{
    Number<N + 1, B, T> Overflow;
}

template <size_t N, size_t B, typename T>
void Number<N, B, T>::to_base(int number)
{
    int resto = 0;
    for (int i = 0; i < N; i++)
    {
        resto = number % B;
        if (resto >= 10)
            numbers[i] = resto - 10 + 'A';
        else
            numbers[i] = resto + '0';

        number /= B;
    }
}

template <size_t N, size_t B, typename T>
std::ostream &Number<N, B, T>::write(std::ostream &os) const
{
    if (negativo)
        std::cout << "- ";
    else
        std::cout << "+ ";

    for (int i = N - 1; i >= 0; i--)
        std::cout << numbers[i] << ' ';

    std::cout << '\n';
    return os;
}

template <size_t N, size_t B, typename T>
int Number<N, B, T>::get_number(int i) const
{
    return numbers[i];
}

template <size_t N, size_t B, typename T>
int Number<N, B, T>::get_int(int pos) const
{
    char letra = numbers[pos];
    int conv;

    if (letra > 57)
        conv = letra - 65 + 10;
    else
    {
        conv = numbers[pos] - '0';
    }

    return conv;
}
template <size_t N, size_t B, typename T>
char Number<N, B, T>::set_char(int &numero, int &carry) const
{
    char digito;
    if (B > 10)
    {
        if (numero >= B)
        {
            numero = numero - B;
            carry = 1;
            return digito = numero + '0';
        }
        if (numero >= 10)
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
        if (numero >= B)
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

template <size_t N, size_t B, typename T>
int Number<N, B, T>::val_abs_() const
{
    //Saber cual es el mayor.
    //Diferente signo: al mayor le restamos el menor.
    int val_abs = 0;
    for (int i = 0; i < N; i++)
        val_abs += (get_int(i) * int(pow(B, i)));

    return val_abs;
}

template <size_t N, size_t B, typename T>
bool Number<N, B, T>::get_negativo() const
{
    return negativo;
}

template <size_t N, size_t B, typename T>
bool Number<N, B, T>::check_overflow(int val_number1, int val_number2, bool operacion) const
{
    //operacion = false ---> Suma
    //operacion = true  ---> Multiplicacion
    if (!operacion)
        return (pow(B, N) - 1 < (val_number1 + val_number2)) ? true : false;
    else
        return (pow(B, N) - 1 < (val_number1 * val_number2)) ? true : false;
}

template <size_t N, size_t B, typename T>
bool Number<N, B, T>::check_underflow(int val_number1, int val_number2) const
{
    return (pow(B, N) < (val_number1 + val_number2)) ? true : false;
}

template <size_t N, size_t B, typename T>
Number<N, B, T> Number<N, B, T>::Suma(Number<N, B, T> &number1, Number<N, B, T> &SumaT) const
{
    int carry = 0, numero1, numero2, suma;
    for (int i = 0; i < N; i++)
    {
        numero1 = number1.get_int(i);
        numero2 = get_int(i);
        suma = numero2 + numero1 + carry;

        SumaT.numbers[i] = set_char(suma, carry);
    }
    return SumaT;
}

template <size_t N, size_t B, typename T>
Number<N, B, T> Number<N, B, T>::Resta(Number<N, B, T> &number1, Number<N, B, T> &RestaT) const
{
    int carry = 0, numero1, numero2, resta;
    for (int i = 0; i < N; i++)
    {
        numero1 = number1.get_int(i);
        numero2 = get_int(i);
        resta = numero2 - numero1 - carry;

        if (resta < 0)
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

template <size_t N, size_t B, typename T>
Number<N, B, T> Number<N, B, T>::Multiplicacion(Number<N, B, T> &number1, Number<N, B, T> &MultiplicacionT) const
{
    int multiplicador = number1.val_abs_();

    for (int i = 0; i < multiplicador; i++)
        MultiplicacionT = Suma(MultiplicacionT, MultiplicacionT);

    return MultiplicacionT;
}

//                          //
//                          //
//                          //
//                          //
// Especialización Binario  //
//                          //
//                          //
//                          //
//                          //

template <size_t N, typename T>
Number<N, 2, T>::Number(int number) : numbers(NULL)
{
    if (number < 0)
    {
        negativo = true;
        number = fabs(number);
    }
    else
        negativo = false;

    reservar();

    complemento2(number);
}

template <size_t N, typename T>
Number<N, 2, T>::Number(const Number<N, 2, T> &Number1) : numbers(NULL),
                                                          negativo(Number1.negativo)
{
    reservar();

    for (int i = 0; i < N; i++)
        numbers[i] = Number1.numbers[i];
}

template <size_t N, typename T>
Number<N, 2, T>::~Number()
{
    liberar();
}

template <size_t N, typename T>
void Number<N, 2, T>::reservar()
{
    numbers = new T[N];
}

template <size_t N, typename T>
void Number<N, 2, T>::liberar()
{
    if (numbers)
        delete[] numbers;
}

template <size_t N, typename T>
Number<N, 2, T> Number<N, 2, T>::operator=(Number<N, 2, T> Number1)
{
    liberar();
    reservar();

    for (int i = 0; i < N; i++)
        numbers[i] = Number1.numbers[i];

    negativo = Number1.negativo;

    return *this;
}

template <size_t N, typename T>
Number<N, 2, T> Number<N, 2, T>::operator+(Number<N, 2, T> Number1)
{
    Number<N, 2, T> SumaT;

    int v_abs = val_abs_();
    int v_abs_number1 = Number1.val_abs_();

    if (check_overflow(v_abs, v_abs_number1, false))
        throw overflow_set_exception();

    if (get_negativo() != Number1.get_negativo())
    {
        if (val_abs_() < Number1.val_abs_())
        {
            SumaT.negativo = Number1.get_negativo();
            return Number1.Suma(*this, SumaT);
        }
        else
        {
            SumaT.negativo = get_negativo();
            return Number1.Suma(*this, SumaT);
        }
    }
    else
    {
        SumaT.negativo = get_negativo();
        return Suma(Number1, SumaT);
    }
}

template <size_t N, typename T>
Number<N, 2, T> Number<N, 2, T>::operator-(Number<N, 2, T> Number1)
{
    Number<N, 2, T> RestaT;

    int v_abs = val_abs_();
    int v_abs_number1 = Number1.val_abs_();

    if (check_underflow(v_abs, v_abs_number1))
        throw underflow_set_exception();

    if (get_negativo() != Number1.get_negativo())
    {
        if (val_abs_() < Number1.val_abs_())
        {
            RestaT.negativo = get_negativo();
            RestaT = Number1.Resta(*this, RestaT);
            RestaT.complemento2();
            return RestaT;
        }
        else
        {
            RestaT.negativo = get_negativo();
            return Resta(Number1, RestaT);
        }
    }
    else
    {
        if (val_abs_() < Number1.val_abs_())
        {
            RestaT.negativo = !get_negativo();
            return Number1.Resta(*this, RestaT);
        }
        else
        {
            RestaT.negativo = get_negativo();
            return Resta(Number1, RestaT);
        }
    }
}

template <size_t N, typename T>
Number<N, 2, T> Number<N, 2, T>::operator*(Number<N, 2, T> Number1)
{
    Number<N, 2, T> MultiplicacionT;

    int signo_number = get_negativo(), signo_number1 = Number1.get_negativo();

    if (check_overflow(val_abs_(), Number1.val_abs_(), true))
        throw overflow_set_exception();

    if (negativo == 1 && Number1.negativo == 1) // (-)*(-) = +
        MultiplicacionT.negativo = !get_negativo();

    else if (negativo != Number1.negativo) // (+)*(-) = -
        MultiplicacionT.negativo = true;

    else if (negativo == 0 && Number1.negativo == 0) // (+)*(+) = +
        MultiplicacionT.negativo = get_negativo();

    return Multiplicacion(Number1, MultiplicacionT);
}

template <size_t N, typename T>
void Number<N, 2, T>::complemento2(int number) const
{
    int resto = 0;
    for (int i = 0; i < N; i++)
    {
        resto = number % 2;
        if (!negativo)
            numbers[i] = resto + '0';
        else
        {
            resto = (resto == 0) ? 1 : 0;
            numbers[i] = resto + '0';
        }
        number /= 2;
    }

    if (negativo)
    {
        for (int i = 0; i < N; i++)
        {
            if (numbers[i] == '1')
                numbers[i] = '0';
            else
            {
                numbers[i] = '1';
                break;
            }
        }
    }
}

template <size_t N, typename T>
void Number<N, 2, T>::complemento2(void) const
{
    int pos = 0;
    for (; pos < N; pos++)
        if (numbers[pos] == '1')
            break;

    for (int i = pos + 1; i < N; i++)
    {
        if (numbers[i] == '1')
            numbers[i] = '0';
        else
            numbers[i] = '1';
    }
}

template <size_t N, typename T>
std::ostream &Number<N, 2, T>::write(std::ostream &os) const
{
    for (int i = N - 1; i >= 0; i--)
        std::cout << numbers[i] << ' ';

    std::cout << '\n';
    return os;
}

template <size_t N, typename T>
int Number<N, 2, T>::get_int(int pos) const
{
    int conv = numbers[pos] - '0';
    return conv;
}
template <size_t N, typename T>
char Number<N, 2, T>::set_char(int &numero, int &carry) const
{
    char digito;
    if (numero >= 2)
    {
        numero = numero - 2;
        carry = 1;
        return digito = numero + '0';
    }
    else
    {
        carry = 0;
        return digito = numero + '0';
    }
}

template <size_t N, typename T>
int Number<N, 2, T>::val_abs_() const
{
    //Saber cual es el mayor.
    //Diferente signo: al mayor le restamos el menor.
    int val_abs = 0;
    for (int i = 0; i < N; i++)
        val_abs += (get_int(i) * int(pow(2, i)));

    return val_abs;
}

template <size_t N, typename T>
bool Number<N, 2, T>::get_negativo() const
{
    return negativo;
}

template <size_t N, typename T>
bool Number<N, 2, T>::check_overflow(int val_number1, int val_number2, bool operacion) const
{
    //operacion = false ---> Suma
    //operacion = true  ---> Multiplicacion
    if (!operacion)
        return (pow(2, N) - 1 < (val_number1 + val_number2)) ? true : false;
    else
        return (pow(2, N) - 1 < (val_number1 * val_number2)) ? true : false;
}

template <size_t N, typename T>
bool Number<N, 2, T>::check_underflow(int val_number1, int val_number2) const
{
    return (pow(2, N) < (val_number1 + val_number2)) ? true : false;
}

template <size_t N, typename T>
Number<N, 2, T> Number<N, 2, T>::Suma(Number<N, 2, T> &number1, Number<N, 2, T> &SumaT) const
{
    int carry = 0, numero1, numero2, suma;
    for (int i = 0; i < N; i++)
    {
        numero1 = number1.get_int(i);
        numero2 = get_int(i);
        suma = numero2 + numero1 + carry;

        SumaT.numbers[i] = set_char(suma, carry);
    }
    return SumaT;
}

template <size_t N, typename T>
Number<N, 2, T> Number<N, 2, T>::Resta(Number<N, 2, T> &number1, Number<N, 2, T> &RestaT) const
{
    int carry = 0, numero1, numero2, resta;
    for (int i = 0; i < N; i++)
    {
        numero1 = number1.get_int(i);
        numero2 = get_int(i);
        resta = numero2 - numero1 - carry;

        if (resta < 0)
        {
            resta = 2 - fabs(resta);
            RestaT.numbers[i] = set_char(resta, carry);
            carry = 1;
        }
        else
            RestaT.numbers[i] = set_char(resta, carry);
    }
    return RestaT;
}

template <size_t N, typename T>
Number<N, 2, T> Number<N, 2, T>::Multiplicacion(Number<N, 2, T> &number1, Number<N, 2, T> &MultiplicacionT) const
{
    int multiplicador = number1.val_abs_();

    for (int i = 0; i < multiplicador; i++)
        MultiplicacionT = Suma(MultiplicacionT, MultiplicacionT);

    return MultiplicacionT;
}