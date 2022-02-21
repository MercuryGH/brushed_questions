# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

import collections

class Solution:
    @staticmethod
    def dfs(root: TreeNode, curr: int, prefix: collections.defaultdict, targetSum: int) -> int:
        if root is None:
            return 0

        ret = 0
        curr += root.val
        ret += prefix[curr - targetSum]
        prefix[curr] += 1
        ret += Solution.dfs(root.left, curr, prefix, targetSum)
        ret += Solution.dfs(root.right, curr, prefix, targetSum)
        prefix[curr] -= 1

        return ret

    def pathSum(self, root: TreeNode, targetSum: int) -> int:
        prefix = collections.defaultdict(int)
        prefix[0] = 1

        return Solution.dfs(root, 0, prefix, targetSum)