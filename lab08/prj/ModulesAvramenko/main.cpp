#include <cmath>
#include <stdexcept>

double s_calculation(double x, double y, double z) {
    // Перевірка на можливість ділення на нуль
    if (std::abs(x + y) < 1e-9) {
        throw std::invalid_argument("Помилка: ділення на нуль у виразі yz/(x+y)");
    }

    // Обчислення аргументу під квадратним коренем
    double sqrt_argument = std::abs(y * z / (x + y));

    // Перевірка, що sqrt_argument не дорівнює нулю, інакше відбудеться ділення на нуль
    if (std::abs(sqrt_argument) < 1e-9) {
        throw std::domain_error("Помилка: обчислення sqrt(0) викликає ділення на 0 в основному виразі");
    }

    // Обчислення виразу
    double result = std::sin(x) / std::sqrt(sqrt_argument) + 3 * std::pow(y, 5);
    return result;
}
