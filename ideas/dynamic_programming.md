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

### Computing number of permutations when adding `k` of `i`-th element
Let's say we have `n` elements. There are two ways to do it:
- **1:** Choose `k` of the `n + k` elements to put the `i` elements
- **2:** Multiply the current state by `inv_fat(k)` and, when computing the final answer, multiply by `n!`

These are equivalent:
- **1:** you will have `C(k0, k0) * C(k0 + k1, k1) * C(k0 + k1 + k2, k2) * ... = C(k0+k1+k2+k3+...,k0 k1 k2 k3 ...)`
- **2:** yuo will have `inv_fat(k0) * inv_fat(k1) * inv_fat(k2) * ... * fat(k0+k1+k2+k3+...) = C(k0+k1+k2+k3+...,k0 k1 k2 k3 ...)`

### Subset of `N` elements w/ maximal sum `<= W`
First, sort elements by decrasing value. Now, a subset that respect such constraint can be bijected to **any subsequence followed by a contiguous subarray** (also called suffix).  
This modelling can be seen as trivial, but it makes sense for this restricted-sum problem since, in a solution, if fixing that what follows is strictly a contiguos subarray, there are at most `N` greedly-computable subarrays that can be used.  
  
For instance, `[5,4,3,2,1], W = 10`. If we take `(5)`, the contiguos subarrays that can be matched w/ it are `[3,2]` and `[2,1]`.
These can also be seen as: `[5,_,3,2,_]` and `[5,_,_,2,1]`.  
  
**Obs1:** it makes sense to enforce a gap before the suffix `s`. If there is not one, the actual suffix would be the merge between the last active subarray in the subsequence and `s`.  
  
**Obs2:** when repeated elements occur, we need to take caution to nut hurt our bijection:  
If the input is `[3,2,2,2,1]`, the following 3 represent the same subset:  
- `[3,2,2,_,1]`: subsequence is `(3,2,2)`, `[1]` is suffix  
- `[3,2,_,2,1]`: subsequence is `(3,2)`, `[2,1]` is suffix    
- `[3,_,2,2,1]`: subsequence is `(3)`, `[2,2,1]` is suffix  
Thus, we must fix how we are taking the elements when there is more than one to be taken.  
It makes sense to remove them from left to right (arbitrary). Thus, the correct representation would be:
- `[3,_,2,2,1]`
  
**Obs3:** the subsequence can be empty: `[3,2,2,2,1] W=5`, one of the solutions is `[_,_,2,2,1]`  
  
Now, we build a dp `f(i, w):` given that we considered until the `i`-th smallest value (one value can have multiple elements) and that the current sum is `w`, number of solutions (subsequences respecting our bijection).  
The functional equation is `f(i, w) += f(i - 1, w - (j * Vi))`, if we are adding `j` elements of the `i-th` smallest value to a solution.  
  
Consider `Delta f(i, w)` (sum of updates). This is the number of subsequences created after considering the `i`-th value. These are different from the ones already stored in `f()` and can thus be used to compute new solutions by matching with the contiguos intervals.  
That is, having `D` (delta) subsets and `S` valid contiguos intervals, we build `D*S` new solutions.  
  
Now there remains the question: how many contiguos intervals can be considered from `(i, w)`?  
These can be found before and kept in stack. Find them using a simple bruteforce. Now, while we advance `i`, remove those intervals that cross `i` or don't present a gap, keeping only the valid ones.
  
#### Permutations of `N` elements w/ maximal sum `<= W`
Similar to the subset problem, but now we need to keep the permutation counts (and repeated elements discounts) in `f`.  
A new `dp` state will be needed since the number of inserted elements is necessary to compute the answer (both in `f` and for the suffixes).
Also, if we add `j` elements from value `i`, discount the current permutation w/ `1/(j!)` 
    
Check: https://codeforces.com/group/XrhoJtxCjm/contest/422715/submission/191737107

### When `N` is not a dimension
In some DPs, even if the problem relates to a structure of size `N`, it may be that `N` is not a dimension, but appears only in the transitions.

#### Ways of building sequence of size `N` w/ `xor 0` and `sum M`
`dp[i][k]:` sequences using until `i`-th bit with sum `k` and xor `0`  
`N` will appear in the transition when choosing which of the `N` numbers will recieve `2*l` active bits (`C(N,2l)`).
  
Check: https://atcoder.jp/contests/arc116/tasks/arc116_d

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

### Try to compress stuff with similar characteristic to fit the state description
Let's say we can use edges `(x,y)` to join different but all edges have the same cost. 
  
