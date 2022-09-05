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

