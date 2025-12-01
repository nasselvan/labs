#include <iostream>
#include <vector>
using namespace std;

// f считает количество единиц в бинарной записи чисел от 0 до n
class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> ans(n + 1); // создаём массив от 0 до n

        ans[0] = 0; // в числе 0 нет единиц

        for (int i = 1; i <= n; i++) {
            // ans[i >> 1] — это количество единиц в числе i/2
            ans[i] = ans[i >> 1] + (i & 1);
        }

        return ans;
    }
};

int main() {
    Solution s;

    int n;
    cin >> n;  

    vector<int> res = s.countBits(n); 
    for (int x : res) {
        cout << x << " ";
    }

    return 0;
}
