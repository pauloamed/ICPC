# Ideas
Summary of some ~not so~ frequent ideas

```
Q is necessary for P (P => Q): If (P => Q), it is impossible P without Q.
P is sufficient for Q (P => Q)
P is sufficient and necessary for Q, (P => Q) and (Q => P)
```

## General

### System of Difference Constraints
Given is a list of **inequalities** in the form:
```
x_i - y_i <= T_i
x_i, y_i <= N
```
That is a system of inequalities (a positive variable and a negative `<=` a threshold) of differences between 2 of `N` variables.  
Satisfying these constraints can be done by using the shortest path algorithm:
- For each inequality, create an edge from the negative variable `y_i` to the positive `x_i` with cost `T_i`
- Create a phantom node `0` and create edges w/ cost `0` from this node to every other node
- Run shortest path w/ negative edges. If there is a negative cycle, it is not feasible

**Note**: equality can be represented by 2 inequalities

#### Solving *The army of Thutmose III*
Ww have `M` intervals `[l;r]` and we want to know if we can turn some numers `x` on in order that
- The number of active elements inside each interval is at least 1
- The number of active elements inside each interval is at most `K`

For this:
- The number of elements inside a interval can be represented as a difference in the prefix sum vector
- Defining that a position has at most one element can be represented as a difference between variable. The same goes for "not negative".
- Solve using the system of difference constraints
  
Check: https://codeforces.com/gym/103934/problem/A

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

### Maximum size with bounded cost
Can also be solved finding minimum cost for each size and taking the greatest size with cost inside the bounds.

### Median on sub-arrays `[TODO]`
https://codeforces.com/blog/entry/18879?#comment-238126

### Use offset in structures for values
If modifying values kept in a structure by subtracting/adding `x` at each iteration, instead of updating the stored values, create an offset for both stored values and values to be stored comprising such modifications.
  
Check: https://atcoder.jp/contests/agc024/submissions/33929120

### Paint grid with squares in `O(W*H)`
Let's say we are painting the whole grid from bottom to top, left to right. Then, the bottom-left corner of each square of side `L` will keep a latent painting `L`. 
When you visit a point w/ latent painting `X`, paint the square of the current point and set a latent painting of `X-1` at upper and right. 
This set is actually a `max` since a point can be visited/updated by multiple other points.

### Make array `A` equal to `B`: change `a[j], j \in [l;r]` into `a[i]`, `i \n [l;r]`
Operation: Substitute each element inside a range `[l;r]` with an element (which element? depends on the problem dur) from this range.
Compressed values: elements in the order they appear, without duplicates: 1 1 2 4 2 2 5 5 3 => 1 2 4 2 5 3

A necessary (but not sufficient) condition is that (i.e. there is only a solution if) compressed values from `B` are a subsequence from `A`.  
The operation can only delete elements from the compressed values of `A`; no new element is created.
  
Moreover, depending on the operation, the range each value can occupy can be freely modified, turning the transformation feasible (sufficient).
  
Check: https://codeforces.com/gym/101964/problem/F

### RMQ query on slinding window
Min (or max) heap with lazy delete; keep adding while you slide through.

### Maximize active variables with clauses `NAND`
`A NAND B`: `A` or `B` but not both. This reduces to maximum independent set where edges are such clauses.
  
Check: https://codeforces.com/gym/101666/problem/E

