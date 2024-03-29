# Flow, cut and bipartite matching

## Nice reductions

### Edge-disjoint path problem
The number of edge disjoint paths from the source to the sink equals to the max flow from the source to sink setting edge capacities to 1.
If a node can only be part of `k` paths, create a `in` and `out` node for each real node and between these version an edge with capacity `k`.

### Minimum node-cover ~= Maximum matching ~= `N -` (Max independent set) 
It is known that `min_node_cover + max_indep_set = N`  
Also, per König's theorem, `min_node_cover = maximum matching`.

### General path cover
Find the minimum number of paths in a graph s.t. each node belongs to **at least** one path.  
Solve using maximum bipartite matching. For each node, create to versions `in` and `out`. 
If `x->y \in E`, create an edge in the bipartite matching `out(x)->in(y)`. 
Connect the source to `out` vertices and the sink to `in` vertices.

The maximum matching equals to the minimum path cover (if edge `out(x)->in(y)` is active, it means that the edge `x->y` belongs to a path). 
The number of paths is `n - sz(max_matching)` (since each used edge unites 2 paths).

#### Node-disjoint path cover
Find the minimum number of paths in a graph s.t. each node belongs to **exactly** one path.  
..same as general..  
If `x` reaches `y` (run the transitive closure), create an edge in the bipartite matching `out(x)->in(y)`.  

The maximum matching *~equals* to the minimum path cover node-disjoint (if edge `out(x)->in(y)` is active, it means that there is a path from `x` to `y`). 
The number of paths is `n - sz(max_matching)` (since each used edge unites 2 paths).

Check: https://codeforces.com/gym/100820/problem/A  
Check: https://vjudge.net/contest/478250#problem/I  

### Dilworth's theorem
**Anti-chain of a graph:** Set of nodes s.t. there is no path between them (if seeing graph as an order, set of elements that are not comparable).  
**Chain:** Set of nodes s.t. there is a path between every pair of nodes (if order, every pair is comparable)
**Minimal chain decomposition:** Decompose graph (or order) in edge-disjoint chains, minimizing the number of chains.

The **largest anti-chain** (numer of nodes) has the same size as the **minimal chain decomposition** (number of nodes).
  
The **minimal chain decomposition** is equivalent to the **general path cover**.


## Min Cut

### Cut red/blue starting from unfeasible

Can see cut as a "choice" problem-solver where you have to choose which edges disconnect.  
That is, starting from a full-profit but unfeasible configuration, find choices with minimal cost to be applied in order to maximize `profit - cost`.
  
Paths from the src to the sink need to comprise invalid characteristics to be removed. The min cut will turn the graph feasible with minimum possible cost of removal. Compute this total gain and then `ans: tot - mincut`.

#### Given `N` elements, color each one, gaining either `A[i]` or `B[i]`, and `C[i][j]` if colour `i` and `j` the same
Given are `N` elements, color each one either blue or red. 
If it becomes blue, you will gain `A[i]`. Else, `B[i]`. If both `i` and `j` end up with the same color, you gain `C[i][j]`.
  
Create cut graph with `src` (blue), `snk` (red) and `N` nodes. 
Add the following edges:
```
src->i (cap A[i])
i->snk (cap B[i])
i->j and j->i (cap C[i][j])
```
  
Path: `src -> i -> snk` : a node is both blue and red  
Path: `src -> i -> ... -> j -> snk` : nodes `i, ..., j` are both blue and red  
  
Compute the total but incorrect gain: `sum A + sum B + sum C(i>j)*`.
  
`*`: Why only `i>j`? Note that there is not the case in which we cut both `i->j` and `j->i`.
Suppose that there is. It must be that `i` is blue and `j` red (or vice versa). Indeed, `i->j` needs to be cut. 
But cutting `j->i` is useless and invalidates `min` cut. 

Check: https://codeforces.com/gym/101484/problem/H

#### Given `N` elements, if color, color red and/or blue, losing `A[i]` and/or `B[i]`; `C[i][j]` is gained if `i` is blue or `j` red
Given are `N` elements, each can be coloured blue, red, blue and red, or not colored. Coloring `i` blue costs `A[i]`; coloring red costs `B[i]`.
`C[i][j]` is gained if `i` is blue or `j` red.
  
Crete cut graph with `src` (not blue), `snk` (not red) and `N*2` nodes. Each node has a `in` (in edge) and `out` (out edge) version.
Add the following edges:
```
src->i (cap A[i])
i->snk (cap B[i])
in(i)->out(j) (cap C[i][j])
```
Path: `src -> in(i) -> out(j) -> snk` : we are not paiting neither `i` nor `j` but gain `C[i][j]`  
  
Compute the total but incorrect gain: `sum C[][]` and then `ans: tot - mincut`
  
Check: https://codeforces.com/gym/101484/problem/H

### Max Cut

