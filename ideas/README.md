# Ideas
Summary of some ~not so~ frequent ideas

```
Q is necessary for P (P => Q): If (P => Q), it is impossible P without Q.
P is sufficient for Q (P => Q)
P is sufficient and necessary for Q, (P => Q) and (Q => P)
```

## General

### Median on sub-arrays `[TODO]`
https://codeforces.com/blog/entry/18879?#comment-238126

### Use offset in structures
If modifying values kept in a structure by subtracting/adding `x` at each iteration, instead of updating the stored values, create an offset for both stored values and values to be stored comprising such modifications.
  
Check: https://atcoder.jp/contests/agc024/submissions/33929120

### Paint grid with squares in `O(W*H)`
Let's say we are painting the whole grid from bottom to top, left to right. Then, the bottom-left corner of each square of side `L` will keep a latent painting `L`. 
When you visit a point w/ latent painting `X`, paint the square of the current point and set a latent painting of `X-1` at upper and right. 
This set is actually a `max` since a point can be visited by multiple other points.

### RMQ query on slinding window
Min (or max) heap with lazy delete; keep adding while you slide through.

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
Let's say we have the following condition `a_j - a_i < v(t_j - t_i)` for building a sequence.  
This can be manipulated to `a_j - a_i < vt_j - vt_i` and further to `a_j - vt_j < a_i - vt_i`. 
If we define `x_i = a_i - vt_i`, we can reduce this to `x_j < x_i`.

If there are multiple conditions `AND`, it is feasible to reduce these to `(x_i < x_j, y_i < y_j, ...)`  and solve this as the longest increasing subsequence of tuples.

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

### Tree + inversible operations
First, compute the euler tour of the tree s.t.
- `beg[x]`: time subtree of `x` was entered
- `end[x]`: time subtree of `x` was left
  
When refering to a value `v`, `-v` is it's inverse.
  
**Updtate subtree `x`, query node `y`**
- Update `v` to `beg[x]` and `-v` to `end[x]`
- Query `beg[y]`

**Update node `x`, query path `y-z`**
- Update `v` to `beg[x]` and `-v` to `end[x]`
- Query `beg[y] + beg[z] - beg[LCA(y,z)]`

**Update path `x-y`, query node `z`**
- Update `v` to `beg[x]`, `v` to `beg[y]` and `-v` to `beg[LCA(x,y)]` **2x**
- Query from `beg[y]` to `end[z]`

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
  
Check: https://atcoder.jp/contests/abc256/tasks/abc256_h


## Randomized

### Blogewoosh 6
Given `n` numbers in a random order, the expected times that the maximum seen value changes is `O(log(n))` while processing such numbers.

# Game theory

### Last to play wins/unwanted positions
If the problem presents this variation, set the "about to win" positions as unwanted positions (really high grundy). Thus, states leading only to such positions will get a losing status.
