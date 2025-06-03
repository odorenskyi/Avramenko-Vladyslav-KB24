#ifndef STRUCT_TYPE_PROJECT_9_H_INCLUDED
#define STRUCT_TYPE_PROJECT_9_H_INCLUDED

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

// Структура для зберігання інформації про заклад освіти
struct EducationalInstitution {
    int edeboCode;                    // Код закладу в ЄДЕБО
    string fullName;                  // Повне найменування
    string shortName;                 // Коротка назва
    string fullNameEng;               // Повне найменування (англ.)
    string ownershipForm;             // Форма власності
    string managementBody;            // Орган управління
    string headPosition;              // Посада керівника
    string headFullName;              // ПІБ керівника
    string address;                   // Юридична адреса
    string phone;                     // Телефон/факс
    string email;                     // Електронна пошта
    string website;                   // Веб-сайт
    bool crimUkraine;                 // ОЦ "Крим-Україна"
    bool donbasUkraine;               // ОЦ "Донбас-Україна"
    bool militaryDepartment;          // Військова кафедра
    int foundationYear;               // Рік заснування
    EducationalInstitution* next;     // Вказівник на наступний елемент

    // Конструктор за замовчуванням
    EducationalInstitution() : edeboCode(0), crimUkraine(false),
                              donbasUkraine(false), militaryDepartment(false),
                              foundationYear(0), next(nullptr) {}
};

// Прототипи функцій для роботи з динамічною структурою даних

// Функції Авраменко
EducationalInstitution* addRecord(EducationalInstitution* head);
EducationalInstitution* loadFromFile(const string& filename);

// Функції Ковальчук
EducationalInstitution* searchByCode(EducationalInstitution* head, int code);
void displayRegistry(EducationalInstitution* head, const string& outputFile = "");

// Функції Терещенко
EducationalInstitution* deleteRecord(EducationalInstitution* head, int code);
void saveToFile(EducationalInstitution* head, const string& filename);

// Допоміжні функції
void clearRegistry(EducationalInstitution* head);
int getRegistrySize(EducationalInstitution* head);
void displayMenu();
bool validateInput(int code, const string& name);

#endif // STRUCT_TYPE_PROJECT_9_H_INCLUDED
