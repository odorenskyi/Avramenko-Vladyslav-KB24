#ifndef STRUCT_TYPE_PROJECT_9_H_INCLUDED
#define STRUCT_TYPE_PROJECT_9_H_INCLUDED

#include <string>
#include <iostream>
#include <fstream>
#include <limits>

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

// Функції Авраменко
EducationalInstitution* addRecord(EducationalInstitution* head);
EducationalInstitution* loadFromFile(const string& filename);
bool codeExists(EducationalInstitution* head, int code);

// Функції Ковальчук
EducationalInstitution* searchByCode(EducationalInstitution* head, int code);
void displayRegistry(EducationalInstitution* head, const string& outputFile = "");
void displaySingleRecord(EducationalInstitution* institution);
void displaySingleRecordToFile(EducationalInstitution* institution, ofstream& file);
void interactiveSearch(EducationalInstitution* head);

// Функції Терещенко
EducationalInstitution* deleteRecord(EducationalInstitution* head, int code);
void saveToFile(EducationalInstitution* head, const string& filename);
EducationalInstitution* interactiveDelete(EducationalInstitution* head);
void autoSave(EducationalInstitution* head, const string& filename);
void createBackup(EducationalInstitution* head, const string& backupFilename);
bool validateDataIntegrity(EducationalInstitution* head);

// Допом
void clearRegistry(EducationalInstitution* head);
int getRegistrySize(EducationalInstitution* head);
void displayMenu();
bool validateInput(int code, const string& name);

#endif // STRUCT_TYPE_PROJECT_9_H_INCLUDED
