#include <iostream>
#include <vector>
#include <cstdlib> 
#include <ctime>  

using namespace std;

int main() {
    int N;
    cout << "Enter number of vertices: ";
    cin >> N;

    // дабы не перегружать
    if (N > 20) {
        cout << "Warning" << endl;
    }

    // случ чиссла
    srand(time(0));

    // создаём матрицу N x N и заполняем нулями
    vector<vector<int>> adj(N, vector<int>(N, 0));

    // проходим по всем парам вершин
    for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) {
            if (i == j) {
                // на диагонали ставим 0 
                adj[i][j] = 0;
            } else {
                // генерируем случайную связь 0 или 1
                int val = rand() % 2;
                adj[i][j] = val;
                adj[j][i] = val; // симметрично для неориентированного графа
            }
        }
    }

    if (N <= 20) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << adj[i][j] << " ";
            }
            cout << endl;
        }
    } else {
        cout << "large" << endl;
    }

    return 0;
}
