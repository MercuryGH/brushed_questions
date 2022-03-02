'''
贪心模拟题, 脚本语言好做
思路可见
https://leetcode-cn.com/problems/find-the-closest-palindrome/solution/python-tan-xin-da-mo-ni-by-himymben-6cbl/
https://leetcode-cn.com/problems/find-the-closest-palindrome/solution/javascript-jian-dan-si-lu-by-mantoufan-oldl/
'''
class Solution:
    def nearestPalindromic(self, n: str) -> str:
        nLen = len(n)
        if nLen == 1: # 特判
            return str(int(n) - 1)

        halfN = n[: nLen // 2] # n 前半部分（向下取整）
        nInt = int(n)
        possibleResults = set()

        v = int(n[: (nLen + 1) // 2])
        possibleStr1 = str(v - 1)
        possibleStr2 = str(v + 1)

        # 这些东西还是特判
        possibleResults.add('9' * (nLen - 1))
        possibleResults.add('1' + '0' * (nLen - 1) + '1')

        if nLen % 2 == 1: # 奇数
            possibleResults.add(possibleStr1 + possibleStr1[-2::-1])
            possibleResults.add(possibleStr2 + possibleStr2[-2::-1])
        else:
            possibleResults.add(possibleStr1 + possibleStr1[::-1])
            possibleResults.add(possibleStr2 + possibleStr2[::-1])
        
        if n[::-1] != n:
            if nLen % 2 == 1:
                possibleResults.add(halfN + n[nLen // 2] + halfN[::-1])
            else:
                possibleResults.add(halfN + halfN[::-1])

        if n in possibleResults:
            possibleResults.remove(n)

        return min(
            possibleResults, 
            key=lambda x: (abs((k := int(x)) - nInt), k)
            # 注意这里使用了一个二元组作为 key
            # 因为还需要取较小的 k 作为答案，所以还需要第二个比较条件
        )
