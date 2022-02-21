from typing import Collection

class Solution:
    def reorganizeString(self, s: str) -> str:
        sLength = len(s)
        if sLength < 2:
            return s

        charCount = Collection.Counter(s)
        maxCount = max(charCount.values())
        if maxCount <= (sLength + 1) // 2:
            retArray = [""] * sLength
            oddIndex, evenIndex = 1, 0
            for char, count in charCount.items():
                while count > 0 and count <= sLength // 2 and oddIndex < sLength:  # 给其他字母放奇数下标位置
                    retArray[oddIndex] = char
                    count -= 1
                    oddIndex += 2
                while count > 0:  # 给出现最多的字母放偶数下标位置
                    retArray[evenIndex] = char
                    count -= 1
                    evenIndex += 2
            return "".join(retArray)  # array.stringify
        else:
            return ""
