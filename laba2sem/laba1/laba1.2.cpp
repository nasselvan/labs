//Необходимо отзеркалить бинарное дерево
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// Узел
struct Node {
    int data;        
    Node* left;     
    Node* right; 
    Node(int x) : data(x), left(nullptr), right(nullptr) {} // конструктор узла
};

// Построение дерева по уровням 
Node* buildTree(const vector<int>& values) {
    if (values.empty()) return nullptr;  // нет чисел, тогда дерево пустое
    
    Node* root = new Node(values[0]);   // корень
    queue<Node*> q;                     // очередь для построения по уровням
    q.push(root);                       
    
    int i = 1;                           // индекс следующего числа в массиве
    while (i < values.size()) {          // пока есть числа
        Node* current = q.front(); q.pop(); // берём узел, куда будем добавлять потомков
        
        // левый
        if (i < values.size()) {
            current->left = new Node(values[i++]);
            q.push(current->left);      // добавляем в очередь, чтобы потом добавить детей
        }
        
        // правый 
        if (i < values.size()) {
            current->right = new Node(values[i++]);
            q.push(current->right);
        }
    }
    
    return root; // корень дерева
}

// Зеркалирование дерева
void mirror(Node* root) {
    if (!root) return;          // \узел пустой, ничего
    
    mirror(root->left);         // зеркалим левое поддерево
    mirror(root->right);        // зеркалим правое поддерево
    swap(root->left, root->right); // меняем местами 
}

// Обход как в примере (левоправокорень)
void postorder(Node* root) {
    if (!root) return;          //узел пустой, ничего
    
    postorder(root->left);      // идём в левое поддерево
    postorder(root->right);     // идём в правое поддерево
    cout << root->data << " ";  // значение узла
}


int main() {
    vector<int> values;         // массив для чисел
    int x;
    
    // Считываем числа до конца ввода
    while (cin >> x) {
        // проверка ограничения по заданию
        if (x > 10000) {
            cerr << "Элемент превышает максимальное значение 1e4" << endl;
            return 1;
        }
        
        values.push_back(x);
        
        // проверка ограничения на количество узлов
        if (values.size() > 10000) {
            cerr << "Превышен максимальный размер дерева 1e4" << endl;
            return 1;
        }
    }
    
    Node* root = buildTree(values); // строим дерево
    
    mirror(root);                   // зеркалим дерево
    
    postorder(root);                
    cout << endl;
    
    return 0;
}
