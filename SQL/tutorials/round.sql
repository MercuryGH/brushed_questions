-- 编写 SQL语句，从 Products 表中返回 
-- prod_id、prod_price 和 sale_price。
-- sale_price 是一个包含促销价格的计算字段。
-- 提示：可以乘以 0.9，得到原价的 90%（即 10%的折扣）

select prod_id,
  prod_price,
  round(prod_price * 0.9, 3) as sale_price -- 四舍五入到小数点后3位
  -- 其实直接用 prod_price * 0.9 就完事了
from Products