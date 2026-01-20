#include <iostream>
#include <vector>
#include <windows.h>
#include <numeric>

using namespace std;

/*
  dsu
  рассматриваем:
  объединение кланов
  поиск клана пользователя
  проверку, в одном ли клане два пользователя
  удаление клана (все участники становятся одиночками)
*/

class ClanSystem {
private:
    vector<int> parent;

    // чтобы деревья не становились длинными
    vector<int> rank;

    // members эт список всех пользователей в клане root
    vector<vector<int>> members;

    int n;

public:
    // изначально каждый пользователь находится в своём клане
    ClanSystem(int size) {
        n = size;
        parent.resize(n);
        rank.resize(n, 0);
        members.resize(n);

        iota(parent.begin(), parent.end(), 0);

        // каждый пользователь это отдельный клан
        for (int i = 0; i < n; ++i) {
            members[i].push_back(i);
        }
    }

    // поиск главы клана с сжатием путей
    int findClan(int x) {
        if (parent[x] == x)
            return x;
        return parent[x] = findClan(parent[x]);
    }

    // Объединение двух кланов
    void uniteClans(int x, int y) {
        int rootX = findClan(x);
        int rootY = findClan(y);

        if (rootX == rootY) {
            cout << "находятся в одном клане.\n";
            return;
        }

        // какой клан будет главным при объединении
        if (rank[rootX] < rank[rootY])
            swap(rootX, rootY);

        parent[rootY] = rootX;

        // переносим всех участников клана rootY в rootX
        for (int user : members[rootY]) {
            members[rootX].push_back(user);
        }
        members[rootY].clear();

        if (rank[rootX] == rank[rootY])
            rank[rootX]++;

        cout << "Кланы пользователей " << x << " и " << y << " объединены.\n";
    }

    // Проверка
    bool areInSameClan(int x, int y) {
        return findClan(x) == findClan(y);
    }

    // Удаление клана
    // Все участники клана становятся одиночками
    void deleteClan(int userInClan) {
        int root = findClan(userInClan);

        // Для каждого участника делаем отдельный клан
        for (int user : members[root]) {
            parent[user] = user;
            rank[user] = 0;
            members[user].clear();
            members[user].push_back(user);
        }

        members[root].clear();

        cout << "Клан распущен. Все участники теперь одиночки.\n";
    }

    void printClan(int x) {
        int root = findClan(x);
        cout << "Клан пользователя " << x << ": ";
        for (int user : members[root]) {
            cout << user << " ";
        }
        cout << endl;
    }
};

int main() {
    SetConsoleOutputCP(65001); 
    ClanSystem game(10);

    game.uniteClans(1, 2); // {1,2}
    game.uniteClans(3, 4); // {3,4}
    game.uniteClans(1, 4); // {1,2,3,4}

    if (game.areInSameClan(2, 3)) {
        cout << "Пользователи 2 и 3 в одном клане.\n";
    }

    game.printClan(1);

    game.deleteClan(1);

    if (!game.areInSameClan(2, 3)) {
        cout << "Теперь пользователи 2 и 3 в разных кланах.\n";
    }

    game.printClan(2);

    return 0;
}
