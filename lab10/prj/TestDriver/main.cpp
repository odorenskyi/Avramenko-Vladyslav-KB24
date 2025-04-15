// TestDriver.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <cctype>
#include <vector>
#include <algorithm>

// Для демонстрації включаємо "реалізації" функцій із ModulesПрізвище.h
// У вашому проекті включіть:
#include "ModulesAvramenko.h"  // Приклад: #include "ModulesПрізвище.h"
// А також налаштуйте компілятор для зв'язку з libModulesПрізвище.a

// *************************************************************
// Тут наведені реалізації функцій для демонстрації тест-драйвера.
// У вашому проекті ці функції можуть бути в окремих модулях.

using namespace std;

struct TestCase10_1 {
    string inputFile;
    string inputContent;
    string outputFile;
    string authorInfo;
    // Очікуваний результат з вихідного файлу (порівнюється як суцільний рядок)
    string expectedOutput;
};

struct TestCase10_2 {
    string inputFile;
    string inputContent;
    // Очікуваний результат містить інформацію про кількість цифр і дату/час (частину перевірити можна через пошук підрядка)
    string expectedSubstring;
};

struct TestCase10_3 {
    string outputFile;
    double x, y, z;
    int b;
    string expectedSubstring; // частина очікуваного виводу, напр., двійкове представлення числа
};

const string LOG_FILE = "TestLog.txt";

// Функція запису рядка в лог-файл
void LogResult(const string& testID, const string& inputData, const string& obtainedResult, bool passed) {
    ofstream log(LOG_FILE, ios::app);
    if (!log.is_open()) {
        cerr << "Помилка відкриття лог-файлу." << endl;
        return;
    }
    log << "Test Case: " << testID << "\n";
    log << "Вхідні дані: " << inputData << "\n";
    log << "Отриманий результат:\n" << obtainedResult << "\n";
    log << "Статус тесту: " << (passed ? "PASSED" : "FAILED") << "\n";
    log << "-------------------------------------\n";
    log.close();
}

// Функція зчитування файлу повністю у рядок
string ReadFileContent(const string& filename) {
    ifstream fin(filename);
    if (!fin.is_open()) return "";
    stringstream ss;
    ss << fin.rdbuf();
    fin.close();
    return ss.str();
}

// ****************************************************************
// Основна функція тестового драйвера
// ****************************************************************
int main() {
    // Очищення лог-файлу
    ofstream log(LOG_FILE, ios::out);
    log.close();

    bool allTestsPassed = true;

    // ====================
    // Тестування задачі 10.1
    // ====================
    vector<TestCase10_1> tests10_1 = {
        { "Input10_1_A.txt",
          "Це тестовий файл для перевірки програми. Він містить інформацію про модуль, студентів та програмістів.",
          "Output10_1_A.txt",
          "Іван Іваненко, КПІ, Київ, Україна, 2025",
          "Автор: Іван Іваненко, КПІ, Київ, Україна, 2025" },
    };

    for (size_t i = 0; i < tests10_1.size(); i++) {
        TestCase10_1 tc = tests10_1[i];
        // Крок А1. Створення вхідного файлу із заданим вмістом
        ofstream fout(tc.inputFile, ios::out);
        fout << tc.inputContent;
        fout.close();

        // Виклик функції
        bool res = processTask10_1(tc.inputFile, tc.outputFile, tc.authorInfo);

        // Крок А3. Зчитування отриманого вихідного файлу
        string obtainedOutput = ReadFileContent(tc.outputFile);
        // Перевіримо, що вивід містить очікувану інформацію (наприклад, частину з авторською інформацією)
        bool passed = res && (obtainedOutput.find(tc.expectedOutput) != string::npos);
        allTestsPassed = allTestsPassed && passed;

        // Протоколювання
        string inputData = "inputFile: " + tc.inputFile + ", authorInfo: " + tc.authorInfo;
        LogResult("10.1_TC" + to_string(i+1), inputData, obtainedOutput, passed);
        cout << "Test 10.1_TC" << i+1 << ": " << (passed ? "PASSED" : "FAILED") << "\n";
    }

    // ====================
    // Тестування задачі 10.2
    // ====================
    vector<TestCase10_2> tests10_2 = {
        { "Input10_2_A.txt",
          "Лабораторна робота з базових технологій 12345",
          "У файлі Input10_2_A.txt міститься 5 цифр." }
    };

    for (size_t i = 0; i < tests10_2.size(); i++) {
        TestCase10_2 tc = tests10_2[i];
        // Створення файлу
        ofstream fout(tc.inputFile, ios::out);
        fout << tc.inputContent;
        fout.close();

        // Виклик функції
        bool res = processTask10_2(tc.inputFile);

        // Зчитування модифікованого файлу
        string obtainedOutput = ReadFileContent(tc.inputFile);
        bool passed = res && (obtainedOutput.find(tc.expectedSubstring) != string::npos);
        allTestsPassed = allTestsPassed && passed;

        string inputData = "inputFile: " + tc.inputFile;
        LogResult("10.2_TC" + to_string(i+1), inputData, obtainedOutput, passed);
        cout << "Test 10.2_TC" << i+1 << ": " << (passed ? "PASSED" : "FAILED") << "\n";
    }

    // ====================
    // Тестування задачі 10.3
    // ====================
    vector<TestCase10_3> tests10_3 = {
        { "Output10_3_A.txt", 3.0, 4.0, 5.0, 13, "1101" },
        // Можна додати інші тест-кейси...
    };

    for (size_t i = 0; i < tests10_3.size(); i++) {
        TestCase10_3 tc = tests10_3[i];
        // Для задачі 10.3 вхідний файл не потрібен, оскільки результат записується до вихідного файлу.
        bool res = processTask10_3(tc.outputFile, tc.x, tc.y, tc.z, tc.b);
        string obtainedOutput = ReadFileContent(tc.outputFile);
        bool passed = res && (obtainedOutput.find(tc.expectedSubstring) != string::npos);
        allTestsPassed = allTestsPassed && passed;

        string inputData = "x=" + to_string(tc.x) + ", y=" + to_string(tc.y) + ", z=" + to_string(tc.z) + ", b=" + to_string(tc.b);
        LogResult("10.3_TC" + to_string(i+1), inputData, obtainedOutput, passed);
        cout << "Test 10.3_TC" << i+1 << ": " << (passed ? "PASSED" : "FAILED") << "\n";
    }

    cout << "\nУсі тести " << (allTestsPassed ? "пройдені." : "мають помилки.") << "\n";
    return 0;
}
