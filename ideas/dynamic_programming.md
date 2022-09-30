# Dynamic Programming

#### Basics
In DP problems, we will first have a **functional equation** (`f(x) = ...f(y)...`) that states the optimal modelling. Such is recursive, thus, the need of DP. 
  
We will call `f(x)` the LHS and `...f(y)...` the RHS. Also, we will say that `f(x)` depends on `f(y)`. Note that the relation *depends on* creates a graph on our states.  
  
I guess that in most of the problems this graph is a DAG or at most it has some self loops that are easy to handle.

When solving a DP problem, it **always** has to be clear (it is pointless to keep coding without these):
- **Base case**
- **Functional equation**

As solving a DP is only a smart way of traversing a graph, we need to visit each edge of this graph (transitions of the DP). 
Thus, the cost of a DP is `O(E)`. This actually given `N` (number of states) and `T` (number of transitions), `O(N*T)`.  

Some DP optimizations work aiming to reduce the cost of considering edges for a state:
- Using a query structure for `max`, `min`, `+`, ...
- Using a CHT structure for efficient evaluation of linear functions

#### Pull and push

Assuming our graph of dependence doesn't contain cycles,  
  
Let's say our modelling is something like `f(x) = min(f(y) + c)`. Using the direct method (in oppositon to successive approximation), this can be computed/implemented using **push** or **pull**.  
In the **push** method, we **update `f(x)` while in `f(y)`**. That is, we are pushing values from `f(y)` into `f(x)`. Also, `f(y)` is *contributing* to `f(x)` (more common in sums).
While in the **pull method**, we only **compute `f(x)` only when we reach it**. 

Note that, for both, when we reach `f(x)`, all `f(y)` that `f(x)` depends on must be already computed. 
Note that, when using **memoization (recursive DP)**, we are using the **pull method**.

Depending on the problem, implementing using the pulling may be easier than pushing or vice-versa. One can also combine pushing and pulling in the same modelling.
  
For example, let's say that `f(x) = max_ab(f(a), f(b))`. How can we push here? Note that, while in `a`, trying to push into `x`, computing which state `b` is may be confusing ~(at least I thought so)~. This problem https://codeforces.com/contest/678/problem/E works like this. 
  
Pushing and pulling in the same implementation: https://atcoder.jp/contests/abc242/editorial/3548.

## Modellings

### Independent set on layered graph
Use bitmasks: `dp[i][mask]`: at layer `i` used `mask` from this layer

### `2^n`: find the best permutation if we can build from left to right (linearly)
`dp[i][mask]:` solved `i` first positions of the permutation and used `mask&j=1` elements.

### Knapsack with value_i=1: biggest subset with bounded cost
DP where you maintain `best[x]: minimum cost of using x elements` and iterate through elements, minimizing `best[x]` when possible

#### Biggest set of non-intersecting intervals : Cost of a set: r_endpoint
We want to build the biggest set of intervals that dont intersect with each other. The minimal cost of a set of size `i` here (`best[i]`) is not a cost per se, but the greatest `r_endpoint` in the best case of a set of size `i`. Such best case has `r_endpoint` minimal.
  
By keeping the best case, we can try to match an interval `[l;r]` to each `i` in `best[]` and try to update (minimize) `best` in some entries. Since it is the best case, if it does not fit, it wouldn't fit in any other case.
  
Check: https://codeforces.com/gym/101519/problem/I  

### `dp[i+j]:` convolution as transition
A lot of problems deal with something like:
```
C[n] = F(G(A[0], B[n]), G(A[1], B[n - 1]), ...,  G(A[i], B[j = n - i])..., G(A[n], B[0]))
It can be that A=B
```
This is a convolution operation and is quite common when `dp[i]`: stuff about set of size `i`. 
The transition using `A` and `B` means building a new state by merging all sizes combinations between `A` and `B`.
  
Computing this transition for each new size `i` in `C` requires `O(min(|B|, i))` operations:
for each `0 <= j < i`, take `j` elements from `A` and `i-j` from `B`.  
Doing this for every position is thus `O(|C|*|B|)`.
  
If `F` is a summation and `G` is multiplication, this is polynomial multiplication, and can be done in `O((|A|+|B|)log(|A|+|B|))` using FFT.
  
### Inplace relaxation vs. Using new array
Let's say we have an DP array with current values and we will apply a transition in it.
There is a difference between and:
- `f[i] = min(f[i], transition(f[j]))`
- Creating a new array `g` with INF values and applying `g[i] = min(g[i], transition(f[j]))`.

The same right-min-side value is computed in both.
However, in the first, we are able to ignore it and maintain the previous value of `f`. 
But in the second, we are enforcing that only values from this new transition can go into `g`.
  
For instance, "choosing which elements to take" would use the first, since we can **maintain the best answer by ignoring**, but "choosing the best way to take" would use the second, since we **need to take**, but in the optimal manner.

### Game: Random vs. Greedy strategy / Black vs. white balls
Two players take elements from an array; one follows a greedy strategy and other a random. Use dynamic programming for computing `dp[i][j]: probability of j-th element be taken by first player given that i elements are laid`

Check: https://codeforces.com/problemset/gymProblem/102916/D

### How many ways to choose at least one element for each pair of two consecutive elements
`f(n) = f(n - 1) + f(n - 2)`  
Insert the `n`-th element by either skipping `n-1` or not.

### Choosing elements in a circular array
Let's say `f(n)` is defined as `g(n)` but on a circular array and `g(n)` builds on choosing elements or not.  
Solve `g(n)` while keeping an extra state, a flag, indicating whether the first element was taken or not. Now, each state `g[n]` will have two versions (`g[n][0]` and `g[n][1]`) indicating whether the first element was already taken. Use this to solve `f(n)` by solving cases.

