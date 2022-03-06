from typing import List

class Solution:
    def cellsInRange(self, s: str) -> List[str]:
        start, end = s.split(':')
        char1 = chr(start[0])
        char2 = chr(end[0])
        digit1 = start[1]
        digit2 = end[1]

        ans = []
        for i in range(digit1, digit2 + 1):
            for j in range(ord(char1), ord(char2) + 1):
                curChar = chr(j)
                ans.append(j + i)
        return ans

