#include <vector>
#include <string>
using std::vector, std::string;

/**
 * 蜡烛之间的盘子
 */
class Solution
{
public:
    vector<int> platesBetweenCandles(string s, vector<vector<int>> &queries)
    {
        const int n = s.length();
        vector<int> prefix(n, -1);
        for (int i = 0, sum = 0; i < n; i++) {
            if (s[i] == '*') {
                sum++;
            }
            if (s[i] == '|') {
                prefix[i] = sum;
            }
        }
        vector<int> leftFirst(n);
        vector<int> rightFirst(n);
        for (int i = 0, l = -1; i < n; i++) {
            if (s[i] == '|') {
                l = i;
            }
            leftFirst[i] = l;
        }
        for (int i = n - 1, r = -1; i >= 0; i--) {
            if (s[i] == '|') {
                r = i;
            }
            rightFirst[i] = r;
        }

        vector<int> ans;
        for (const auto &query : queries) {
            const int l = query[0];
            const int r = query[1];
            const int i = rightFirst[l];
            const int j = leftFirst[r];
            if (i == -1 || j == -1 || i >= j) {
                ans.push_back(0);
            } else {
                ans.push_back(prefix[j] - prefix[i]);
            }
        }
        return ans;
    }
};
/**
 * class Solution {
public:
    vector<int> platesBetweenCandles(string s, vector<vector<int>>& queries) {
        int n = s.length();
        vector<int> preSum(n);
        for (int i = 0, sum = 0; i < n; i++) {
            if (s[i] == '*') {
                sum++;
            }
            preSum[i] = sum;
        }
        vector<int> left(n);
        for (int i = 0, l = -1; i < n; i++) {
            if (s[i] == '|') {
                l = i;
            }
            left[i] = l;
        }
        vector<int> right(n);
        for (int i = n - 1, r = -1; i >= 0; i--) {
            if (s[i] == '|') {
                r = i;
            }
            right[i] = r;
        }
        vector<int> ans;
        for (auto& query : queries) {
            int x = right[query[0]], y = left[query[1]];
            ans.push_back(x == -1 || y == -1 || x >= y ? 0 : preSum[y] - preSum[x]);
        }
        return ans;
    }
};*/