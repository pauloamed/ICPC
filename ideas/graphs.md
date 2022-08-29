# Graph ideas

### Query: walk 10^9 steps from a node
Binary lifting or cycle detection may be used. This is probably a graph in which every outdegree is `1`.

Binary lifting: Precompute `bf[x][i]`: where will I stop if start from `x` and walk `2^i` edges. 
Cycle detection: find a cycle of length `L` in `O(n)`, use this cycle `K/L` times and walk `L` naively. Since `L` is `O(n)`, the total cost is `O(n)`.

If there are multiple queries, binary lifting might be better. If there are updates, binary lifting might have a drawback since it's idea is to be a precomputed structure.

### Number of spanning trees of a graph in `O(N^3)`
Kirchhoff theorem states that the number of spanning trees of a graph (allows multiple edges) is equal to the determinant of any submatrix of the laplacian matrix of such graph.  
Laplacian matrix, `Lij`:
- if `i=j`: `deg(v)` 
- else: edges between `i` and `j` `* -1`

### Partitioning set of nodes `S` for DP: `g(S) = sum_T[f(T)*g(S-T)]`
For some DP modelling, when computing `f(S)`, `S` set of vertices, we might need to partition `S` into exclusive cases in order to avoid processing the same thing twice (eg. when using non-idempotent ops). 
Such partitioning can be done by choosing an arbitrary vertex `v \in S` and 

Examples:
- Number forests `g(S)` over a set of vertices `S` using auxiliary `f(S)` couting number of trees on `S`.
Note that we can partition the forests on `S` by the trees that contain `v`.
Iterate through all `T` set of nodes spanning a tree, `g(S) = sum_T[f(T)*g(S-T)]`  

- Number connected graphs `g(S)` over a set of vertices `S` using auxiliary `f(S)` couting number of graphs on `S`.
Note that we can partition the graphs on `S` by the connected components that contain `v`.
Iterate through all `T` set of nodes forming a connected graph, `g(S) = sum_T[f(T)*g(S-T)]`

### Sum on DAG not repeating nodes
Like, `1->2, 1->3, 2->4, 2->4` and `4` should only be counted once for 1.
This can only be solved using brute-froce.

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


### Greedy on contiguos intervals `[TODO]`
- Lex smallest?
  - Yes: https://atcoder.jp/contests/arc144/submissions/33347474
  - No: https://codeforces.com/contest/1701/submission/166136085
- Numer of intervals per element:
  - 1:  https://codeforces.com/contest/1701/submission/166136085
  - 2: https://atcoder.jp/contests/arc144/submissions/33347474

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


## 2SAT
Build an implication graph: nodes are propositions (`x`) and their negations (`~x`) and there is a **direct** edge `(p,q)` if `p => q`. Also, if `(p,q)` exists, so does `(~q,~p)` (contraposition). 
  
A path `x...y` in this graph indicates that, if `x` is set to true, `y` also needs also to be true. A valoration will satisfy the clauses iff there won't be `x=true` and `y=false` and there exists a path `x...y`.  
  
**First, we need to check whether `x` and `~x` are in the same SCC**. 
If that is the case, there is a path from `x` to `~x` and from `~x` to `x`, it means that we can't satisfy the clauses:
- if we set `x` to true, since `x => ~x`, `~x` would also be true (absurd)
- if we set `x` to false, `~x` would need to be true, and, since `~x => x`, `x` would also be true (absurd)

Then, build the condensation graph. All variables in the same SCC have the same truth value. 

TODO
  


# Graphs properties

### Functional graphs
Each node has outdegree 1. A connected component contains exactly one cycle (and possibly some chains of nodes leading into the cycle).

### Degrees directed graphs
- If every vertex has outdegree >= 1, the graph has a cycle
- If, for every vertex, indegree = outdegree, the graph is a union of cycles and it has an eulerian circuit

### Condensation graph
Graph resulted after collapsing SCCs into a single node. This graph is acyclic.

