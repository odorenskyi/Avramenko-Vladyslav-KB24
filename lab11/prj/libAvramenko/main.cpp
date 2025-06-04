#include "struct_type_project_9.h"
#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

EducationalInstitution* addRecord(EducationalInstitution* head) {
    EducationalInstitution* newInstitution = new EducationalInstitution();

    cout << "\n=== ДОДАВАННЯ НОВОГО ЗАКЛАДУ ОСВІТИ ===" << endl;

    // Введення основних даних
    cout << "Введіть код закладу в ЄДЕБО: ";
    while (!(cin >> newInstitution->edeboCode) || newInstitution->edeboCode <= 0) {
        cout << "Помилка! Введіть коректний код (ціле додатне число): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(); // Очищення буфера після числа

    cout << "Введіть повне найменування: ";
    getline(cin, newInstitution->fullName);

    cout << "Введіть коротку назву: ";
    getline(cin, newInstitution->shortName);

    cout << "Введіть повне найменування (англ.): ";
    getline(cin, newInstitution->fullNameEng);

    cout << "Введіть форму власності: ";
    getline(cin, newInstitution->ownershipForm);

    cout << "Введіть найменування органу управління: ";
    getline(cin, newInstitution->managementBody);

    cout << "Введіть посаду та ПІБ керівника: ";
    getline(cin, newInstitution->headPosition);

    cout << "Введіть ПІБ керівника: ";
    getline(cin, newInstitution->headFullName);

    cout << "Введіть юридичну адресу: ";
    getline(cin, newInstitution->address);

    cout << "Введіть телефон/факс: ";
    getline(cin, newInstitution->phone);

    cout << "Введіть електронну пошту: ";
    getline(cin, newInstitution->email);

    cout << "Введіть веб-сайт: ";
    getline(cin, newInstitution->website);

    // Введення булевих значень
    char choice;
    cout << "ОЦ 'Крим-Україна' (y/n): ";
    cin >> choice;
    newInstitution->crimUkraine = (choice == 'y' || choice == 'Y');

    cout << "ОЦ 'Донбас-Україна' (y/n): ";
    cin >> choice;
    newInstitution->donbasUkraine = (choice == 'y' || choice == 'Y');

    cout << "Військова кафедра (y/n): ";
    cin >> choice;
    newInstitution->militaryDepartment = (choice == 'y' || choice == 'Y');

    cout << "Введіть рік заснування: ";
    while (!(cin >> newInstitution->foundationYear) ||
           newInstitution->foundationYear < 1000 ||
           newInstitution->foundationYear > 2024) {
        cout << "Помилка! Введіть коректний рік (1000-2024): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Додавання на початок списку
    newInstitution->next = head;

    cout << "Запис успішно додано!" << endl;
    return newInstitution;
}

EducationalInstitution* loadFromFile(const string& filename) {
    ifstream file(filename, ios::binary);
    EducationalInstitution* head = nullptr;
    EducationalInstitution* tail = nullptr;

    if (!file.is_open()) {
        cout << "Файл " << filename << " не знайдено. Створюється новий реєстр." << endl;
        return nullptr;
    }

    cout << "Завантаження реєстру з файлу " << filename << "..." << endl;

    while (file.peek() != EOF) {
        EducationalInstitution* newInstitution = new EducationalInstitution();

        // Читання числових даних
        file.read(reinterpret_cast<char*>(&newInstitution->edeboCode), sizeof(int));
        if (file.eof()) break;

        // Функція для читання рядків з бінарного файлу
        auto readString = [&file](string& str) {
            size_t length;
            file.read(reinterpret_cast<char*>(&length), sizeof(size_t));
            if (length > 0) {
                char* buffer = new char[length + 1];
                file.read(buffer, length);
                buffer[length] = '\0';
                str = string(buffer);
                delete[] buffer;
            }
        };

        // Читання всіх рядкових полів
        readString(newInstitution->fullName);
        readString(newInstitution->shortName);
        readString(newInstitution->fullNameEng);
        readString(newInstitution->ownershipForm);
        readString(newInstitution->managementBody);
        readString(newInstitution->headPosition);
        readString(newInstitution->headFullName);
        readString(newInstitution->address);
        readString(newInstitution->phone);
        readString(newInstitution->email);
        readString(newInstitution->website);

        // Читання булевих значень
        file.read(reinterpret_cast<char*>(&newInstitution->crimUkraine), sizeof(bool));
        file.read(reinterpret_cast<char*>(&newInstitution->donbasUkraine), sizeof(bool));
        file.read(reinterpret_cast<char*>(&newInstitution->militaryDepartment), sizeof(bool));

        // Читання року заснування
        file.read(reinterpret_cast<char*>(&newInstitution->foundationYear), sizeof(int));

        newInstitution->next = nullptr;

        // Додавання до кінця списку для збереження порядку
        if (head == nullptr) {
            head = tail = newInstitution;
        } else {
            tail->next = newInstitution;
            tail = newInstitution;
        }
    }

    file.close();

    int count = getRegistrySize(head);
    cout << "Завантажено " << count << " записів з файлу." << endl;

    return head;
}

bool codeExists(EducationalInstitution* head, int code) {
    EducationalInstitution* current = head;
    while (current != nullptr) {
        if (current->edeboCode == code) {
            return true;
        }
        current = current->next;
    }
    return false;
}