### Number of sequences with restrictions on consecutive elements
Define `f(n):` number of sequences with `n` elements with restrictions on adjacent elements.
Let's say we have:
- a restriction-unaware way of transitioning from `f(n-1)`, creating **all** new sequences (`g`)
- a way of counting **all** bad sequences built from `f(n-2)` (`h`)
  
Thus, `f(n) = g(f(n-1)) - h(f(n-2))`.  

For instance, if we are computing the number of paths of size `k` that don't use the same edge twice in a row:
- `f(n)[i]`: number paths of size n ending in i
- `g(x) = Adj_matrix * x`: creating **all** paths, some might fail restrictions
- `h(x) = Diag - Id`: creating 2-sized paths that use that goes forth and back at the same edge

### DPs w/ different query/updt timestamps
A state can have one or more transitions to be processed in a line sweep. If it has more than one, each new transtion may (or not) update the current value of the state. This yields a successive approaximation approach.

If a transition has a time for querying and another for updating, one needs to keep these latent updates and only publish them in the appropriate moment. That is, if a transition `x` has `query_time_x=10` and `update_time_x=15` and another transition `y` has `query_time_y=11` and `update_time_y=13`, transition `y` must not access updates from transition `x`.  
  
One way of solving this is keeping in a priority queue sorted by time the transitions to be published. 
Once we reach a `query_time` that is able to access the top transition from this pq, we may publish it.  
  
Also, the usual line-sweep approach where we add at `v[t]` all events that happen in time `t`. There will be 2 event types: update and query.
  
Check: https://codeforces.com/gym/101615/problem/H  
Check: https://codeforces.com/gym/100819/problem/S

### Chance of getting to accepted state using optimal strategy, maximizing probability on mid states (greedy)
I find these problems kinda tricky because the base state of the recursion may be a state with a built structure (the accepted state).

- Base case: accepted states
- Transitions: for each possible choice in the current state, choose the one that maximizes the probability of the current state
  
Check: https://codeforces.com/contest/678/problem/E  
Check: https://codeforces.com/gym/100625/problem/B  

### Maximum partition size of a submask into good masks : Maximum chain of good masks
Suppose that there is a predicate over masks indicanting whether they are good.
The mask with all elements is guaranteed to be good and the union of two good sets is also good.
  
You want to compute the maximum partition size of all elements: maximum number of masks without intersection and with union equal to all elements.
Note that this task e equivalent to computing the maximum chain size of good masks if one is submask of other.
  
A naive 3^N algorithm is possible but a N2^N is also feasible if we look at the chain idea:
- think of building the masks with all elements in a bottom-up fashion
- for each mask, it can be reached be a `O(N)` other masks if we deactivate 1 bit from it (edges)
- this is like a graph problem with multiple sources and one target and you want to maximize the number of good vertices we go through
- `dp[mask]:` maximum number of good nodes you passed until reaching `mask`
  
Check: https://codeforces.com/gym/101666/problem/G
  
## Optimization

### Avoid doing transitions on Big Child in tree
Let's say a transition costs `O(f(sz(T)))` but initialization of `DP` can process ONE transition in `O(sz(T)))`.
  
If `f(x) = n * x`, for instance, it is efficient to, instead of processing the big child, 
initialize the `DP` for a node with value from the big child over the cost of `O(sz(T)))`.
  
When `f(x) = n * x`, this leads to an optimization from `O(n^3)` to `O(n^2)`.
  
Check: https://codeforces.com/contest/815/problem/C    
Check: https://codeforces.com/gym/101964/problem/D

### Transition looks at an interval (range query : pull dp) / Element is looked by range (range update : push dp)
Approach solving the transitions using a RMQ/segment query structure.  
  
For instance, `f(i) = true, iff for any i in [l;r], f(i + 1) is true`, one can solve `f(i)` by range querying `[l+1;r+1]`.
  
Check: https://codeforces.com/contest/985/problem/E

### Linear recurrences
Can be expressed in term of matrixes. Matrix exponentiation is associative, what enables us to solve a linear DP using:
- Segtree (check segtree page), BIT
- Matrix exponentation
A polynomial approach is also feasible:
- Divide and conquer on FFT
- Exponentiation by squaring (if the a (transition) polynomial is recurrent)

### Matrix and tensor exponentiation
Let's say we want to compute the number of paths of size `k` on a graph of size `N`. This can be solved by exponentiating `Adj_matrix`.  
Our DP state will need to keep the number of paths for each vertex :`F(k)(i)` is the number of paths of size `k` ending at `i`. Our transition  is `F(k) = F(k - 1) * Adj_matrix` which is a simplification of `F(k)(i) = sum(F(k-1)(j)*to(j)(i))`.  
  
Note that our transition has only one term (`F(k - 1) * Adj_matrix`) which is already a simplification of `sum(F(k-1)(j)*to(j)(i))` for each `i`. But what if there is now another term?  
  
Let's say now that we want paths of size `k` that don't use the same edge twice in a row. This can modelled as `G(k) = G(k-1) * Adj_matrix - G(k-2) * (Diag - Id)`.  
Just as before, this linear combination can be simplified into a matrix (but now we are handling **tensors** since `Adj_matrix` is already a matrix).  
  
Thus, at first we had scalars multiplying `F(k-1)(j)` and we built a matrix (`Adj_matrix`). Then, we had matrixes multiplying `G(k-1)` and we built tensors. 

Note that tensors from G(x) could be flattened into matrixes. With tensors of size `M` keeping matrixes of size `N`, we multiply `M^3` times with cost `N^3`. Thus, `M^3 * N^3`.  
Flatenning these tensors into matrixes of size `MN`, we would have `(MN)^3` multiplications of cost `1`. Thus, the same complexity.

