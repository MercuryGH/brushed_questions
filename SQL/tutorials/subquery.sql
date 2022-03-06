-- 返回购买价格为 10 美元或以上产品的顾客列表

-- 1. 子查询法
select distinct cust_id
from Orders
where order_num in (
    select order_num
    from OrderItems
    where item_price >= 10
)

-- 2. join 法（推荐）
select distinct Orders.cust_id
from OrderItems, Orders
where OrderItems.order_num = Orders.order_num and
    OrderItems.item_price >= 10

select cust_id, sum(item_price * quantity) as total_ordered
from OrderItems, Orders
where OrderItems.order_num = Orders.order_num
group by cust_id
order by total_ordered desc

