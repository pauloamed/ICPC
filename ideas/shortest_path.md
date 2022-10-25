# Shortest Path

#### Shortest Path is Dynamic Programming and Dijkstra is an optimization of Bellman-Ford
Firstly, we are dealing with optimal structures: the shortest path between two vertices is composed by other shortest paths.  
  
In DP problems, we will first have a **functional equation** (`f(x) = ...f(y)...`) that states the optimal modelling. Such is recursive, thus, the need of DP. Then, we need to solve this equation. We can use the **direct method** or a **successive approximation method**.
- **Direct**: Vanilla DP. For computing the left-hand side (`f(x)`), values in the right-hand side (`...f(y)...`) must have already been computed. 
Thus, the the modelling needs to be acyclic (**DAG**). *Note: we can actually solve self-loops in some cases by algebraic manipulation.* **Example**: Floyd-Warshall.
- **Successive approximation:** Start with an upper bound and keep improving until a fixed point is reached (convergence). The fixed point is the solution. Cycles are allowed here. You will need to keep a list of new approximations to visit.
 - **Pull:** At `x`, compute an approximation for `f(x)` using updated values of the RHS (`f(y)`, `x` depend on `y`). If this is the new best approximation, add nodes that depend on `x` to the list.
 - **Push/Relaxing/Label correction:** At `y`, given an approximation of `f(y)`, compute approximations of `f(x)`, `x` depend on `y`. If such are new best approximations, add them to the list. **Example**: Dijkstra, Bellman-Ford.

If the **edges are non-negative**, one can use a greedy approach on the push method in order to optimize it (**Dijkstra**). We know that, since edges are non-negative, the minimum value from the list won't ever be enhanced, being thus the optimal value. Therefore, for each iteration, we have solved one entry of our functional equation.
  
Note that an approximation of node `x` in **Dijkstra** is actually a path to node `x`. We are mainly generating all minimum paths to each node and taking the shortest one. It is thus guaranteed the shortest path for each node. Also, this doesn't become exponential since we stop generating paths from a node once its shortest path has been found.
  
Note that Dijkstra can also be used in DAGs. While Dijkstra will solve states in incresing order of `f(.)`, the direct method will solve them in topological order.  
  
Check: https://codeforces.com/gym/101201/problem/B

#### DP with states
Since it is DP, you can create new states for each node and solve these as the shortest path problem.

Check: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1297  
Check: https://www.hackerrank.com/contests/w20/challenges/synchronous-shopping  
Check: https://community.topcoder.com/stat?c=problem_statement&pm=12468  
Check: https://community.topcoder.com/stat?c=problem_statement&pm=13596

Some may need you to compress the graph into only useful nodes.  
Check: https://codeforces.com/gym/101512/problem/H  

#### Some problems don't look like shortest path
Because it isn't obivious:  
Check: https://szkopul.edu.pl/problemset/problem/ROXsaseQWYR11jbNvCgM19Er/site/?key=statement   
(here the "minimum distance" is actually the minimum number reachabel for a mod `k`)
  
Or because the functional equation is somehow different:  
Check: https://codeforces.com/gym/101620/problem/G  

#### Point w/ (maximum) minimum distance to a set of points
If we run a multisource BFS from such set, every visited position will hold the minimum distance to this set.  
Visit every point in the universe and take the one w/ highest distance.

#### BFS with priority nodes
Instead of visiting any reachable node for each iteration, 
the problem wants your BFS to visit first all reachable nodes with max priority,
than those with lower priority (nodes with high priority might appear again after relaxing one w/ lower priority) and so on.  
For this, use a priority queue instead of a queue.  
Thus, you will only decrease the priority of the next visited node if those (reachable) w/ high priority run out.

#### BFS on too much edges, delete node after visiting
You need to run a BFS on a graph with too much edges.  
What you can do is, instead of storing all edges, keep a structure that allows you to query the adjacent vertices `Y`s from `X`.  
Once you visit `X`, just add all `Y`s into the queue and delete them from such structure.
You can do this since they only need to be added once into the queue given that this will be their shortest distance.

Check: https://codeforces.com/contest/1662/problem/F  
Check: https://codeforces.com/contest/59/problem/E

#### Minimum coins problem (allowing negative edges)
Check: https://codeforces.com/gym/101512/problem/B

