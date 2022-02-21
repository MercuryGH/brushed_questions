#include <string>
#include <vector>
#include <algorithm>
#include <queue>

class Solution
{
public:
    /**
     * 不使用堆，每次都用std::sort()找当前最能用的字母，在字母数目 n 多的时候效率低
     * 对于本题，由于只有三个字母（n = 3），所以反而可能比较快
     */
    std::string longestDiverseStringTrivial(int a, int b, int c)
    {
        std::string ans;
        // 记录还能放多少个 字母，注意这个不是字典！！
        std::vector<std::pair<int, char>> arr = {{a, 'a'}, {b, 'b'}, {c, 'c'}};

        while (true)
        {
            const auto cmp = [](const std::pair<int, char> &x, const std::pair<int, char> &y)
            {
                return x.first > y.first; // 优先放能放多的
            };

            std::sort(arr.begin(), arr.end(), cmp);
            bool hasNext = false;

            for (auto &[freq, ch] : arr)
            {
                const int m = ans.size();
                if (freq <= 0)
                {
                    break;
                }
                if (m >= 2 && ans[m - 2] == ch && ans[m - 1] == ch) // 出现第一多的字符串被占用
                {
                    continue; // 选择出现第二多的字符串
                }
                hasNext = true;
                ans.push_back(ch); // 或者使用 += 运算符
                freq--;            // 在这种 for 循环中可以修改 key
                break;
            }
            if (hasNext == false)
            {
                break;
            }
        }
        return ans;
    }

    /**
     * 使用优先队列（最大堆）优化，在 n 大时效率显著高
     */
    std::string longestDiverseString(int a, int b, int c)
    {
        std::priority_queue<std::pair<int, char>> pq;
        if (a > 0)
            pq.push({a, 'a'});
        if (b > 0)
            pq.push({b, 'b'});
        if (c > 0)
            pq.push({c, 'c'});
        std::string ans;

        while (pq.empty() == false)
        {
            std::pair<int, char> firstP = pq.top();
            pq.pop();

            const int m = ans.size();
            const char ch = firstP.second;
            if (m >= 2 && ch == ans[m - 1] && ch == ans[m - 2])
            {
                if (pq.empty() == true) {
                    break;
                }

                std::pair<int, char> secondP = pq.top();
                pq.pop();
                pq.push(firstP);  // 装回去，本次不需要用你

                const char alteredCh = secondP.second;
                ans.push_back(alteredCh);
                const int alteredFreq = secondP.first - 1;

                if (alteredFreq > 0) {
                    pq.push({alteredFreq, alteredCh});
                }
            }
            else
            {
                ans.push_back(ch);
                const int freq = firstP.first - 1;
                if (freq > 0) {
                    pq.push({freq, ch});
                }
            }
        }
        return ans;
    }
};