#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <climits> 
using namespace std;

// ребро 
struct Edge {
    int from, to;    // откуда и куда
    int flow;        // текущий поток
    int capacity;    // пропускная способность
    Edge(int f, int t, int fl, int cap) : from(f), to(t), flow(fl), capacity(cap) {}
    int residual() { return capacity - flow; } // сколько ещё можно передать
};

// Узел графа
struct Node {
    int number;             // номер узла
    vector<Edge*> adj;      // список дуг, из этого узла можно куда-то идти
    Node(int n) : number(n) {}
};

// Ищем дугу между двумя узлами
Edge* get_edge(vector<Node*>& graph, int src, int dst) {
    for (auto e : graph[src]->adj)
        if (e->to == dst) return e;
    return nullptr; // если нет
}

// DFS те ищем путь из src в dst, по которому ещё можно что-то передать
bool dfs(vector<Node*>& graph, int src, int dst, list<Edge*>& path, vector<bool>& visited) {
    if (src == dst) return true; 
    visited[src] = true;
    for (auto e : graph[src]->adj) {
        if (e->residual() > 0 && !visited[e->to]) { 
            if (dfs(graph, e->to, dst, path, visited)) {
                path.push_front(e); // сохраняем путь
                return true;
            }
        }
    }
    return false; // пути нет
}

// Форда-Фалкерсона алгоритм, считает макс поток
int ford_fulkerson(vector<Node*>& graph, int src, int dst, int &iterations) {
    iterations = 0; // количество итераций
    int max_flow = 0; // максимальный поток
    while (true) {
        list<Edge*> path;              //сохр найденный путь
        vector<bool> visited(graph.size(), false); // отмечаем посещенные узлы
        if (!dfs(graph, src, dst, path, visited)) break; // пути нет

        iterations++; // нашли путь, плюсуем итерацию

        int min_flow = INT_MAX;      // мин пропускная способность на пути
        for (auto e : path) min_flow = min(min_flow, e->residual());

        for (auto e : path) {
            e->flow += min_flow; // увеличиваем поток
            auto* anti = get_edge(graph, e->to, e->from); // находим обратную дугу
            if (anti) anti->flow -= min_flow; // уменьшаем поток обратно
        }
        max_flow += min_flow; // добавляем к общему потоку
    }
    return max_flow;
}

// выводим граф на экран
void print_graph(vector<Node*>& graph) {
    for (auto node : graph) {
        cout << "Node " << node->number << " -> ";
        for (auto e : node->adj) {
            cout << "(" << e->to << ", " << e->flow << "/" << e->capacity << ") ";
        }
        cout << endl;
    }
}
// Простой граф:
vector<Node*> create_simple_graph() {
    vector<Node*> g(4);
    for (int i = 0; i < 4; i++) g[i] = new Node(i);

    g[0]->adj.push_back(new Edge(0,1,0,1));
    g[0]->adj.push_back(new Edge(0,2,0,1));
    g[1]->adj.push_back(new Edge(1,3,0,1));
    g[2]->adj.push_back(new Edge(2,3,0,1));

    // антидуги чтобы откатить
    g[1]->adj.push_back(new Edge(1,0,0,0));
    g[2]->adj.push_back(new Edge(2,0,0,0));
    g[3]->adj.push_back(new Edge(3,1,0,0));
    g[3]->adj.push_back(new Edge(3,2,0,0));

    return g;
}

// Медленный граф 
vector<Node*> create_slow_graph(int n) {
    vector<Node*> g(n+2);
    for (int i = 0; i <= n+1; i++) g[i] = new Node(i);

    for (int i = 0; i <= n; i++) {
        g[i]->adj.push_back(new Edge(i,i+1,0,1));
        g[i+1]->adj.push_back(new Edge(i+1,i,0,0)); // антидуга
    }
    return g;
}

// Несходимый граф
vector<Node*> create_unsolvable_graph() {
    vector<Node*> g(4);
    for (int i = 0; i < 4; i++) g[i] = new Node(i);

    g[0]->adj.push_back(new Edge(0,1,0,1));
    g[0]->adj.push_back(new Edge(0,2,0,1));

    g[1]->adj.push_back(new Edge(1,0,0,0));
    g[2]->adj.push_back(new Edge(2,0,0,0));
    g[3]->adj.push_back(new Edge(3,1,0,0));
    g[3]->adj.push_back(new Edge(3,2,0,0));

    return g;
}

// Запуск теста
void run_test(vector<Node*> graph, int src, int dst, string name) {
    int iterations;
    int max_flow = ford_fulkerson(graph, src, dst, iterations);
    cout << "=== Test: " << name << " ===" << endl;
    cout << "Graph size: " << graph.size() << endl;
    cout << "Max flow: " << max_flow << endl;
    cout << "Iterations: " << iterations << endl;
    print_graph(graph);
    cout << "=========================" << endl << endl;
}

int main() {
    // 1. Простой граф
    auto g1 = create_simple_graph();
    run_test(g1, 0, 3, "Simple Graph");
    for (auto n : g1) delete n;

    // 2. Медленный граф
    auto g2 = create_slow_graph(5);
    run_test(g2, 0, 6, "Slow Graph");
    for (auto n : g2) delete n;

    // 3. Несходимый граф
    auto g3 = create_unsolvable_graph();
    run_test(g3, 0, 3, "Unsolvable Graph");
    for (auto n : g3) delete n;

    return 0;
}
