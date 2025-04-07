#include <iostream>
#include "ModulesAvramenko.h"

using namespace std;

void run_tests() {
    // Тестування задачі 9.1
    double task1_input[10] = {0, 0.1, 0.3, 1.0, 2.0, 3.0, 5.0, 7.0, 10.0, 15.0};
    double task1_expected[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    cout << "Тестування задачі 9.1" << endl;
    cout << "========" << endl;
    for (int i = 0; i < 10; i++) {
        double result = waveGrade(task1_input[i]);
        cout << "Аргумент(-и): " << task1_input[i] << endl
             << "Очікується: " << task1_expected[i] << endl
             << "Отримано: " << result
             << (abs(result - task1_expected[i]) < 0.001 ? " - PASSED" : " - FAILED") << endl
             << "========" << endl;
    }

    // Тестування задачі 9.2
    double task2_input[5] = { 32, 212, 68, -40, 100 };
    double task2_expected[5] = { 0, 100, 20, -40, 37.78 };

    cout << "Тестування задачі 9.2" << endl;
    cout << "========" << endl;
    for (int i = 0; i < 5; i++) {
        double result = fahrenheitToCelsius(task2_input[i]);
        cout << "Аргумент(-и): "
             << task2_input[i];
        cout << endl;
        cout << "Очікується: " << task2_expected[i] << endl
             << "Отримано: " << result
             << (abs(result - task2_expected[i]) < 0.01 ? " - PASSED" : " - FAILED") << endl
             << "========" << endl;
    }

    // Тестування задачі 9.3}
    int task3_input[4] = {2, 1, 9, 0};
    int task3_expected[4] = {15, 1, 2, 0};

    cout << "Тестування задачі 9.3" << endl;
    cout << "========" << endl;
    for (int i = 0; i < 4; i++) {
        int result = processBinary(task3_input[i]);
        cout << "Аргумент(-и): " << task3_input[i] << endl
             << "Очікується: " << task3_expected[i] << endl
             << "Отримано: " << result
             << (result == task3_expected[i] ? " - PASSED" : " - FAILED") << endl
             << "========" << endl;
    }
}

int main()
{
    run_tests();
    return 0;
}