Note that maximizing `x` is equivalent to minimizing `C - x`, `C > x`. 
In contexts in which we know exactly how many variables are in the sum being maximized, we can solve it by:
```
MAX SUM_i_1_N(x_i) = N*C - MIN SUM_i_1_N(C - x)
```
That is, computing the min cost where choices are expressed as `C - x`.

#### Bootfall
![Just Bootfall. Thanks kobus!](assets/bootfall.png)

Suppose we need to choose, for each `A,B,C,...` 1 position among `N`.
The same position can be choosen by multiple elements.
Cut can be applied by creating a path for each `A,B,C,...` to be cutted. 
If there is a gain for each position, the MaxCut is desired here.
  
The original problem adds a cost that can easily be added to the graph formulation: **cost of `C_ab` for the distance** between `i` and `j`. Add `N` edges for each pair of nodes `A_i` and `B_i` with capacity `C_ab`.
In a cut where `A` is at `i` and `B` at `j`, `abs(i-j)` edges will need to be cut.
  
Check: https://codeforces.com/gym/103388/problem/J

## Bipartite matching

### Merging nodes
Suppose a graph with sides A and B for bipartite matching and that the size of A is really small (`<15?`). Nodes from B may be merged if they connect to the same nodes from A. The number of condensed nodes will be at most `2^sz(A)`, what might be smaller than `B`. 

### Hall's theorem on contiguous intervals
Notation:
- `f(S)` is the set of adjacent nodes of `S`
- An `X`-perfect matching (`X` saturation) is a matching which covers every vertex in `X` with an edge
- Hall's: There is a`X`-perfect matching iff for every subset `W` of `X`, `|W| <= |f(W)|`.

We have a bipartite (`L` and `R` sets) matching problem. 
In order to find a `L`-perfect matching, Hall's condition is thus sufficient and necessary. 

TODO

Check: https://szkopul.edu.pl/problemset/problem/EwpbJWZPly_zZ5i4ytg_8fDE/site/?key=statement  

### Saturating `A` when `A` has `deg(x) >= k` and `B` has `deg(x) <= k`
If we have a bipartite graph `(A,B)` s.t. 
- every `a` in `A` has **at least `k`** edges to `B` and
- every `b` in `B` has **at most `k`** edges to `A`

Then there is `A`-perfect matching  (`A` saturates) if `k >= 1`.

##### Proof (by contradiction)
Suppose that there is a subset that violates Hall.
That is, there is a subset `X` of `A` s.t. `|X| > |f(X)|`.
Define `S = sum_X(deg(x))` and `T = sum_f(X)(deg(x))`.
We have that
- `S >= k|X|`
  - Since every element in `A` has at least `k` edges
- `T <= k|f(X)|`
  - Since every element in `B` has at most `k` edges
- `S <= T`
  - Since
    - every edge of the matching between `X` and `f(X)` belongs to both `X` and `f(X)`
    - every edge from `X` belongs to the matching
    - there may be a edge in `f(X)` not going to `X`
  
Thus, we have that `k|X| <= S <= T <= k|f(X)|`
  
##### (Particular case) `A` has `deg(x) \in 0,1,2` and `B` has `deg(x) <= 2`
We want to know if it is possible to saturate `A`. Note that
- If there is a node `x` s.t. `deg(x) = 0`, it is impossible to saturate `A`
- If there is a node `x` s.t. `deg(x) = 1`, be greedy remove `x` from `A` and `f(x)` and it other edge from `B`

In the end, either there the matching is impossible, or every node `a` from `A` has `deg(a)>=2`.


## Greedys

### Complete bipartite matching where edge are intervals `[TODO]`
- Lex smallest?
  - Yes: https://atcoder.jp/contests/arc144/submissions/33347474
  - No: https://codeforces.com/contest/1701/submission/166136085
- Numer of intervals per element:
  - 1:  https://codeforces.com/contest/1701/submission/166136085
  - 2: https://atcoder.jp/contests/arc144/submissions/33347474

### Bipartite MaxCMF: edges are suffixes : cost at right side of bipartite
Let's say we have a bipartite graph `(A,B), |A|=|B|=N` and `A_i` can income `in_i` and `B_i` can outcome `out_i` with cost `c_i`.
Edges are `A_i` can send to `B_j`, `j>=i`.  
  
Iterate from `i:0...N` and keep a dict `f[x]`: number of elements w/ cost `x`.  
Add elements from `A_i` to `f`: `f[0] += in_i`.  Then, check which elements `B_i` can take care of: take all possible elements (`num<=out_i`) from `f` w/ `cost < c_i` and assign them to `B_i`, prefer to take elements w/ lower cost.  
Each iteration can remove at most `ON` elements and adds `1` element to `f`. This amortizes to `O(N)` (ignoring the dict cost).  
  
Check: https://codeforces.com/gym/100506/problem/J  
  
Probably can be extended to `|A| != |B|` if a complete order (line sweep) exists.
