#include <algorithm>
#include <random>
#include <cstdlib>
#include <cmath>
#include <vector>
using std::vector;

class Solution {
    void dfs(vector<int> &res, int cur, const int n) {
        if (cur > n) {
            return;
        }
        res.push_back(cur);
        for (int i = 0; i <= 9; i++) {
            dfs(res, cur * 10 + i, n);
        }
    }
    public:
    vector<int> lexicalOrder(int n) {
        vector<int> ans;
        for (int i = 1; i <= 9; i++) {
            dfs(ans, i, n);
        }
        return ans;
    }
};
