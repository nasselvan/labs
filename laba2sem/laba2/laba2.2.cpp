/*  
Нужно на C++ без использования std::unordered_map написать свою хеш-таблицу для хранения значений по ключу
Ключ: int
Значение: int
Метод разрешения коллизий: метод цепочек
Реализация хеш-функций: метод деления
Ограничения
Количество элементов : n <= 10^6
*/
#include <iostream>
#include <vector>
#include <list>
using namespace std;

//ключ-значение
struct KeyValue {
    int key;
    int value;
    KeyValue(int k, int v) : key(k), value(v) {}
};

class HashTable {
private:
    int M;  // размер массива корзин
    vector<list<KeyValue>> table; // массив списков те цепоччек

    // метод деления
    int hash(int key) {
    return (key % M + M) % M; // неотр индекс
}

public:
    HashTable(int size) : M(size) {
        table.resize(M); // создаём M корзин
    }

    // Добавление 
    void insert(int key, int value) {
        int idx = hash(key);
        for (auto &kv : table[idx]) {
            if (kv.key == key) {
                kv.value = value; // если есть, обновляем значение
                return;
            }
        }
        table[idx].emplace_back(key, value); 
    }

    // значение по ключу, возвращает тру
    bool get(int key, int &value) {
        int idx = hash(key);
        for (auto &kv : table[idx]) {
            if (kv.key == key) {
                value = kv.value;
                return true;
            }
        }
        return false; // ключ не найден
    }

    // Удаление элемента по ключу
    bool remove(int key) {
        int idx = hash(key);
        for (auto it = table[idx].begin(); it != table[idx].end(); ++it) {
            if (it->key == key) {
                table[idx].erase(it);
                return true;
            }
        }
        return false; 
    }
};

// заранее узнаем колво операций
int main() {
    int n;
    cin >> n; // количество операций

    HashTable ht(1000003); 

    for (int i = 0; i < n; i++) {
        string op;
        int key, value;
        cin >> op;
        if (op == "insert") {
            cin >> key >> value;
            ht.insert(key, value);
        } else if (op == "get") {
            cin >> key;
            if (ht.get(key, value)) {
                cout << value << "\n";
            } else {
                cout << "NOT FOUND\n";
            }
        } else if (op == "remove") {
            cin >> key;
            ht.remove(key);
        }
    }

    return 0;
}