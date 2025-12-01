//Поиск подмассивов размера K в массиве размера N, сумма элементов которых равна нулю
#include <iostream>
#include <vector>
using namespace std;

// рекурсивная функция поиска подмассивов размера K с сум 0
void research(vector<int>& arr, int K, int start, vector<int>& current, vector<vector<int>>& result) {
    if (current.size() == K) { // если подмассив нужного размера
        int sum = 0;
        for (int idx : current) sum += arr[idx]; // считаем сумму
        if (sum == 0) result.push_back(current); // если сумма 0, сохраняем
        return;
    }

    for (int i = start; i < arr.size(); i++) {
        current.push_back(i); // +индекс
        research(arr, K, i + 1, current, result);
        current.pop_back(); // убираем индекс 
    }
}

void printResult(vector<vector<int>>& result) {
    for (size_t i = 0; i < result.size(); i++) {
        cout << "[";
        for (size_t j = 0; j < result[i].size(); j++) {
            cout << result[i][j];
            if (j != result[i].size() - 1) cout << ", ";
        }
        cout << "]";
        if (i != result.size() - 1) cout << ", ";
    }
    cout << endl;
}

int main() {
    vector<vector<int>> arrays = {
        {1, -1, 2, -2},
        {1, -1, 2, -3},
        {1, 1, -1, -1}
    };
    vector<int> Ks = {2, 3, 2}; 

    for (size_t test = 0; test < arrays.size(); test++) {
        vector<int>& arr = arrays[test];
        int K = Ks[test];
        vector<vector<int>> result;
        vector<int> current;

        research(arr, K, 0, current, result);

        cout << "array " << test+1 << ": ";
        printResult(result);
    }

    return 0;
}





