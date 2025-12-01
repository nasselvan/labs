#include <iostream>
using namespace std;

class Solution {
public:
    // Функция вычисляет количество способов подняться по лестнице
    int climbStairs(int n) {
        if (n <= 2) return n;
        int prev1 = 2;  
        int prev2 = 1;  
        int cur = 0;    //  результат для текущей ступени

        for (int i = 3; i <= n; i++) {
            cur = prev1 + prev2;
            prev2 = prev1;
            prev1 = cur;
        }

        // количество способов добраться до n ступени
        return cur;
    }
};

int main() {
    Solution s;

    int n;
    cin >> n;

    cout << s.climbStairs(n);

    return 0;
}
