#include <iostream>
#include <vector>
using namespace std;

void shell(vector<int>& arr) {
    int n = arr.size();

    //с большого шага и уменьшаем до 1
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // вставками для каждого шага
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            // сдвиг
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

int main() {
    vector<int> arr = {8, 5, 3, 2, 9, 1, 4};

    cout << "Before: ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    shell(arr);

    cout << "After:  ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    return 0;
}
