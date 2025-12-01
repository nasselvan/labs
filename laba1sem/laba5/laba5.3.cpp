#include <iostream>
#include <vector>
using namespace std;

void countsort(vector<int>& arr) {
    if (arr.empty()) return;
// узнаем размер счётчика
    int maxV = arr[0];
    for (int x : arr) maxV = max(maxV, x);
// массив-счётчик для каждого числа от 0 до maxV
    vector<int> count(maxV + 1, 0);

    //сколько раз встречается каждое число
    for (int x : arr) count[x]++;

    // заполняем
    int index = 0;
    for (int i = 0; i <= maxV; i++) {
        while (count[i] > 0) {
            arr[index++] = i;
            count[i]--;
        }
    }
}

int main() {
    vector<int> arr = {4, 2, 2, 8, 3, 3, 1};

    cout << "Before: ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    countsort(arr);

    cout << "After:  ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    return 0;
}
