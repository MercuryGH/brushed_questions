-- 返回 2020 年 1 月的所有订单的订单号和订单日期

select order_num, order_date
from Orders

where date_format(order_date, '%Y%m') = '202001' 
-- 或者等价地 month(order_date)='01' and year(order_date)='2020'

order by order_date