#include "struct_type_project_9.h"
#include <iostream>
#include <string>
#include <limits>

using namespace std;

// Константи
const string DATA_FILE = "registry.dat";
const string BACKUP_FILE = "registry_backup.dat";

// Прототипи допоміжних функцій
void displayMenu();
int getMenuChoice();
void pauseScreen();
void showHeader();

int main() {
    system("chcp 65001");
    system("cls");
    EducationalInstitution* registryHead = nullptr;
    int choice;
    bool running = true;

    // Показати заголовок програми
    showHeader();

    // Автоматичне завантаження реєстру з файлу при запуску
    cout << "Ініціалізація системи..." << endl;
    registryHead = loadFromFile(DATA_FILE);

    cout << "\nСистема готова до роботи!" << endl;
    pauseScreen();

    // Головний цикл програми
    while (running) {
        system("clear");
        showHeader();
        displayMenu();

        choice = getMenuChoice();

        switch (choice) {
            case 1: {
                // Виведення реєстру на екран
                cout << "\n=== ВИВЕДЕННЯ РЕЄСТРУ НА ЕКРАН ===" << endl;
                displayRegistry(registryHead);
                pauseScreen();
                break;
            }

            case 2: {
                // Виведення реєстру у файл
                cout << "\n=== ЕКСПОРТ РЕЄСТРУ У ФАЙЛ ===" << endl;
                string filename;
                cout << "Введіть ім'я файлу для експорту (наприклад, report.txt): ";
                cin.ignore();
                getline(cin, filename);

                if (filename.empty()) {
                    filename = "registry_export.txt";
                    cout << "Використовується ім'я за замовчуванням: " << filename << endl;
                }

                displayRegistry(registryHead, filename);
                pauseScreen();
                break;
            }

            case 3: {
                // Додавання нового запису
                cout << "\n=== ДОДАВАННЯ НОВОГО ЗАПИСУ ===" << endl;
                registryHead = addRecord(registryHead);
                pauseScreen();
                break;
            }

            case 4: {
                // Пошук запису за кодом ЄДЕБО
                cout << "\n=== ПОШУК ЗАПИСУ ===" << endl;
                int searchCode;
                cout << "Введіть код ЄДЕБО для пошуку: ";

                while (!(cin >> searchCode) || searchCode <= 0) {
                    cout << "Помилка! Введіть коректний код (ціле додатне число): ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                searchByCode(registryHead, searchCode);
                pauseScreen();
                break;
            }

            case 5: {
                // Видалення запису
                cout << "\n=== ВИДАЛЕННЯ ЗАПИСУ ===" << endl;
                int deleteCode;
                cout << "Введіть код ЄДЕБО запису для видалення: ";

                while (!(cin >> deleteCode) || deleteCode <= 0) {
                    cout << "Помилка! Введіть коректний код (ціле додатне число): ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                registryHead = deleteRecord(registryHead, deleteCode);
                pauseScreen();
                break;
            }

            case 6: {
                // Ручне збереження
                cout << "\n=== ЗБЕРЕЖЕННЯ РЕЄСТРУ ===" << endl;
                if (validateDataIntegrity(registryHead)) {
                    saveToFile(registryHead, DATA_FILE);

                    char createBackupChoice;
                    cout << "Створити резервну копію? (y/n): ";
                    cin >> createBackupChoice;
                    if (createBackupChoice == 'y' || createBackupChoice == 'Y') {
                        createBackup(registryHead, BACKUP_FILE);
                    }
                } else {
                    cout << "Збереження скасовано через помилки в даних!" << endl;
                }
                pauseScreen();
                break;
            }

            case 7: {
                // Статистика реєстру
                cout << "\n=== СТАТИСТИКА РЕЄСТРУ ===" << endl;
                int totalRecords = getRegistrySize(registryHead);
                cout << "Загальна кількість записів: " << totalRecords << endl;

                if (totalRecords > 0) {
                    // Підрахунок статистики
                    int stateOwned = 0, privateOwned = 0, withMilitary = 0;
                    int crimUkraineCount = 0, donbasUkraineCount = 0;

                    EducationalInstitution* current = registryHead;
                    while (current != nullptr) {
                        if (current->ownershipForm.find("Державна") != string::npos) {
                            stateOwned++;
                        } else if (current->ownershipForm.find("Приватна") != string::npos) {
                            privateOwned++;
                        }

                        if (current->militaryDepartment) withMilitary++;
                        if (current->crimUkraine) crimUkraineCount++;
                        if (current->donbasUkraine) donbasUkraineCount++;

                        current = current->next;
                    }

                    cout << "Державні заклади: " << stateOwned << endl;
                    cout << "Приватні заклади: " << privateOwned << endl;
                    cout << "З військовою кафедрою: " << withMilitary << endl;
                    cout << "ОЦ 'Крим-Україна': " << crimUkraineCount << endl;
                    cout << "ОЦ 'Донбас-Україна': " << donbasUkraineCount << endl;
                }
                pauseScreen();
                break;
            }

            case 0: {
                // Завершення роботи програми
                cout << "\n=== ЗАВЕРШЕННЯ РОБОТИ ПРОГРАМИ ===" << endl;

                // Автоматичне збереження
                cout << "Виконується автоматичне збереження..." << endl;
                if (validateDataIntegrity(registryHead)) {
                    autoSave(registryHead, DATA_FILE);
                    cout << "Дані збережено успішно!" << endl;
                } else {
                    cout << "УВАГА: Виявлено помилки в даних!" << endl;
                    char forceSave;
                    cout << "Зберегти попри помилки? (y/n): ";
                    cin >> forceSave;
                    if (forceSave == 'y' || forceSave == 'Y') {
                        saveToFile(registryHead, DATA_FILE);
                    }
                }

                // Очищення пам'яті
                cout << "Очищення пам'яті..." << endl;
                clearRegistry(registryHead);

                cout << "Дякуємо за використання системи!" << endl;
                cout << "Програму розробили: Авраменко, Ковальчук, Терещенко" << endl;

                running = false;
                break;
            }

            default: {
                cout << "Невірний вибір! Спробуйте ще раз." << endl;
                pauseScreen();
                break;
            }
        }
    }

    return 0;
}

void displayMenu() {
    cout << "\n" << string(60, '=') << endl;
    cout << "                    ГОЛОВНЕ МЕНЮ" << endl;
    cout << string(60, '=') << endl;
    cout << "1. Переглянути весь реєстр на екрані" << endl;
    cout << "2. Експортувати реєстр у текстовий файл" << endl;
    cout << "3. Додати новий заклад до реєстру" << endl;
    cout << "4. Знайти заклад за кодом ЄДЕБО" << endl;
    cout << "5. Видалити заклад з реєстру" << endl;
    cout << "6. Зберегти реєстр у файл" << endl;
    cout << "7. Переглянути статистику реєстру" << endl;
    cout << "0. Завершити роботу програми" << endl;
    cout << string(60, '=') << endl;
}

int getMenuChoice() {
    int choice;
    cout << "Ваш вибір: ";

    while (!(cin >> choice)) {
        cout << "Помилка! Введіть число: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return choice;
}

void pauseScreen() {
    cout << "\nНатисніть Enter для продовження...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void showHeader() {
    cout << string(80, '=') << endl;
    cout << "     ЕЛЕКТРОННИЙ РЕЄСТР СУБ'ЄКТІВ ОСВІТНЬОЇ ДІЯЛЬНОСТІ" << endl;
    cout << "                  ЗАКЛАДИ ВИЩОЇ ОСВІТИ" << endl;
    cout << "                       ВАРІАНТ 9" << endl;
    cout << string(80, '=') << endl;
    cout << "Розробники: Авраменко, Ковальчук, Терещенко" << endl;
    cout << "Дисципліна: Базові методології та технології програмування" << endl;
    cout << string(80, '=') << endl;
}

// Реалізація допоміжних функцій з struct_type_project_9.h
void clearRegistry(EducationalInstitution* head) {
    while (head != nullptr) {
        EducationalInstitution* temp = head;
        head = head->next;
        delete temp;
    }
}

int getRegistrySize(EducationalInstitution* head) {
    int count = 0;
    EducationalInstitution* current = head;

    while (current != nullptr) {
        count++;
        current = current->next;
    }

    return count;
}

bool validateInput(int code, const string& name) {
    if (code <= 0) {
        cout << "Помилка: код ЄДЕБО повинен бути додатнім числом!" << endl;
        return false;
    }

    if (name.empty()) {
        cout << "Помилка: назва не може бути порожньою!" << endl;
        return false;
    }

    return true;
}
