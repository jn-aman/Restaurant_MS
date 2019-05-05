# Paradise - Restaurant referral and Delivery(C++)
This project main functionalities are:

1. A rating based system to award customers on their orders and referral with 4 level rating increment using k- array trees.

2. Order Delivery option, find the best possible cycle in the city graph using Dijkstra's Algorithm.

# Algorithms:
1. Find the shortest cycle so as to cover the marked nodes, in minimum time possible by applying dijkstra's algorithm after reaching each marked node.In this algorithm 
   ,first a map is made with key as city_index and value as no of cities this city_index is connected to and distance from each city.Thereafter, we first find the 
    shortest city that is marked true on the destination array. and then we find the path to this shortest city.After that, we make this shortest city as source and mark
    false for this city on the destination array. and recur over the remaining destination.
    The path to this shortest city is calculated using dijkstra's algorithm.  
2. Implemented a referral program (using k- array tree data structure) to increment the rating of all referrer upto 4 level.


3. Most popular dish is updated after each order, is implemented using heap and hash map.
   Here a heap is maintained to keep track of the item that are mostly ordered i.e., heap is maintained in terms of particular item_no order count.
4. A rating system(mcoupons) is implemented to provide discount to customers on the basis of their orders and no of referrer they have.In this rating system, 
   initially all customers start with a rating of 100. Let's say a customer is total bill amount is 250,
   then 
                                    new_rating  = old_rating + 20% of total_bill_amount;
   and then the customers are asked how much of the available m_coupons they want to use; then 
                                    Total amount payable = total_bill_amount + 10% of rating_value_used.
   Also the rating of a customer increases (or updated) when any other new customer uses the ref_id of the former as described in the referral program.    
   

Data structures and STL used:
1. unordered_map
2. pair
3. vector
4. heap
5. k-array Tree
6. graph
7. Linked list
8. queue
9. string 

File handling is used to store all the important and relevant details like 
customers tree(k-array tree), store the graph of city, store the most popular dishes,e.t.c.