#### (Irreplaceable) Edges in shortest path from `s` to `t`
First, run a Dijkstra from `s` and other from `t`, which will compute, for each node `x`, its minimum distance to `s` (`d_s[x]`) and to `t` (`d_t[x]`).  
If an edge `(u,v)` with weight `w` is in the shortest path from `s` to `t`, then, it must be that `d_s[u] + w + d_t[v] = d_s[t] = d_t[s]`.  
Every edge `(u,v)` in the shortest path is responsible for an interval `[d_s[u], d_s[v]]` in the shortest path. If an edge is irreplaceable, it must be the only responsible for such interval i.e. doesn't intersect w/ other edge intervals.
  
Check: https://codeforces.com/contest/567/problem/E  

#### `K`-th shortest path
Use priority queue instead of set.  
For finding the `k-th` shortest path to a node `sink` we actually need to find the `1...k`-th shortest paths for all nodes.  
Note that the `i-th` pop of the PQ in the vertice `x` is the `i-th` shortest path from the source to `x`. Thus, for getting the `k-th` shortest path for a node `x`, we need to allow `k` pops.

Note that we will restrict the number of pops, not the number of insertions in the priority queue.
Concerning optimization (as in vanilla Dijkstra):
- **Lazy delete:** We won't process the `i-th` pop if `i > k` since this won't change any approximation
- **Only add useful approximations/relaxations:** Add an approximation to the PQ only if it is better than the current candidates to top `K`
  - Adding useless approximations won't harm correctness since better approximations will be processed before. 
  - For this, solving "keep top `K` elements from a stream" problem will do. If it is the case of blocked paths, for each unique value, only one shortest path must be kept.

#### Keep the `K + 1` shortests paths because of `K` blocked paths
Some problems need for you to keep for the same node the `K` shortests paths since some of these may be blocked and then you would need to ignore the blocked path and consider the following one.  
If the blockage happens because of a condition (source or time mod `P`), the shortest paths need to be unique concerning such condition i.e. there is no need in keeping `K` different shortest paths if all of them will be blocked. Thus, keep the shortest path for each source or time mod `P`.

Check: https://codeforces.com/gym/102006/problem/E  
Check: https://atcoder.jp/contests/abc245/tasks/abc245_g  
Check: https://www.hackerearth.com/challenges/competitive/september-clash-15/algorithm/dangerous-dungeon/description/  

#### Negative edges - Potential
Graph has negative edges but we want to use Dijkstra.  
  
Reweight the graph so that all weights are non-negative, but all shortest paths are the same. 
Define a function `p` over `V` that provides an offset for `V` s.t. when in a path, entering vertex `x` contributes `+p(x)` to the cost and leaving contributes `-p(x)`. 
We want to define this potential `p` s.t. for every edge `u->v`, `w(u->v) + p(u) - p(v) >= 0` (that is, it is now non-negative).
  
Note that assiging this offset to the vertices maintains the shortest path. 
Take the sortest path on the modified graph `(x1,x2,x3,...,xk)`. 
The cost of this shortest would be
```
(p(x1) + w(x1->x2) - p(x2)) + 
(p(x2) + w(x2->x3) - p(x3)) + 
... + 
(p(xk-1) + w(xk-1->xk) - p(xk)) 
= dist(x1, xk) + p(x1) - p(xk)
```
`dist(x1,xk)` has to be the shortest path in the original graph (subtract `(p(x1) - p(xk))` from the result).
  
A potential is valid iff for every edge `u->v`, `w(u->v) + p(u) - p(v) >= 0`.

Check: https://atcoder.jp/contests/abc237/tasks/abc237_e

#### `A` red nodes pointing to `B` blue nodes but edge weights are fixed for each blue node
Let's say we have this problem. The number of edges would be `A*B` (for each red, create an edge to a blue).  
However, since edge weights `B_i` are fixed for each blue node, we can create a virtual middleware node `V`:  
- All red nodes point to `V` with edge cost `0`  
- `V` points to each blue node with edge cost `B_i`  
  
Check: https://oj.uz/problem/view/APIO15_skyscraper

#### Objective function is a ratio
Let's say each edge has a profit `p` and a cost `c`.  
Given that `E` is the set of edges traversed, the final cost function is `sumP / sumC`, a ratio.
  
You want to find the path of greatest ratio. You can't use the cost function as is since it is tricky. Do binary search instead:
```
Find greatest R s.t.:
sumP / sumC >= R
sumP >= R*sumC
sumP - R*sumC >= 0
Since P and C are indexed by edges,
sum(p - R*c) >= 0
```
Define a new cost for each edge: `p - R*c`. The predicate is true iff there exists a path w/ non-negative cost.
  
If a path is a cycle, try to use Floyd-Warshall for searching any non-negative cycle.
  
Check: https://oj.uz/problem/view/APIO17_merchant  

## SPFA - Fast Bellmanford
Some optimizations can be done by pushing front instead of only back (use a deque).  
Random shuffle edges.

