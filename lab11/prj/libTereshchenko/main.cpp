#include "struct_type_project_9.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

EducationalInstitution* deleteRecord(EducationalInstitution* head, int code) {
    if (head == nullptr) {
        cout << "Реєстр порожній! Нема що видаляти." << endl;
        return nullptr;
    }

    EducationalInstitution* current = head;
    EducationalInstitution* previous = nullptr;

    // Пошук елемента для видалення
    while (current != nullptr && current->edeboCode != code) {
        previous = current;
        current = current->next;
    }

    // Якщо елемент не знайдено
    if (current == nullptr) {
        cout << "Запис з кодом ЄДЕБО " << code << " не знайдено в реєстрі." << endl;
        return head;
    }

    // Показуємо інформацію про запис, який буде видалено
    cout << "\n=== ЗНАЙДЕНО ЗАПИС ДЛЯ ВИДАЛЕННЯ ===" << endl;
    cout << "Код ЄДЕБО: " << current->edeboCode << endl;
    cout << "Назва: " << current->fullName << endl;
    cout << "Коротка назва: " << current->shortName << endl;

    // Підтвердження видалення
    char confirmation;
    cout << "\nВи дійсно хочете видалити цей запис? (y/n): ";
    cin >> confirmation;

    if (confirmation != 'y' && confirmation != 'Y') {
        cout << "Видалення скасовано." << endl;
        return head;
    }

    // Видалення елемента
    if (previous == nullptr) {
        // Видаляємо перший елемент
        head = current->next;
    } else {
        // Видаляємо елемент з середини або кінця
        previous->next = current->next;
    }

    delete current;
    cout << "Запис успішно видалено з реєстру!" << endl;

    return head;
}

void saveToFile(EducationalInstitution* head, const string& filename) {
    ofstream file(filename, ios::binary | ios::trunc);

    if (!file.is_open()) {
        cout << "Помилка створення файлу " << filename << " для збереження!" << endl;
        return;
    }

    if (head == nullptr) {
        cout << "Реєстр порожній. Створено порожній файл " << filename << endl;
        file.close();
        return;
    }

    cout << "Збереження реєстру у файл " << filename << "..." << endl;

    EducationalInstitution* current = head;
    int count = 0;

    // Функція для запису рядка у бінарний файл
    auto writeString = [&file](const string& str) {
        size_t length = str.length();
        file.write(reinterpret_cast<const char*>(&length), sizeof(size_t));
        file.write(str.c_str(), length);
    };

    while (current != nullptr) {
        // Запис числових даних
        file.write(reinterpret_cast<const char*>(&current->edeboCode), sizeof(int));

        // Запис всіх рядкових полів
        writeString(current->fullName);
        writeString(current->shortName);
        writeString(current->fullNameEng);
        writeString(current->ownershipForm);
        writeString(current->managementBody);
        writeString(current->headPosition);
        writeString(current->headFullName);
        writeString(current->address);
        writeString(current->phone);
        writeString(current->email);
        writeString(current->website);

        // Запис булевих значень
        file.write(reinterpret_cast<const char*>(&current->crimUkraine), sizeof(bool));
        file.write(reinterpret_cast<const char*>(&current->donbasUkraine), sizeof(bool));
        file.write(reinterpret_cast<const char*>(&current->militaryDepartment), sizeof(bool));

        // Запис року заснування
        file.write(reinterpret_cast<const char*>(&current->foundationYear), sizeof(int));

        current = current->next;
        count++;
    }

    file.close();

    if (file.fail()) {
        cout << "Помилка при записі у файл!" << endl;
    } else {
        cout << "Реєстр успішно збережено!" << endl;
        cout << "Збережено " << count << " записів у файл " << filename << endl;
    }
}

EducationalInstitution* interactiveDelete(EducationalInstitution* head) {
    int code;
    char choice;

    do {
        if (head == nullptr) {
            cout << "Реєстр порожній! Нема що видаляти." << endl;
            break;
        }

        cout << "\n=== ВИДАЛЕННЯ ЗАПИСУ З РЕЄСТРУ ===" << endl;
        cout << "Введіть код ЄДЕБО запису для видалення: ";

        while (!(cin >> code) || code <= 0) {
            cout << "Помилка! Введіть коректний код (ціле додатне число): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        head = deleteRecord(head, code);

        if (head != nullptr) {
            cout << "\nВидалити ще один запис? (y/n): ";
            cin >> choice;
        } else {
            cout << "Реєстр тепер порожній." << endl;
            break;
        }

    } while (choice == 'y' || choice == 'Y');

    return head;
}

void autoSave(EducationalInstitution* head, const string& filename) {
    cout << "\n=== АВТОМАТИЧНЕ ЗБЕРЕЖЕННЯ ===" << endl;
    saveToFile(head, filename);
}

void createBackup(EducationalInstitution* head, const string& backupFilename) {
    cout << "Створення резервної копії..." << endl;
    saveToFile(head, backupFilename);
    cout << "Резервну копію створено: " << backupFilename << endl;
}

bool validateDataIntegrity(EducationalInstitution* head) {
    if (head == nullptr) {
        return true; // Порожній список вважається валідним
    }

    EducationalInstitution* current = head;
    int count = 0;

    while (current != nullptr) {
        // Перевірка обов'язкових полів
        if (current->edeboCode <= 0) {
            cout << "Помилка: некоректний код ЄДЕБО у записі №" << (count + 1) << endl;
            return false;
        }

        if (current->fullName.empty()) {
            cout << "Помилка: відсутня назва у записі №" << (count + 1) << endl;
            return false;
        }

        if (current->foundationYear < 1000 || current->foundationYear > 2024) {
            cout << "Помилка: некоректний рік заснування у записі №" << (count + 1) << endl;
            return false;
        }

        current = current->next;
        count++;
    }

    cout << "Перевірка цілісності пройшла успішно. Записів: " << count << endl;
    return true;
}
