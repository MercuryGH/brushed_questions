from cgitb import small
from typing import List

class Solution:
    @staticmethod
    def calcConsecutiveSum(start: int, count: int):
        return count * (start + start + count - 1) // 2

    def minimalKSum(self, nums: List[int], k: int) -> int:
        n = len(nums)
        if n == 0:
            numsSum = 0
            minNum = 1
            maxNum = 0
        else:
            nums.sort()
            numsSum = sum(nums)
            minNum = nums[0]
            maxNum = nums[-1]

        ans = 0
        smallRange = minNum - 1 # 从1数起加 smallRange 个数
        ans += Solution.calcConsecutiveSum(1, min(smallRange, k))
        k = max(k - smallRange, 0)
        for i in range(n - 1):
            rangeStart: int = nums[i] + 1
            rangeEnd: int = nums[i + 1] - 1
            if rangeStart > rangeEnd:
                continue
            # 从rangeStart counts rangeEnd - rangeStart
            rangeCount = rangeEnd - rangeStart + 1
            ans += Solution.calcConsecutiveSum(rangeStart, min(rangeCount, k))
            k = max(k - rangeCount, 0)

        ans += Solution.calcConsecutiveSum(nums[-1] + 1, k)
        return ans

s = Solution()

nums = [1,4,25,10,25]
k = 2
nums = [5,6]
k = 6
print(s.minimalKSum(nums, k))