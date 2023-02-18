### Evaluation of sums of sliding window on ordered list w/ restricted delta
Let's say we are sliding a window of size `K` through an orderd list of integers.  
If we create a virtual list of the sum for each sliding window,
- it will be a sorted array
- the difference between the `i`-th and `i+1`-th element is `V[k+i] - V[i]`

#### Solving IOI16 - Molecules
- We want a subset of elements which sum is inside `[L;R]`
- **C:** It is guaranteed that `max_val - min_val <= R - L`

**1:**
Observe the answer: let's say the answers has size `k` (size of subset).
Then, if there is an answer of size `k`, in the ordered list of values, it must be that `sum(0:k-1) <= R` and that `sum(n-k:n-1) >= L`.
That is, there is an intersection between intervals `[L;R]` and `[sum(0:k-1); sum(n-k:n-1)]`.  
  - Since `sum(0:k-1) <= R`, `[L;R]` ends after `[sum(0:k-1); sum(n-k:n-1)]` begins  
  - Since `sum(n-k:n-1) >= L`, `[L;R]` starts before `[sum(0:k-1); sum(n-k:n-1)]` ends  
  
**2:** 
Also, consecutive points of these virtual list have distance at most `R-L` (**C**).
Thus, if we iterate through this list, it must be that at least one of such points are inside `[L;R]`.  
- Think of the evaluation of the sliding window as points in a line
  - Per **1**, `[L;R]` intersects w/ the interval between the first and last points
  - Since the distance between consecutive points is at most `R-L`, there can't be a gap greater than the size `[L;R]`
- If the intersection occurs in the beggining or end, the first/last points would be valid answers
- Else, the gap indicates that there will be an intersection
  
Check: https://oj.uz/problem/view/IOI16_molecules  

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

 
### Paint grid with squares in `O(W*H)`
Let's say we are painting the whole grid from bottom to top, left to right. Then, the bottom-left corner of each square of side `L` will keep a latent painting `L`. 
When you visit a point w/ latent painting `X`, paint the square of the current point and set a latent painting of `X-1` at upper and right. 
This set is actually a `max` since a point can be visited/updated by multiple other points.

### RMQ query on slinding window
Min (or max) heap with lazy delete; keep adding while you slide through.

### D-query offline
D-query: number of different elements in a given interval
Sort queries by `r` (1), keep a structure for querying the sum on a range on a binary vector (2) and, for each interval, keep only (3) the greatest position `<= r` active in such vector(4).
Given a `[lq;rq]` query, each element will only be counted once in such vector (3) and it will be counted if inside the query interval (1 and 4). The sum on `[lq;rq]` in such vector (2) is the answer.

### Number of intersections between intervals
Given are blue and red intervals as `[l;r]`. You want to know how many pairs `(a,b)` exist s.t. `a` is a blue interval and `b` is a red interval and `a` and `b` intersects. Naivelly, this is `O(n*m)` but we can do faster.
  
Let's say that `a` intervals are fixed and `b` intervals are queries. We want the sum of queries of the type: number of intervals active in `[lq;rq]`. We can solve this using preffix: Number of intervals that opened until `rq` minus number of intervals that closed until `lq-1`.
  
Check: https://codeforces.com/gym/102433/problem/G
