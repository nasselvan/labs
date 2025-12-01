#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        // Если дней мало то прибыли не будет
        if (prices.size() <= 1) return 0;

        int minPrice = prices[0]; // минимальная цена, которую видели до текущего дня
        int maxProfit = 0;        // максимальная возможная прибыль

        // bltv gj lyzv
        for (int i = 1; i< prices.size(); i++) {
            if (prices[i] < minPrice) {
                minPrice = prices[i];
            }
            else {
                int profit = prices[i] - minPrice;

                if (profit > maxProfit) {
                    maxProfit = profit;
                }
            }
        }

        return maxProfit;
    }
};

int main() {
    Solution s;

    vector<int> prices = {7, 1, 5, 3, 6, 4};

    cout << s.maxProfit(prices); 

    return 0;
}