Can we compress the info "edge between `x` and `y`" to only the number of edges?  
How does using an edge affects the function in question to be computed? Does the number of used edges is enough to computed `F` correctly?

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

### `f(x, a) = min_b_gcd(a,b)!=1 f(y, b)` in `O(VlogV)`
We are transitioning from `x` to `y`. There is a cost function `f_x(v)` to be minimized (`f(x,v):` min cost of `x` if assumes value `v`).
  
Functional equation is: `f(x, a) = min_b_gcd(a,b)!=1 f(y, b)` (minimum value for `(x,v)` comes from `(y,b)` where `b` is **not coprime** with `a`).
  
Optimize this by defining:
- `g(x,v):` min cost of `x` if gcd used at transition is `v`
- `h(x,v):` min cost that `x` "offers" to `y` (`y` is LHS and `x` RHS) if value of `y` is `v`

Functional equation can then be rewriten as: `f(x, a) = h(y, a)`
  
Compute `g` and `h` using the sieve:
- `g_x(a) = min_b_a|b f_x(b)` (iterate through multiples of `a`, pull dp)
- `h_x(a) = min_b_b|a g_x(b)` (iterate through multiples of `b` (divisors of `a`), push dp)
  
Check: https://open.kattis.com/problems/gcdharmony
  
### Decomposable transitions costs: `(Ai - Aj) ^ 2` and similars
In some max/min DPs, we are transitioning from `i` to `j` and this is followed by a `cost(Ai, Aj)`.
```
f_i = max_j>i (f_j + cost(A_i, A_j))
```
It may be that `cost(A_i, A_j)` is decomposable into two functions that depend solely on `i` or `j`.  
We are calling these costs functions decomposable. Following are some examples.

#### `cost(A_i, A_j) = A_i + A_j`
Just `f_i = A_i + max_j>i (f_j + A_j)`

#### `cost(A_i, A_j) = (A_i + A_j)^2 = A_i^2 + 2 * A_i * A_j + A_j^2` (Convex hull trick)
By querying `j`, `2 * A_i * A_j + A_j^2` can be seen as evaluating a linear function `g(x) = 2*A_j*x + A_j^2`, where `x = A_i`.
  
Keeping the maximal linear functions for each query value can be done using CHT.

#### `cost(A_i, A_j) = |A_i - A_j|`
It is trickier since `|A_i - A_j|` depends on `A_i<A_j`.
We will decompose this query in two cases: `A_i<A_j` and `A_i>A_j` and index `A_k` values in 2 easy queriable structures.
  
That is, when visiting `A_i`, execute the cases:
```
(C1: A_i < A_j) f_i = -A_i + max_j>i (f_j + A_j)
(C2: A_i > A_j) f_i = A_i + max_j>i (f_j - A_j)
```
Compute `C1` by quering `max` on `A_k > A_i` (a suffix starting after `A_i`); 
similarly, compute `C2` by quering `max` on `A_k < A_i` (a preffix ending before `A_i`).
  
After computing `f_i`, update the `C1`-structure `G` at position `A_i` w/ `max(G_(A_i), f_i + A_i)`;
similarly update the `C2`-structure `H` at position `A_i` w/ `max(H_(A_i), f_i - A_i)`;

#### `cost(A_i, A_j) = floor((j - i) / M)`
Note that `floor((j-i)/M) = `
```
(C1: j < i (mod M)) floor(j/M) - floor(i/M) - 1
(C2: j >= i (mod M)) floor(j/M) - floor(i/M)
```
Then,
```
(C1) f_i = -floor(i/M) - 1 + max_j>i (f_j + floor(j/M))
(C2) f_i = -floor(i/M) + max_j>i (f_j + floor(j/M))
```
Addressing `C1` and `C2` can be done as in `|A_i - A_j|`.
Index 2 queriable structures using `k % M` and, when at `i`, 
perform a query on `C1`-structure `G` on the prefix smaller then `i`
and a quer on `C2`-structure `H` on the suffix starting at `i`.
  
Check: http://qoj.ac/problem/4590  

### Avoid doing transitions on Big Child in tree
Let's say a transition costs `O(f(sz(T)))` but initialization of `DP` can process ONE transition in `O(sz(T)))`.
  
If `f(x) = n * x`, for instance, it is efficient to, instead of processing the big child, 
initialize the `DP` for a node with value from the big child over the cost of `O(sz(T)))`.
  
When `f(x) = n * x`, this leads to an optimization from `O(n^3)` to `O(n^2)`.
  
Check: https://codeforces.com/contest/815/problem/C     
Check: https://codeforces.com/gym/101964/problem/D  
Check: https://atcoder.jp/contests/arc121/tasks/arc121_e  

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

