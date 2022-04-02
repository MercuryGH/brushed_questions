import collections
import itertools
from typing import List, Final

class Solution:
    def mostVisitedPattern(self, username: List[str], timestamp: List[int], website: List[str]) -> List[str]:
        # 首先, 记录每个用户访问过的页面, 并按照时间先后顺序排序. 通过combinations排列组合的方式, 记录每个页面三元组对应的用户集合. 根据用户集合大小逆序排序, 字典序升序排序后的第一项即为所求. 
        # 时间O(N^3), 假设有 k个不同的人, 那么每个人平均访问的网站数为 n/k, 排列组合的复杂度为O((n/k)^3), 加上外层遍历用户的复杂度为O(n^3/k^2). 空间O(N^3)：根据时间复杂度的分析, 所有路径的最大数量为n^3, 所以记录路径的哈希表的空间复杂度为O(N^3)
        n: Final = len(username)
        # key为用户名, value为 (访问时间, 页面) 的列表, 且value按照访问时间排序
        m_dict = collections.defaultdict(list)  # key: any, value: list（value的默认值为空list）
        # 存储用户访问记录, 此步骤O(N)
        for i in range(n):
            m_dict[username[i]].append((timestamp[i], website[i]))
        
        # 此步骤O(N^2), 因为需要遍历O(N)的列表, 而每个key对应的数组最高是O(N)长度
        for key in m_dict:
            m_dict[key].sort() # 元组排序
        # key为页面的三元组, value为按顺序访问过该三元组的用户的集合（要去重）
        patternUser = collections.defaultdict(set)

        # 获取每个三元组的用户集合
        for key, value in m_dict.items():
            # e.g. value = [(1, 'home'), (2, 'about'), (3, 'career'), (4, 'gaming')]
            for combined in itertools.combinations(value, 3):
                # e.g. combined = ((1, 'home'), (2, 'about'), (3, 'career'))
                siteName = (combined[0][1], combined[1][1], combined[2][1])
                # e.g. key_from_tuple = ()
                patternUser[siteName].add(key)
        # 首先按照用户集合大小逆序排序, 相同情况按照按字典排序
        res = sorted(patternUser, key=lambda x:(-len(patternUser[x]), x))
        return res[0]

'''
给定两个字符串数组 username和website和一个整数数组timestamp。给定的数组长度相同, 其中元组 [username[i], website[i], timestamp[i]]表示用户 username[i] 在时间 timestamp[i] 访问了网站 website[i] 。

访问模式 是包含三个网站的列表(不一定是完全不同的)。

例如, ["home",  "away",  "love"],  ["leetcode",  "love",  "leetcode"], 和 ["luffy",  "luffy",  "luffy"] 都是模式。
一种 访问模式 的 得分 是访问该模式中所有网站的用户数量, 这些网站在该模式中出现的顺序相同。

例如, 如果模式是 [“home”, “away”, “love”] , 那么分数就是用户数量 x , x 访问了 “home” , 然后访问了 “away” , 然后访问了 “love” 。
同样, 如果模式是 ["leetcode",  "love",  "leetcode"] , 那么分数就是用户数量 x , 使得 x 访问了"leetcode", 然后访问了 "love" , 之后又访问了 "leetcode" 。
另外, 如果模式是 [“luffy”, “luffy”, “luffy”] , 那么分数就是用户数量 x , 这样 x 就可以在不同的时间戳上访问 “luffy” 三次。
返回 得分 最大的 访问模式 。如果有多个访问模式具有相同的最大分数, 则返回字典序最小的。
'''