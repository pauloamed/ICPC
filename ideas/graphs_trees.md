# Graphs and trees

### Query: walk 10^9 steps from a node
Binary lifting or cycle detection may be used. This is probably a graph in which every outdegree is `1`.

Binary lifting: Precompute `bf[x][i]`: where will I stop if start from `x` and walk `2^i` edges. 
Cycle detection: find a cycle of length `L` in `O(n)`, use this cycle `K/L` times and walk `L` naively. Since `L` is `O(n)`, the total cost is `O(n)`.

If there are multiple queries, binary lifting might be better. If there are updates, binary lifting might have a drawback since it's idea is to be a precomputed structure.

### Trees: fixing the minimum distance of 2 nodes
It is given a tree, you choose a pair of nodes and set their distance `D` as the minimum distance.  
The other pairs which distance is `<= D` must follow:
```
D=dist(a,e)
X, X': nodes w/ distance at most 1 to b
Y, Y': nodes w/ distance at most 2 to c
Z, Z': nodes w/ distance at most 1 to d

               X  Y  Z
               |  |  |            
Subtree(a)--a--b--c--d--e--Subtree(e)
               |  |  |
               X' Y' Z'
               
(u,v), s.t. dist(u,v) <= D: u,v \in {a,b,c,d,e,X,Y,Z,X',Y',Z'}
```

### Trees: iterativelly: find deepest node `X` from root -> destroy nodes in path from `X` to root -> solve created trees
Run an euler tour in your tree and also compute the depths. Label each node to it's order in the euler tour. Keep a segtree for RMQ and sum update using the created indexes.  
  
Note that depths will only decrease in the process. Also, subtrees have their roots fixed. Thus, the original tree structure can be used and the euler tour indexes are fixed.
  
In the current root, query the deepest node. Mark all nodes in the path from the root to it (use `in` and `out` for guiding). For each newly marked node, search for unmarked adjacent nodes. Solve each of these: subtract the current (query the segtree) depth from it in order to simulate it as the root.
  
Check: https://codeforces.com/gym/101512/problem/F

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

Check: https://atcoder.jp/contests/abc253/tasks/abc253_h  
Check: https://atcoder.jp/contests/abc213/tasks/abc213_g  

### Sum on DAG not repeating nodes
Like, `1->2, 1->3, 2->4, 2->4` and `4` should only be counted once for 1.
This can only be solved using brute-froce.

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

### Euler identity to planar graphs
```
v - e + f = 1 + c
f: number of faces (including outside)
v: number of vertices
e: number of edges
c: number of components
```
It is ok to have colinear edges.

