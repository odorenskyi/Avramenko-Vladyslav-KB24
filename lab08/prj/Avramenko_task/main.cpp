#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <string>
#include "ModulesAvramenko.h" // Підключення заголовкового файлу з реалізацією s_calculation()

// 8.2.1. Функція повертає інформацію про розробника
void developer_info() {
    std::cout << "╔══════════════════════════════════════╗\n";
    std::cout << "║   Авраменко Владислав                ║\n";
    std::cout << "╠═══© All rights reserved══════════════╣\n";
    std::cout << "╚══════════════════════════════════════╝\n";
}

// 8.2.2. Функція обчислює логічний вираз a+1 < b+3 та повертає 1 (true) або 0 (false)
int logical_expression_result(char a, char b) {
    // Використовуємо ASCII-коди символів
    return ((static_cast<int>(a) + 1) < (static_cast<int>(b) + 3)) ? 1 : 0;
}

// 8.2.3. Функція виводить значення x, y, z у десятковому та шістнадцятковому форматах,
// а також обчислене значення S за допомогою s_calculation()
void print_numbers_and_S(double x, double y, double z) {
    // Вивід чисел у десятковій системі числення
    std::cout << "Десяткове представлення:" << std::endl;
    std::cout << "x = " << std::dec << x << ", y = " << y << ", z = " << z << std::endl;

    // Вивід чисел у шістнадцятковій системі числення
    std::cout << "Шістнадцяткове представлення:" << std::endl;
    std::cout << "x = " << std::hex << static_cast<int>(x)
              << ", y = " << static_cast<int>(y)
              << ", z = " << static_cast<int>(z) << std::endl;
    std::cout << std::dec; // повернення до десяткового формату

    // Обчислення S за допомогою s_calculation()
    try {
        double S = s_calculation(x, y, z);
        std::cout << "Обчислене значення S = " << S << std::endl;
    }
    catch (const std::exception& ex) {
        std::cout << "Помилка при обчисленні S: " << ex.what() << std::endl;
    }
}

int main() {
    double x, y, z;
    char a, b;

    // Послідовне введення даних
    std::cout << "Введіть значення x, y, z: ";
    std::cin >> x >> y >> z;

    std::cout << "Введіть символи a та b: ";
    std::cin >> a >> b;

    // 8.2.1. Вивід інформації про розробника
    developer_info();

    // 8.2.2. Вивід результату логічного виразу
    std::cout << "Результат виразу a+1 < b+3: " << logical_expression_result(a, b) << std::endl;

    // 8.2.3. Вивід чисел (у десятковій та шістнадцятковій системах) та обчислене значення S
    print_numbers_and_S(x, y, z);

    return 0;
}
