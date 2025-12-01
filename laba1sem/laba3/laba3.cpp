//Удалить дублирующиеся значения из входного массива
#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

// F удаляет дубликаты из массива
vector<int> removeDuplicates(const vector<int>& arr) {
    unordered_set<int> used;   // мн для хранения уже встреченных чисел
    vector<int> result;        // сюда только уникальные значения


    for (int x : arr) {
        if (used.count(x) == 0) {
            used.insert(x);    // отметка что элемент уже встречался
            result.push_back(x);
        }
    }

    return result; // возврат без дубликатов
}

int main() {

    {
        vector<int> arr = {1, 2, 3, 1};
        vector<int> out = removeDuplicates(arr);

        cout << "Test 1: ";
        for (int x : out) cout << x << " ";
        cout << "\n";
    }

    {
        vector<int> arr = {5, 5, 5, 5};
        vector<int> out = removeDuplicates(arr);

        cout << "Test 2: ";
        for (int x : out) cout << x << " ";
        cout << "\n";
    }

    {
        vector<int> arr = {10, 20, 30, 40};
        vector<int> out = removeDuplicates(arr);

        cout << "Test 3: ";
        for (int x : out) cout << x << " ";
        cout << "\n";
    }

    return 0;
}
//arr → 4*10⁴ + 24 ≈ 40 KB
//out → 4*10⁴ + 24 ≈ 40 KB
//unordered_set → 40 * 10⁴ ≈ 400 KB
//Стек/переменные ≈ 1 KB
//Итого ≈ 480-500 KB