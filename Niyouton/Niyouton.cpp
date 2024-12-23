#include <iostream>
#include <vector>
#include <cmath>


double factorial(int n);
double interpolation(const std::vector<double>& x, const std::vector<double>& F, double x_value);

int main() 
{

    setlocale(LC_ALL, "RU");

    std::vector<double> x = { 1.05, 1.06, 1.07, 1.08, 1.09, 1.10, 1.11 };
    std::vector<double> F = { 0.04879, 0.058269, 0.067659, 0.076961, 0.086178, 0.09531, 0.10436 };

    double x_value = 1.065;

    double result = interpolation(x, F, x_value);
    std::cout << "ln(" << x_value << ") = " << result << std::endl;
    std::cout << "ln(" << x_value << ") = " << log(x_value) << std::endl;

    return 0;
}

// Функция для вычисления факториала
double factorial(int n) 
{
    if (n == 0) return 1;
    double result = 1;
    for (int i = 1; i <= n; i++) 
    {
        result *= i;
    }
    return result;
}

// Функция для интерполяции по формулам Ньютона
double interpolation(const std::vector<double>& x, const std::vector<double>& F, double x_value)
{
    int n = x.size();
    std::vector<std::vector<double>> delta(n, std::vector<double>(n));

    // Заполнение первого столбца конечных разностей
    for (int i = 0; i < n; i++)
    {
        delta[i][0] = F[i];
    }

    // Вычисление конечных разностей
    for (int j = 1; j < n; j++) 
    {
        for (int i = 0; i < n - j; i++)
        {
            delta[i][j] = delta[i + 1][j - 1] - delta[i][j - 1];
        }
    }

    // Вычисление значения интерполяционного многочлена
    double result = delta[0][0];
    for (int i = 1; i < n; i++) 
    {
        double term = delta[0][i];
        for (int j = 0; j < i; j++)
        {
            term *= (x_value - x[j]);
        }
        result += term / factorial(i);
    }

    return result;
}