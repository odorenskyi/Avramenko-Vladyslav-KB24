#include <algorithm>
#include <bitset>
#include <cmath>
#include <cctype>
#include <ctime>
#include <fstream>
#include <stdexcept>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

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

// Функція для конвертації натурального числа b у двійковий рядок
string ConvertToBinary(int b) {
    if (b <= 0) return "0";
    string binary = "";
    while (b > 0) {
        binary = to_string(b % 2) + binary;
        b /= 2;
    }
    return binary;
}

// Функція для перевірки точного збігу слова (з урахуванням розділових знаків)
bool ContainsWord(const string& text, const string& word) {
    // Для простоти реалізації використаємо stringstream, розбиваючи текст на токени
    istringstream iss(text);
    string token;
    while (iss >> token) {
        // Видаляємо знаки пунктуації з початку та кінця токена
        while (!token.empty() && ispunct(token.front())) {
            token.erase(token.begin());
        }
        while (!token.empty() && ispunct(token.back())) {
            token.pop_back();
        }
        // Перетворення до нижнього регістру для порівняння
        string tokenLower = token;
        string wordLower = word;
        transform(tokenLower.begin(), tokenLower.end(), tokenLower.begin(), ::tolower);
        transform(wordLower.begin(), wordLower.end(), wordLower.begin(), ::tolower);
        if (tokenLower == wordLower) {
            return true;
        }
    }
    return false;
}

// -------------------
// Реалізація задачі 10.1
// -------------------
// Функція читає вхідний текстовий файл, підраховує символи та перевіряє наявність ключових слів.
// Результати записуються у вихідний файл (якщо файл існує, вміст знищується).
bool processTask10_1(const string& inputFile, const string& outputFile, const string& authorInfo) {
    // Читання вхідного файлу
    ifstream fin(inputFile);
    if (!fin.is_open()) {
        cerr << "Помилка: не вдалося відкрити файл " << inputFile << endl;
        return false;
    }
    stringstream buffer;
    buffer << fin.rdbuf();
    string text = buffer.str();
    fin.close();

    // Підрахунок символів (включаючи пробіли та знаки пунктуації)
    int charCount = text.size();

    // Ключові слова для перевірки
    vector<string> keywords = {"програма", "модуль", "студент", "програміст"};
    // Створення повідомлень для кожного ключового слова
    vector<string> keywordStatus;
    for (const auto& key : keywords) {
        if (ContainsWord(text, key)) {
            keywordStatus.push_back("слово \"" + key + "\" присутнє");
        } else {
            keywordStatus.push_back("слово \"" + key + "\" відсутнє");
        }
    }

    // Відкриваємо вихідний файл для запису (режим перезапису)
    ofstream fout(outputFile, ios::out);
    if (!fout.is_open()) {
        cerr << "Помилка: не вдалося відкрити файл " << outputFile << " для запису." << endl;
        return false;
    }

    // Запис авторської інформації
    fout << "Автор: " << authorInfo << endl;
    // Запис речення з кількістю символів
    fout << "У файлі " << inputFile << " міститься " << charCount << " символів." << endl;
    // Запис статусу ключових слів
    for (const auto& status : keywordStatus) {
        fout << status << "." << endl;
    }

    fout.close();
    return true;
}

// -------------------
// Реалізація задачі 10.2
// -------------------
// Функція відкриває вхідний файл для дозапису та дописує рядок, в якому вказано кількість цифр у файлі,
// а також поточну дату і час дозапису.
bool processTask10_2(const string& inputFile) {
    // Читаємо вміст файлу для підрахунку цифр
    ifstream fin(inputFile);
    if (!fin.is_open()) {
        cerr << "Помилка: не вдалося відкрити файл " << inputFile << " для читання." << endl;
        return false;
    }
    stringstream buffer;
    buffer << fin.rdbuf();
    string text = buffer.str();
    fin.close();

    // Підрахунок цифр
    int digitCount = 0;
    for (char ch : text) {
        if (isdigit(static_cast<unsigned char>(ch))) {
            digitCount++;
        }
    }

    // Отримання поточної дати і часу
    time_t now = time(0);
    char dt[100];
    // Формат: "Дописано dd.mm.yyyy о hh:mm:ss"
    strftime(dt, sizeof(dt), "Дописано %d.%m.%Y о %H:%M:%S", localtime(&now));

    // Відкриваємо файл в режимі дозапису
    ofstream fout(inputFile, ios::app);
    if (!fout.is_open()) {
        cerr << "Помилка: не вдалося відкрити файл " << inputFile << " для дозапису." << endl;
        return false;
    }

    // Формування рядка для дозапису
    fout << endl << "У файлі " << inputFile << " міститься " << digitCount << " цифр." << endl;
    fout << dt << endl;

    fout.close();
    return true;
}

// -------------------
// Реалізація задачі 10.3
// -------------------
// Функція приймає числові значення x, y, z та натуральне число b, викликає функцію s_calculation,
// конвертує число b у двійковий запис та записує результати у вихідний файл.
bool processTask10_3(const string& outputFile, double x, double y, double z, int b) {
    // Виклик функції s_calculation
    double result = s_calculation(x, y, z);

    // Отримання двійкового представлення числа b
    string binaryStr = ConvertToBinary(b);

    // Відкриття вихідного файлу (режим перезапису)
    ofstream fout(outputFile, ios::out);
    if (!fout.is_open()) {
        cerr << "Помилка: не вдалося відкрити файл " << outputFile << " для запису." << endl;
        return false;
    }

    // Запис результатів:
    fout << "Результат роботи функції s_calculation(" << x << ", " << y << ", " << z << ") = " << result << endl;
    fout << "Число " << b << " у двійковому коді: " << binaryStr << endl;

    fout.close();
    return true;
}

// -------------------
// Головна функція (main)
// -------------------
int main() {
    // Демонстрація викликів модулів задач 10.1, 10.2 та 10.3.

    // Задача 10.1
    string inFile10_1 = "Input10_1.txt";   // Ім'я вхідного файлу (створіть його за допомогою текстового редактора)
    string outFile10_1 = "Output10_1.txt";   // Ім'я вихідного файлу
    string authorInfo = "Іван Іваненко, КПІ, Київ, Україна, 2025";
    if (processTask10_1(inFile10_1, outFile10_1, authorInfo)) {
        cout << "Задача 10.1 виконана успішно." << endl;
    }

    // Задача 10.2
    string inFile10_2 = "Input10_2.txt";   // Ім'я вхідного файлу для дописування
    if (processTask10_2(inFile10_2)) {
        cout << "Задача 10.2 виконана успішно." << endl;
    }

    // Задача 10.3
    string outFile10_3 = "Output10_3.txt"; // Ім'я вихідного файлу
    double x = 3.0, y = 4.0, z = 5.0;
    int b = 13;
    if (processTask10_3(outFile10_3, x, y, z, b)) {
        cout << "Задача 10.3 виконана успішно." << endl;
    }

    return 0;
}
