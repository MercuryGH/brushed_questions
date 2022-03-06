-- 编写 SQL 语句，返回顾客 ID（cust_id）、顾客名称（cust_name）和
-- 登录名（user_login），其中登录名全部为大写字母，
-- 并由顾客联系人的前两个字符（cust_contact）
-- 和其所在城市的前三个字符（cust_city）组成。
-- 提示：需要使用函数、拼接和别名。

-- e.g. (result)
-- cust_id	cust_name	user_login
-- a1	    Andy Li	    ANOAK
-- a2	    Ben Liu	    BEOAK

select cust_id, 
  cust_name,
  upper(concat(left(cust_name, 2), left(cust_city, 3))) as user_login
from Customers