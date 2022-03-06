-- 以下代码在 MySQL > 5.7 上可能保存。
-- 因为 ONLY_FULL_GROUP_BY 要求 group by 后面的字段
-- * 必须在 select 里面出现
-- * 或者必须被聚合函数包裹

select prod_name, sum(quantity) as quant_sold
from Products, OrderItems
where Products.prod_id = OrderItems.prod_id
group by prod_id