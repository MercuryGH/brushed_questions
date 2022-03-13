#include <vector>
#include <iostream>
using std::vector;

class Solution {
public:
    /**
     * 将 k 进制数 n 转换为 l 进制
     * n = k^0 * coefs[0] + k^1 * coefs[1] + ...
     * 
     * 返回 n = l^0 * ans[0] + l^1 * ans[1] + ...
     */
    vector<int> transformRadis(const vector<int> &coefs, const int k, const int l) {
        int n = 0;
        int acc = 1;
        for (const int coef : coefs) {
            n += coef * acc;
            acc *= k;
        }

        vector<int> ans;
        while (true) {
            ans.push_back(n % l);
            n /= l;
            if (n == 0) {
                break;
            }
        }
        return ans;
    }
};

int solution(vector<int> &A) {
    vector<bool> hash(100010, 0);
    for (const int num : A) {
        if (num > 0 && num < 100010) {
            hash[num] = 1;
        }
    }

    for (int i = 1; ; i++) {
        if (hash[i] == 0) {
            return i;
        }
    }
    return 1;
}


int main() {
    Solution s;

    vector<int> coefs = {0, 0, 0};
    int k = 10;
    int l = 16;
    auto ans = s.transformRadis(coefs, k, l);
    for (const int num : ans) {
        std::cout << num << " ";
    }

    return 0;
}