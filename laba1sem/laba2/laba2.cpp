//Реализовать функцию, которая определяет, являются ли две строки изоморфными
#include <iostream>
#include <string>
using namespace std;

// Функция проверяет, являются ли две строки изоморфными 
bool isomorf(const string& s1, const string& s2) {
    // Если длины разные — сразу false
    if (s1.size() != s2.size()) return false;

    // Массивы для запоминания соответ. символов
    char map1[256] = {0};
    char map2[256] = {0};

    // по символам строк
    for (int i = 0; i < s1.size(); i++) {
        unsigned char c1 = s1[i];
        unsigned char c2 = s2[i];

        // Если ещё нет соответствия
        if (map1[c1] == 0 && map2[c2] == 0) {
            // связываем
            map1[c1] = c2;
            map2[c2] = c1;
        }
        else {
            // если уже есть, но оно другое, то строки не изоморфны
            if (map1[c1] != c2 || map2[c2] != c1) {
                return false;
            }
        }
    }

    return true;
}

void runTests() {
    // для хранения тестов
    struct Test {
        string a, b;
        bool expected;
    };

    // тесты
    Test tests[] = {
        {"egg", "add", true},
        {"foo", "bar", false},
        {"paper", "title", true},
        {"ab", "aa", false},
        {"aab", "xxy", true},
        {"aab", "xyz", false},
        {"abab", "cdcd", true},
        {"abcd", "aaaa", false},
        {"", "", true}
    };

    // кол-во тестов
    int totalTests = sizeof(tests) / sizeof(tests[0]);

    cout << "Running tests...\n";

    for (int i = 0; i < totalTests; i++) {
        bool result = isomorf(tests[i].a, tests[i].b);
        cout << "Test " << i + 1 << ": ";
        cout << tests[i].a << " , " << tests[i].b << " -> ";
        cout << (result ? "true" : "false");

        if (result == tests[i].expected)
            cout << "   [OK]\n";
        else
            cout << "   [FAIL]\n";
    }
}

int main() {
    runTests();
    return 0;
}
// подсчёт использования памяти:
// map1 + map2: около 512 байт
// строки в тестах: около 1.1 КБ
// массив Test[]: около 600 байт
// стек + служебные данные: около 300 байт
// общий объём около 2.5–3 КБ 
