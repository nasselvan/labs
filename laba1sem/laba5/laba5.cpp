#include <iostream>
#include <vector>
using namespace std;

// Функция сортировки переполнением
void Sort(vector<int>& arr) {
    int i = 0;              
    int n = arr.size();     

    while (i < n) {         
        // если на нуле или текущий элемент >= предыдущего
        if (i == 0 || arr[i] >= arr[i-1]) {
            i++;           
        } else {
            // если текущий элемент меньше предыдущего, меняем их местами
            swap(arr[i], arr[i-1]);
            i--;            // назад дабы переполнить
        }
    }
}

int main() {
    vector<int> arr = {2, 3, 4, 1};

    cout << "Before: ";
    for(int x : arr) cout << x << " ";   // массив до сортировки
    cout << endl;

    Sort(arr);                   // сорт

    cout << "After:  ";
    for(int x : arr) cout << x << " ";   // массив после сортировки
    cout << endl;

    return 0;
}
