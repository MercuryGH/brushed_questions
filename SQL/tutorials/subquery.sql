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



-- 返回产品名称和每一项产品的总订单数
select prod_name, count(order_num) as orders
from Products left join OrderItems
on Products.prod_id = OrderItems.prod_id
group by prod_name
order by prod_name


select Vendors.vend_id, count(prod_id) as prod_id
from Vendors left join Products
on Products.vend_id = Vendors.vend_id
group by Vendors.vend_id
order by Vendors.vend_id