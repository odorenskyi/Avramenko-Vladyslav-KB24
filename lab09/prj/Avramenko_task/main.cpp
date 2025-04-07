#include <iostream>
#include "ModulesAvramenko.h"

// Головна функція для задачі 9.4
int main() {
    char inputSymbol;
    char exitChar;

    do {
        // Запит на введення символу для виконання дії
        std::cout << "Введіть символ для виконання операції:\n"
                     "  'j' - виклик s_calculation()\n"
                     "  'z' - виклик функції задачі 9.1 (оцінка хвилювання моря)\n"
                     "  'х' - виклик функції задачі 9.2 (конвертація температури)\n"
                     "  'c' - виклик функції задачі 9.3 (обчислення за бінарним представленням)\n"
                     "Ваш ввід: ";
        std::cin >> inputSymbol;

        // Обробка введеного символу
        switch (inputSymbol) {
            case 'j':
                double x, y, z;
                std::cout << "Введіть x: ";
                std::cin >> x;
                std::cout << "Введіть y: ";
                std::cin >> y;
                std::cout << "Введіть z: ";
                std::cin >> z;
                std::cout << s_calculation(x, y, z) << std::endl;
                break;
            case 'z': {
                // Виклик функції задачі 9.1: оцінка хвилювання моря
                double waveHeight;
                std::cout << "Введіть висоту хвилі (в метрах): ";
                std::cin >> waveHeight;
                int grade = waveGrade(waveHeight);
                std::cout << "Бали хвилювання моря: " << grade << std::endl;
                break;
            }
            case 'x': {
                // Виклик функції задачі 9.2: конвертація температури з Фаренгейта у Цельсій
                double tF;
                std::cout << "Введіть температуру за Фаренгейтом: ";
                std::cin >> tF;
                double tC = fahrenheitToCelsius(tF);
                std::cout << "Температура в Цельсіях: " << tC << std::endl;
                break;
            }
            case 'c': {
                // Виклик функції задачі 9.3: обчислення за двійковим представленням числа
                unsigned int N;
                std::cout << "Введіть число (від 0 до 65535): ";
                std::cin >> N;
                int result = processBinary(N);
                std::cout << "Результат обчислення: " << result << std::endl;
                break;
            }
            default:
                // Некоректний ввід – видається звуковий сигнал і повідомлення
                std::cout << "Неправильний ввід! \a" << std::endl;
                break;
        }

        // Запит користувача для виходу з програми
        std::cout << "\nДля виходу введіть 'v', 'V' або 'А'. Для продовження – будь-який інший символ: ";
        std::cin >> exitChar;
        std::cout << std::endl;

    } while (exitChar != 'v' && exitChar != 'V' && exitChar != 'A');

    return 0;
}
