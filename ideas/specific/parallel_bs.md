### Parallel binary search

We know we can solve a query using binary search on a monotonic predicate, that is,
finding the first `X` that, after applying to our state `S` all updates that happen until `X`, 
a predicate `P` that queries `S` evaluates true.  
  
Define `f([u1, u2, ...])` for applying updates `u1, u2, ...` on `S`, returning a new state.
And `g: STATE -> ?` the query function on the output of `f`.  
  
Given that updates `[u1,u2,...,uX]` occour until `X`, we want the first `X` s.t. `P(g(f([u1,u2,...,uX])))` is true.  
  
Now, we have **multiple queries `qi`** and want to evaluate for each of these a predicate `P_qi`.
  
When searching in `L...R` for queries `q0, q1, q2`,  it must be that either  
**1.** Given that `U` comprises all udpates from `0...L-1`, `f(U)` has already been applied to `S`  
**2.** `P_qi` accounted updates from `0...L-1`  
  
If **1**, the pseudocode is as follows (for each `P_qi`, we are searching for the first index that evaluates true)  
``` 
binary_search(L,R,queries):
    mid = (L+R)/2
    apply updates in L...mid to S
    evaluate P_qi from queries and partition these depending on the output
    binary_search(mid+1,R,queries w/ P_qi=0)
    unapply updates in L...mid from S
    binary_search(L,mid,queries w/ P_qi=1)
```
If **2**,
```
binary_search(L,R,queries):
    mid = (L+R)/2
    apply updates in L...mid to S
    evaluate P_qi from queries and partition these depending on the output
        update P_qi accounting processed updates
    unapply updates in L...mid from S
    binary_search(L,mid,queries w/ P_qi=1)
    binary_search(mid+1,R,queries w/ P_qi=0)
```

#### Under which conditions can **2** be implemented?
We are focusing on the mainstream case that `P: g(f([u1, u2, ...])) >= T_q` where `T_q` is a threshold for the current query `q`.  
  
Let's call `X` the answer for `q`. 
We want to apply updates `[u1, u2, ...]` from `0...X` in chunks (*associative*).
And queries in each of these chunks will be used for decrementing `T_q` (*inverse*).  
  
Thus, there must be a `h: (INT,) -> INT` s.t. `h(g(f([u1])), g(f([u2])), ...) = g(f([u1,u2,...]))`.  
Also, outputs from `g` must be inversible under `h` i.e. `h(g(f(U)), INV(g(f(U)))) = g(f([])) = NEUTRAL`.  
Thus,
```
P: g(f([u1, u2, ...])) >= T_q  <=>
P: h(g(f([u1])), g(f([u2, ...]))) >= T_q <=>
P: h(INV(g(f([u1]))), g(f([u1])), g(f([u2, ...]))) >= h(INV(g(f([u1])), T_q) <=>
P: g(f([u2, ...])) >= h(INV(g(f([u1])), T_q)
```

Examples:
1. `S:` BIT, `f`: range update sum, `g:` point query; `h:` sum
2. `S:` DSU, `f`: union, `g:` number of different values of a component; `h:` undefined
3. `S:` DSU, `f`: union, `g:` map counting occourence for each value; We can only define `h: MAP -> MAP` i.e. `h: INT^dim -> INT^dim`.

#### Extra dimension for visibility: process updates and queries simultaneously
Let's say that besides the `BDIM` (dimension where we will binary search), there is a `VIS_DIM` (dimension controlling visibility).
You will need to process updates and queries at the same time in order to let only the correct/visible updates avaiable when processing a query.  
If this is the case, strategy **2** needs to be implemented.
  
Sorting updates in `VIS_DIM` and keeping this order is efficient since we will process updates in this order along the recursions.
Instead of keeping updates accessible by their indexes in `BDIM`, keep them as parameters (as done w/ queries) and
partition them into `left` and `right` while processing them.
That is, instead of partitioning them beforehand, do it online.
  
However, it may be that `S` itself can handle multiple dimensions, what allows strategy **1**.

#### Unapplying updates: rollback or inverse
In any case, rollback can be applied in order to undo the applied updates from `L...mid`.
  
However, if the update operation is inversible, the inverse update operation may be simpler to implement.
Note that, depending on commutativity, different orders of inverse operations need to be applied.
