//для литкода
/*суть: даем каждому по 1 конфете,
проходим слева направо: если рейтинг правого больше левого -> правый получает на 1 конфету больше,
проходим справа налево: если рейтинг левого больше правого -> левый получает максимум текущего и правого+1,
и суммируем все конфеты -> минимальное количество, которое нужно.*/

#include <iostream>
#include <vector>
#include <algorithm> 
using namespace std;

class Solution {
public:
    int candy(vector<int>& ratings) {
        int n = ratings.size();
        vector<int> candies(n, 1); // каждому минимум 1 конфета

        // проход слева направо
        for (int i = 1; i < n; i++) {
            if (ratings[i] > ratings[i - 1]) {
                candies[i] = candies[i - 1] + 1;
            }
        }

        // проход справа налево
        for (int i = n - 2; i >= 0; i--) {
            if (ratings[i] > ratings[i + 1]) {
                candies[i] = max(candies[i], candies[i + 1] + 1);
            }
        }

        int total = 0;
        for (int c : candies) total += c;
        return total;
    }
};

int main() {
    Solution s;
    int n;
    cout << "Enter number of children: ";
    cin >> n;

    vector<int> ratings(n);
    cout << "Enter ratings: ";
    for (int i = 0; i < n; i++) {
        cin >> ratings[i];
    }

    int result = s.candy(ratings);
    cout << "Minimum candies needed: " << result << endl;

    return 0;
}
