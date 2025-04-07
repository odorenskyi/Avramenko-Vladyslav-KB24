#include <cmath>
#include <bitset>
#include <string>
#include <algorithm>
#include <stdexcept>

double s_calculation(double x, double y, double z) {
    // Перевірка на можливість ділення на нуль
    if (std::abs(x + y) < 1e-9) {
        return NAN;
        throw std::invalid_argument("Помилка: ділення на нуль у виразі yz/(x+y)");
    }

    // Обчислення аргументу під квадратним коренем
    double sqrt_argument = std::abs(y * z / (x + y));

    // Перевірка, що sqrt_argument не дорівнює нулю, інакше відбудеться ділення на нуль
    if (std::abs(sqrt_argument) < 1e-9) {
        return NAN;
        throw std::domain_error("Помилка: обчислення sqrt(0) викликає ділення на 0 в основному виразі");
    }

    // Обчислення виразу
    double result = std::sin(x) / std::sqrt(sqrt_argument) + 3 * std::pow(y, 5);
    return result;
}

// Функція для задачі 9.1: визначення балу хвилювання за висотою хвилі (в метрах)
int waveGrade(double waveHeight) {
    if (waveHeight == 0.0) {
        return 0; // CALM-GLASSY
    } else if (waveHeight > 0.0 && waveHeight <= 0.1) {
        return 1; // CALM-RIPPLED
    } else if (waveHeight > 0.1 && waveHeight <= 0.5) {
        return 2; // SMOOTH-WAVELET
    } else if (waveHeight > 0.5 && waveHeight <= 1.25) {
        return 3; // SLIGHT
    } else if (waveHeight > 1.25 && waveHeight <= 2.5) {
        return 4; // MODERATE
    } else if (waveHeight > 2.5 && waveHeight <= 4.0) {
        return 5; // ROUGH
    } else if (waveHeight > 4.0 && waveHeight <= 6.0) {
        return 6; // VERY ROUGH
    } else if (waveHeight > 6.0 && waveHeight <= 9.0) {
        return 7; // HIGH
    } else if (waveHeight > 9.0 && waveHeight <= 14.0) {
        return 8; // VERY HIGH
    } else if (waveHeight > 14.0) {
        return 9; // PHENOMENAL
    }
    return -1; // Невизначене значення
}

// Функція для задачі 9.2: конвертація температури з Фаренгейта в Цельсій
double fahrenheitToCelsius(double tF) {
    return (5.0 / 9.0) * (tF - 32);
}

// Функція для задачі 9.3:
// Якщо біт D₁ (другий справа) дорівнює 1, повернути кількість двійкових нулів,
// інакше – суму (кількість) двійкових одиниць у 16-бітовому представленні числа.
int processBinary(unsigned int N) {
    // Отримуємо 16-бітове двійкове представлення числа
    std::string binary = std::bitset<16>(N).to_string();
    // Перевірка значення біта D₁ (індекс 14 зліва, або зсувом вправо на 1)
    return (((N >> 1) & 1) == 1) ?
           static_cast<int>(std::count(binary.begin(), binary.end(), '0')) :  // Якщо D₁ = 1, рахуємо нулі
           static_cast<int>(std::count(binary.begin(), binary.end(), '1'));   // Якщо D₁ = 0, рахуємо одиниці
}