##### mcfx
If it is the `k`-th time you are adding a node to the queue, add it at the front. `k` should be in `[2;sqrt(V)]`. Once `time` reaches `k`, it reset `time=0` and `k` may be recomputed.

##### Small-label first w/ fault tolerance
Before adding the updated node `y` to the end of the queue, check if it is actually better (distance to source is smaller) than the one on the front. But actually compare it using a tolerance:
```
dist(y) < dist(front) (without tolerance)
dist(y) < dist(front) - SQRT (with sum tolerance) [somewhy people use sqrt(V) here]
dist(y) < dist(front) / 2 (with mult tolerance)
```
Check: https://atcoder.jp/contests/abc237/submissions/33906552
	
## Dijkstra Optimizations

#### Dijkstra complexity
Dijkstra complexity can be analyzed using two operations:
- `D:decrease-key`: update `dist[x]` for a node `x`
  - `D` occurs at most `O(m)` times, since each visited edge may update a cost 
- `E:extract-min`: get `x` with min `dist[x]`
  - `E` occurs `O(n)` times, since we are solving one node each iteration
  
Using sets/binary heaps with lazy delete/segtree: `cost(D) = cost(E) = log(n)`. Resulting in `(m+n)*log(n) = mlog(n)`  
Using naive list: `cost(D) = O(1)` and `cost(E)=O(n)`. Resulting in `O(m*1+n*n)=O(n*n)`  

#### If graph is complete `m > n * n / log(n)`
Use disjktra with naive list

#### If edge weights `\in {0, K}` : 0-1 BFS using deque
Push-front `0`-valued edges and push-back `K`-valued edges in the deque. Push-front for quering. This emulates a priority_queue.

#### If edge weights `\in [0;K]` : Dijkstra with buckets `O(N*K+E)` : Dial's algorithm
Suppose that our graph has edge weights at most `K` and that we are running a shortest-path from `src`.  
When visiting a node `v` with distance `d[v]` from `src`, all other nodes `x` in the queue will have `d[x] <= d[v] + K`, since `K` is the max distance.

**1**  
Because of this, we only need to keep and "horizon" of the `K` next layers in such graph.  
While using a circular vector of queues of size `K+1`, we can a BFS in `O(N*K+E)`: for each node, we may need to find the next valid queue in `O(K)`.
  
**2**  
Alternatively, don't keep a circular vector, but a vector with `size = MAXDIST` and perform a line sweep in this vector. Note that `N*K <= MAXDIST`, since we won't visit more than `MAXDIST` positions approach **1**.

**Summary**
This works like a Dijkstra but we use an array of queues for sorting and also we don't need to sort inside the same queue.

#### If edge weights `\in {0, K} U Nat` : Combine deque with priority queue : 
This is actuall a simple optimization on the priority queue.  
Instead of adding updates to the priority queue, having cost `O(logN)`, add updates with edge cost `0` and `K` to a deque (`0-1` BFS).  
We know that, by doing this, it will be correctly sorted. Other edge weights will go into the priority queue.    
  
When querying, take the min between the priority queue and the deque. 
  
Suppose that there are `M1` `0,K` edges and `M2` non-trivial edges.
Then,
- For decrease-key: `O(M1 + M2 * log(N))`
- For get_min: `O(N*log(N))`
- Total: `O(max(N,M2) * log(N))`
  
This helps us generalize to:
- Querying the next min can be done by querying the min of `S` sorted structures
- Keep structures with 2-fixed edge costs into a deque when possible
- Let the heap solve non-fixed edge costs
  
Check: https://oj.uz/problem/view/APIO15_skyscraper

#### If edge weights `\in [A;A*K]` : Dijkstra with real buckets `O(N*K+E)`
Suppose that our graph has edge weights in a **real** range `[1;K)`, Dijkstra is too slow but `K` is small. 
First, for using BFS instead of Dijkstra, we need something like Dial's algorithm. Secondly, we need to know to which bucket assign vertex distance. Note that inside the same bucket, in order to keep Dial's assympotitcs, vertices can't be sorted i.e. their order must not matter.
  
We thus can put all vertices `x` with same `floor(dist[x])` together since every weight is at least `1`.
Also, we can then solve `[A;K*A)` if we index/cluster using `floor(d[x]/A)`.

#### If edge weights `\in S`, and `|S| = K` : `O(N*K+E)`
For each edge value `w`, keep a queue `q_w`.
If using a edge with cost `w` to update a vertex, add that new entry to `q_w`. 
    
`q_w`s will be always sorted inside, so this is querying is like online merging `K` sorted lists.
 
  

