#include <vector>
#include <string>
using std::string;
using std::vector;

/**
 * 单词搜索
 * 基础棋盘DFS题目
 */
class Solution
{
    const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    int n, m;
    string word;
    int targetLength;
    bool success;

    bool outOfBound(int x, int y)
    {
        return x < 0 || x >= n || y < 0 || y >= m;
    }
    void dfs(const vector<vector<char>> &board, vector<vector<bool>> &vis, int x, int y, string &curStr, int curLength)
    {
        if (outOfBound(x, y))
        {
            return;
        }
        if (success == true)
        {
            return;
        }
        if (curLength == targetLength)
        {
            success = true;
            return;
        }

        for (const auto &dir : dirs)
        {
            const int nx = x + dir[0];
            const int ny = y + dir[1];
            if (outOfBound(nx, ny) == false && vis[nx][ny] == false)
            {
                const char nChar = board[nx][ny];
                if (nChar == word[curLength])
                {
                    curStr.push_back(nChar);
                    vis[nx][ny] = true;
                    dfs(board, vis, nx, ny, curStr, curLength + 1);
                    vis[nx][ny] = false;
                    curStr.pop_back();
                }
            }
        }
    }

public:
    bool exist(vector<vector<char>> &board, string word)
    {
        this->n = board.size();
        this->m = board[0].size();
        this->word = word;
        this->success = false;
        this->targetLength = word.length();

        vector<vector<bool>> vis = vector(n, vector<bool>(m, false));

        string curStr;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                const char nChar = board[i][j];
                if (nChar == word[0])
                {
                    curStr.push_back(nChar);
                    vis[i][j] = true;
                    dfs(board, vis, i, j, curStr, 1);
                    vis[i][j] = false;
                    curStr.pop_back();
                    if (success)
                    {
                        return true;
                    }
                }
            }
        }
        return success;
    }
};