### Quadratic functions in linear models
**TODO** (https://codeforces.com/gym/102644/problem/G)
In linear contexts (linear recurrences, min cost max flow), the quadratic function `i^2` can be modelled as the sum of the `i` first odd numbers.

### Pidgeon principle on complexity analysis
Check: https://atcoder.jp/contests/abc260/tasks/abc260_f

### `min(x, n - x)`
You are given a list of elements that have a linear order and that compose a recursive structure (eg. list of tree elements in inorder).
You want to divide and conquer these elements. However, splitting them into the recursive calls isn't trivial.
We can apply `min(x,n-x)` if there is a search algorithm that traverses these elements following the given order for finding a delimiter and thus splitting.
Instead of searching in only one direction with 1 pointer in `O(x), x <= n`, we will use 2 pointers w/ opposite direction, one starting at the beggining and the other at the end (we will traverse these elements following the given order and its reverse). 
Now, the cost of this search is `O(min(x,n-x))`.

Note that:
- We will split the elements of the current call (`all`) into 2 sets: `small` and `large`. 
  - `small`: elements visited in the direction in which the delimiter was found (`all` >= 2*`small`)
  - `large`: the remaining. 
  - `all` will be splitted into these two disjoint sets for the child calls. 
- For each call, we don't traverse more than `O(|small|)` elements.
- An element is at most at `O(logN)` `small` sets: from bottom to top, these sets have their size at least doubled (union-by-size); their sizes don't exceed `N`.
- For each `small` element in a call, we execute a `O(C)` operation (eg. adding to a set, sorting).
- The final cost is bounded by the sum of `small` sets along the divide and conquer
Thus, the final cost is:
```
N: number of elements
log(N): max. number of small sets an element is
C: cost of operation per element inside a small set
= N*log(N)*C
```

In some problems, both original and reverse order can be expressed inside the same list that will be traversed in forward in backward directions.
However, in some less trivials problems, one list for each direction (original and reverse order) need to be build.
For such cases, we will still traverse in both direciton simultaneously, but we need to know which elements will be passed for the child calls, since a simple suffix/preffix split won't work.
What can be done is:
1. Create new lists for the `small` elements, sort if necessary (`C=log(N)`).
2. Solve for the `small` set
3. Delete the `small` set elements from `all`. Can be done with lazy deleting.
4. Solve `large`. Use `all` as `large`, orders are preserved after deleting in (3).
 
### D-query offline
D-query: number of different elements in a given interval
Sort queries by `r` (1), keep a structure for querying the sum on a range on a binary vector (2) and, for each interval, keep only (3) the greatest position `<= r` active in such vector(4).
Given a `[lq;rq]` query, each element will only be counted once in such vector (3) and it will be counted if inside the query interval (1 and 4). The sum on `[lq;rq]` in such vector (2) is the answer.

### Number of intersections between intervals
Given are blue and red intervals as `[l;r]`. You want to know how many pairs `(a,b)` exist s.t. `a` is a blue interval and `b` is a red interval and `a` and `b` intersects. Naivelly, this is `O(n*m)` but we can do faster.
  
Let's say that `a` intervals are fixed and `b` intervals are queries. We want the sum of queries of the type: number of intervals active in `[lq;rq]`. We can solve this using preffix: Number of intervals that opened until `rq` minus number of intervals that closed until `lq-1`.
  
Check: https://codeforces.com/gym/102433/problem/G

### Sum between linear functions and between line segments
The sum between linear functions is also a linear function.  
The sum between `N` line segments (summing their `y` values) leads to a function which can be decomposed into at most `2N` line segments.  

A line sweep can be done storing the ongoing accumulated slope and `y`. 
A line segment can be expressed as a slope, the starting `y` offset and the final `y` offset. 
Decompose a line segment into activation and deactivation points at their starting and ending times respectively.
Activating is adding the starting `y` offset to `y` and the slope to the accumulated slope at time `t_start`.  
Deactivating is removing the final `y` offset from `y` and the slope from the accumulated slope at time `t_end`.

When processing a point in the line sweep, update values as (assume that deactivations will have negative event values):
```
y = y + slope * (event_t - last_t) + event_y_offset
slope += event_slope
last_t = event_t
```
Miminals and maximals will occur only in activation and deactivation points.
  
Check: https://codeforces.com/gym/102433/problem/J

### Reduce the number of variables in conditions (invariants)
**Building a sequence**  
Let's say we have the following condition `|a_j - a_i| <= v(t_j - t_i)` for building a sequence.  
  
This can be manipulated to `a_j - a_i <= vt_j - vt_i` and further to `a_j - vt_j <= a_i - vt_i`. 
If we define `x_i = a_i - vt_i`, we can reduce this to `x_j <= x_i`.
  
Similarly, this can be manipulated to `a_i - a_j <= vt_j - vt_i` and further to `a_j + vt_j <= a_i + vt_i`. 
If we define `y_i = a_i + vt_i`, we can reduce this to `y_j <= y_i`.
  
These two (`x_i` and `y_i`) were possible since `|a-b| <= T iff a-b <= T AND b-a <= T`. 
We are now trying to build the longest (non-strictly) increasing subsequence following `x_i <= x_j AND y_i <= y_j`.
  
If there are multiple conditions `AND`, it is feasible to reduce these to `(x_i <= x_j, y_i <= y_j, ...)`  and solve this as the longest increasing subsequence of tuples.

Check: https://codeforces.com/contest/1662/problem/L

**Count intervals w/ ratio > `X`**  

Another example using preffixes. Count the number of intervals `[L;R]` s.t. the ratio of active bits over its size is greater than `X`:
```
sum_1 / sz > x <=> (sum_r - sum_l) / (r - l) > x <=> 
(sum_r - sum_l) > x (r - l) <=> sum_r - sum_l > xr - xl <=> 
sum_r - sum_l > xr - xl <=> sum_r - xr > sum_l - xl <=> 
y_r > y_l
```  
Check: https://codeforces.com/gym/102134/problem/D

### Longest increasing subsequence of tuples (`x_i < x_j`, `y_i < y_j`, ...).
This is the longest chain of `tuple_i` s.t. `tuple_i` "dominates" `tuple_i-1`. Solve using CQD, BITs, sorting, ...

### Paths down-right on a grid while summing elements
Take a 2D grid and a path with sum `sum` going either down or right on it. `a_ij` of this grid has a value and passing through `(i,j)` adds it to `sum`. Note that each diagonal is visited exactly once in a path.  

From a path you can go to an adjacent path by replacing a cell on diagonal `D` to another cell in `D` adjacent to it. Note that the removed cell needs to be a corner cell; otherwise, the path disconnects. Also, with such operation you can visit all possible paths. 
  
What happens to `sum` when you switch paths? What happens to its parity? Is the range of possible `sum` values contiguos?

### Don't put `x` and `y` in the same set (there are 2 sets)
Create a graph `G` such that if `x` and `y` can't be together, there is an edge `(x,y)` in it. We thus want to check if this graph is bipartite.

### Matchings and sums
Lets say we have sets `A` and `B` and we are assigning elements from `B` to `A`. Each element from `B` can only be assigned to one in `A`.  
If `cost(a) = sz(b) + cost(b)`, i.e. the cost of assiging `b \subset B` to element `a` equals to a `cost(b)` plus `sz(b)`,
- Then we can update values in `B` with `-1` since this value will always be accounted in the final result.
- It is like every element has a contribution to `sz(b)` and, since element will be used **exactly** once, we can compute this contribution beforehand.

### Inverting bits of subarrays
If you have a bit-array `a` and do operations of subarrays bit inversion, there is a bijection to it:
- use the transformed array `b[i] = a[i - 1] ^ a[i]`
- inverting `[l:r]` in `a` is equivalent to inverting `b[l]` and `b[r+1]`
  
Check: https://codeforces.com/gym/101519/problem/D  

## Structures

### Query which intervals contain a number
We want to keep intervals in a structure and query which intervals contain an integer `x`.  
Create a sort of Segment Tree in which each node of this scructure keeps a set of intervals.  
Update: Insert interval `(a;b)` into the `O(log)` nodes `[l;r]` maximals inside `(a;b)`.  
Query: The intervals from all nodes from root to the leaf (`x`) contain `x`.
If we need to delete the queried intervals after finding them, a lazy delete is needed since one interval can be in multiple nodes.  

Check: https://codeforces.com/contest/786/problem/B

### Color update, values converging after small time
Let's suppose we are keeping a set of intervals and performing 2 types of updates on a range `[L;R]`: `set` and `op`.  
If `op` leads to convergence to a single value in `O(C)`, one can still use the color update structure.
A new segment is inserted `O(N + Q)` times and a segment is updated `O(C)` times (until it merges). 
Every visited segment is either updated or deleted. One can only delete inserted segments. Thus, summing the cost for each segment, we have `O((N+Q)*C*logN)`  

**Note:** dividing by `K` or successive `phi()`, `C=log`
  
Check: https://atcoder.jp/contests/abc256/tasks/abc256_h

## XOR base

### Given that we consumed `N` elements, number of subsets w/ xor `= X`
**First, note that "number of subsets w/ xor `0`" equals `2^(N-B)`**, where `B` is the basis rank. 
This is because
- combinations of only basis vectors wont result 0 since these are independent
- assume we are only observing subsets of non-basis vectors. For each of these, only one combination of basis vectors will null it.

Answering for `xor = X` is similar, but
- If `X` is in SPAN, result is `2^(N-B)`
  - Suppose we are answering for `X=0` and at the end we `xor` all results w/ `basis(X)`
- If not, result is 0 (trivial)

### Allowing dependent vector into the basis - Odd length cycle

We can't add a vector to the basis unless it is independent from the other ones there.  
  
However, if we create a new dimension, and set it to `1` in every vector, we will be able to add a dependent vector to the basis
AS LONG AS it is formed by the combination of an even number of basis vectors.   
This will create an odd-length cycle with this added vector and the ones that formed it.
  
Check: https://codeforces.com/gym/101611/problem/I

# Game theory

### Last to play wins/unwanted positions
If the problem presents this variation, set the "about to win" positions as unwanted positions (really high grundy). Thus, states leading only to such positions will get a losing status.
