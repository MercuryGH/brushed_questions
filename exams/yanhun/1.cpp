#include <algorithm>
#include <ctime>
#include <cmath>
#include <iostream>
#include <list>
#include <memory>
#include <queue>
#include <stack>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using std::vector, std::string;

class Solution
{
    int n;

public:
    void dfs(vector<vector<int>> &isConnected, vector<int> &visited, int i)
    {
        for (int j = 0; j < n; j++)
        {
            if (isConnected[i][j] == 1 && !visited[j])
            {
                visited[j] = 1;
                dfs(isConnected, visited, j);
            }
        }
    }

    int findCircleNum(vector<vector<int>> &isConnected)
    {
        n = isConnected.size();
        vector<int> visited(n);

        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            if (!visited[i])
            {
                dfs(isConnected, visited, i);
                ans++;
            }
        }

        return ans;
    }
};
