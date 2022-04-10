from typing import List, Final

class Solution:
    def filterStr(str, l, r) -> str:
        n = len(str)
        res = ''
        for i in range(l):
            res += str[i]
        for i in range(r, n):
            res += str[i]
        return res
            
    def deleteText(self, article: str, index: int) -> str:
        cursor = article[index]
        if cursor == ' ':
            return article

        article = ' ' + article + ' '
        index += 1
        n: Final = len(article)
        l = 0
        r = 0
        for i in range(n):
            if article[i] == ' ':
                if i < index:
                    l = i
            if article[i] == ' ':
                if i > index:
                    r = i
                    break
        print(l, r)
        
        article = Solution.filterStr(article, l, r).strip()
        return article
            
s = Solution()
print(s.deleteText("Hello", 0))

