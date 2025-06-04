#include "struct_type_project_9.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

EducationalInstitution* searchByCode(EducationalInstitution* head, int code) {
    if (head == nullptr) {
        cout << "Реєстр порожній!" << endl;
        return nullptr;
    }

    EducationalInstitution* current = head;

    while (current != nullptr) {
        if (current->edeboCode == code) {
            cout << "\n=== ЗНАЙДЕНО ЗАПИС ===" << endl;
            displaySingleRecord(current);
            return current;
        }
        current = current->next;
    }

    cout << "Запис з кодом ЄДЕБО " << code << " не знайдено в реєстрі." << endl;
    return nullptr;
}

void displayRegistry(EducationalInstitution* head, const string& outputFile) {
    if (head == nullptr) {
        string message = "Реєстр порожній!";
        if (outputFile.empty()) {
            cout << message << endl;
        } else {
            ofstream file(outputFile);
            if (file.is_open()) {
                file << message << endl;
                file.close();
                cout << "Повідомлення записано у файл " << outputFile << endl;
            } else {
                cout << "Помилка створення файлу " << outputFile << endl;
            }
        }
        return;
    }

    if (outputFile.empty()) {
        // Виведення на екран
        cout << "\n" << string(80, '=') << endl;
        cout << "           РЕЄСТР СУБ'ЄКТІВ ОСВІТНЬОЇ ДІЯЛЬНОСТІ" << endl;
        cout << "                    ЗАКЛАДИ ВИЩОЇ ОСВІТИ" << endl;
        cout << string(80, '=') << endl;

        EducationalInstitution* current = head;
        int count = 1;

        while (current != nullptr) {
            cout << "\n--- ЗАПИС № " << count << " ---" << endl;
            displaySingleRecord(current);
            current = current->next;
            count++;
        }

        cout << "\nВсього записів у реєстрі: " << (count - 1) << endl;
        cout << string(80, '=') << endl;
    } else {
        // Виведення у файл
        ofstream file(outputFile);
        if (!file.is_open()) {
            cout << "Помилка створення файлу " << outputFile << endl;
            return;
        }

        file << string(80, '=') << endl;
        file << "           РЕЄСТР СУБ'ЄКТІВ ОСВІТНЬОЇ ДІЯЛЬНОСТІ" << endl;
        file << "                    ЗАКЛАДИ ВИЩОЇ ОСВІТИ" << endl;
        file << string(80, '=') << endl;

        EducationalInstitution* current = head;
        int count = 1;

        while (current != nullptr) {
            file << "\n--- ЗАПИС № " << count << " ---" << endl;
            displaySingleRecordToFile(current, file);
            current = current->next;
            count++;
        }

        file << "\nВсього записів у реєстрі: " << (count - 1) << endl;
        file << string(80, '=') << endl;

        file.close();
        cout << "Реєстр успішно експортовано у файл " << outputFile << endl;
        cout << "Записано " << (count - 1) << " записів." << endl;
    }
}

void displaySingleRecord(EducationalInstitution* institution) {
    if (institution == nullptr) return;

    cout << "Код закладу в ЄДЕБО: " << institution->edeboCode << endl;
    cout << "Повне найменування: " << institution->fullName << endl;
    cout << "Коротка назва: " << institution->shortName << endl;
    cout << "Повне найменування (англ.): " << institution->fullNameEng << endl;
    cout << "Форма власності: " << institution->ownershipForm << endl;
    cout << "Орган управління: " << institution->managementBody << endl;
    cout << "Посада керівника: " << institution->headPosition << endl;
    cout << "ПІБ керівника: " << institution->headFullName << endl;
    cout << "Юридична адреса: " << institution->address << endl;
    cout << "Телефон/факс: " << institution->phone << endl;
    cout << "Електронна пошта: " << institution->email << endl;
    cout << "Веб-сайт: " << institution->website << endl;
    cout << "ОЦ 'Крим-Україна': " << (institution->crimUkraine ? "Так" : "Ні") << endl;
    cout << "ОЦ 'Донбас-Україна': " << (institution->donbasUkraine ? "Так" : "Ні") << endl;
    cout << "Військова кафедра: " << (institution->militaryDepartment ? "Так" : "Ні") << endl;
    cout << "Рік заснування: " << institution->foundationYear << endl;
}

void displaySingleRecordToFile(EducationalInstitution* institution, ofstream& file) {
    if (institution == nullptr) return;

    file << "Код закладу в ЄДЕБО: " << institution->edeboCode << endl;
    file << "Повне найменування: " << institution->fullName << endl;
    file << "Коротка назва: " << institution->shortName << endl;
    file << "Повне найменування (англ.): " << institution->fullNameEng << endl;
    file << "Форма власності: " << institution->ownershipForm << endl;
    file << "Орган управління: " << institution->managementBody << endl;
    file << "Посада керівника: " << institution->headPosition << endl;
    file << "ПІБ керівника: " << institution->headFullName << endl;
    file << "Юридична адреса: " << institution->address << endl;
    file << "Телефон/факс: " << institution->phone << endl;
    file << "Електронна пошта: " << institution->email << endl;
    file << "Веб-сайт: " << institution->website << endl;
    file << "ОЦ 'Крим-Україна': " << (institution->crimUkraine ? "Так" : "Ні") << endl;
    file << "ОЦ 'Донбас-Україна': " << (institution->donbasUkraine ? "Так" : "Ні") << endl;
    file << "Військова кафедра: " << (institution->militaryDepartment ? "Так" : "Ні") << endl;
    file << "Рік заснування: " << institution->foundationYear << endl;
}

void interactiveSearch(EducationalInstitution* head) {
    int code;
    char choice;

    do {
        cout << "\n=== ПОШУК ЗАКЛАДУ ЗА КОДОМ ЄДЕБО ===" << endl;
        cout << "Введіть код ЄДЕБО для пошуку: ";

        while (!(cin >> code) || code <= 0) {
            cout << "Помилка! Введіть коректний код (ціле додатне число): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        searchByCode(head, code);

        cout << "\nЗдійснити ще один пошук? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');
}
