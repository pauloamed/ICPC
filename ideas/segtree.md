# Segtree

### <a name="histogram_weighted_array"></a> Histogram on a weighted array
Let's say we have an array where `a_i` is a weight and we have operations like `add(lu;ru)`: add weights from `a_i`, (`lu <= i <= ru`) to out Segtree.  
What we can do is set for each Segtree node `x` with interval `[l;r]` a variable `val[x]`: sum of `a_i` (`l <= i <= r`) and use this `val[x]` in our operations:  
`add(lu;ru)` will processed as add `val[x]` to `seg[x]` if `x` is inside `[lu;ru]`.

### Area of the union of rectangles
We want the area of the union of rectangles.
We can do this with line sweep + segtree, traversing the X axis (left to right). 
Note that we can decompose every y-aligned edge into several intervals (consecutive endpoints considering all endpoints). 
Our segtree leaves are such intervals. These will have weights just as handling a [histogram on a weighted array](#histogram_weighted_array).  
While traversing the X axis, we want to count how many times each interval occured and use these interval sizes in our area calculation.
Even if a interval is counted multiple times, it only contributes once to our area. 
Every time we process an event in out line sweep (addition or removal of a y-aligned edge i.e. contiguous interval in our segtree), we can query the whole segtree and increment the answer.

### Keeping maximals intervals sizes (powers of 2) with a certain property
Let's say we have predicate `pred` over segtree nodes (intervals) s.t. if it is true for a node `[l:r]`, it is also true for both of its childrens (`[l:m]` and `[m+1:r]`) i.e. `pred(X) => pred(l(X)) AND pred(r(X))`.   
We want to keep which of these nodes are maximals i.e. `pred(X)` but not `pred(parent(X))`.  
  
Note that there can be `O(N)` maximals nodes.
  
For example, each leaf holds a color and `pred(X) = X's interval has only 1 active color`. Depending on how we modify our array, maximals may change. Since there may be `O(N)` of these, probably we will compress this info somehow (eg. count sizes of maximals).

How to keep this info (point update, don't know how to handle range update):
- only change maximals in the `update` function 
- divide top-down from bottom-up
  - top-down: if `X` is maximal, unset it as maximal and set `l(X)` and `r(X)` as maximals
  - bottom-up: if `pred(X)`, it must be that `pred(l(X))` and `pred(r(X))` and that `l(X)` and `r(X)` are maximals. Unset them as maximals and set `X` as maximal. 

### "Best" interval after some updates for associative function
A node `X` with interval `[l;r]` can keep 3 infos: the best interval, preffix and suffix totally inside it.
When merging `X` to `Y` (`X` left and `Y` right) into `Z`:  
- `Z.best = max(X.best, Y.best, f(X.suffix + Y.prefix))`
- `Z.prefix = X.prefix` or `X.prefix + Y.prefix` when `X.prefix = [lx;rx]` 
- `Z.suffix = Y.sufix` or `X.sufix + Y.sufix` when `Y.sufix = [ly;ry]`  
Check: https://codeforces.com/edu/course/2/lesson/5/3/practice/contest/280799/problem/A 

### <a name="bin_search_combined_histogram"></a> Binary search/`k`-th value in a combined histogram segtrees

Let's say we have a set `S` of histogram segtrees that count on the same set of elements `E`.  

By running a binary search on the sum of `S` we can find the `k`-th element on this set `S`. 
That is, when solving `[L;R]` looking at `p_1, p_2, ..., p_|S|` nodes for each segtree (base case, root for each segtree):
- compute the sum `s` of `S` for `[L;m]`
- if `s <= k`, search for `k` in `[L;m]`
  - "walk" each `p_i` to it's left child
- else, search for `k - s` in `[m+1;R]`
  - "walk" each `p_i` to it's right child

Note that, if a segtree `B` is a *subhistogram* (`B_i <= A_i` for all `i`) of another segtree `A`, we can also search for the `k`-th element in `A-B` by computing `seg_A[L...m] - seg_B[L...m]`. That is, the `k`-th element from `A` while excluding those from `B`.

## Linear recurrences on consecutive positions on Segtrees

Linear recurrences for DP when expressed over adjacent positions (`a_i = f(a_(i-1)`) can be used in segtrees since matrixes can encode such transitions. Since matrix multiplication (or other operation in question) is associative, segtrees can be used.
  
Note that `seg[i]` is a node encoding a transition. Querying `seg[l:r]` means computing the transition between `l` and `r`. Once computed, you will need to apply that to the base case.  

Check: https://atcoder.jp/contests/abc246/tasks/abc246_h  
Check: https://codeforces.com/gym/102644/problem/H  

### String editting and pattern matching `[Automaton]`
Given a pattern `P` and a modifiable string `S`, count how many patterns are inside `S` or modify `S`. This can be done using KMP automaton and segtree. For each `[l;r]` node for `S`, keep `to[x]` (to which automaton node the substr `S[l;r]` leads if you start traversing it from `x`) and `accs[x]` (how many times we visit the accepted node from the automaton if we start traversing `S[l;r]` from `x`).

Merge two nodes using function composition: `(a+b).to[x] = b.to[a.to[x]]` and `(a+b).accs[x] = b.accs[a.to[x]] + a.accs[x]`  
Check: https://codeforces.com/gym/101908/problem/H

### Cost (chars to erase) in order to get to the accepted state `[Automaton]` 
We want to know the minimal (cost) chars to erase in order to accept some subseqs and avoid some others. 
An automata w/ costs on edges can be modelled and for each state, there will be 3 types of edges:
- Edges for advancing: reading its char means we won't delete it and we will advance to the next automata state
- Edges for staying: reading its char means we will delete it and we will force the automata to stay in this state
- Useless edges: reading its char doesn't interfer in the current state  
Note that the edges for advancing and staying have the same charset. Edges for staying have cost 1 (since we need to delete 1 char) while other edges have 0 cost.

A segtree node `(l;r)` will keep the cost of minimal path between the automata states. Thus, we only need to check the cost between the start and accepted state. Nodes can be combined using the Floyd-Warshall algorithm. `(l;l)` nodes deal with the `s[l]` char; edges that don't have `s[l]` in their charset are setted to infinite cost.

Check: https://codeforces.com/problemset/problem/750/E

## Persistent Segtree

### Each `a[i]` has a range, find for `[L;R]` `a[i]` s.t. `a[i].l <= L, R <= a[i].r`, intervals are inside `[1;N]`

There will be `N` versions of `seg`, one for each position in `[1;N]`, `seg_i` holds:
- all `a[j]` s.t. `a[j].l <= i`. `a[j]` is added at position `j` as a pair `(a[j].r, j)` (right limit and its id)

Note that `seg` at version `i` acts as a prefix, keeping all items w/ endpoint leq `i`. Thus, we will build this seg as a prefix:
- group elements by their `.l`
- iterate `i` from `1` to `N`, creating a new version of `seg` at `i` and adding in this position elements w/ `.l = i`.

When querying for interval `[L;R]`, query on `seg_L` for the max element comparing the `.r` added. If the `.r` found is `>= R`, the range of the respective element contains `[L;R]`.

### `k`-th element on a path in a tree
Problem: find the `k`-th smallest node in a path from `u` to `v`. There are just queries, no updates.  
  
Construct `N` persistent segtrees, one for each tree node `v`, maintaining the histogram of values from the root to `v`.  
Searching for the `k`-th value on a tree path can be solved using [binary search on combined histogram](#bin_search_combined_histogram) 

By combining `+hist(u)`, `+hist(v)`, `-hist(lca(u,v))`, `-hist(par(lca(u,v))))`, we have the exact count of the values in the path from `u` to `v`. Run the binary search in this combined histogram (using the prefix persistent segtrees).


## HLD
### Non-commutative operations on arrays and trees
When dealing w/ non-commutative operations (eg. reading a string), a forward query `[l;r]` might differ from a backward `[r;l]` query.  
For handling queries in both ways (forward and backward), your node must keep 2 internal states, one for each way.  
When combining nodes, stablish that `(a+b).forward = merge(a.forward, b.forward)` and `(a+b).backward = merge(b.backward, a.backward)`.  
When querying, specify if it is a forward or a backward query. If its a forward query, on a `[l;r]` node, merge `[l;mid]`'s answer to `[mid;r]`'s answer and use only forward values. Otherwise, use only backward values and merge `[mid;r]`'s answer to `[l;mid]`'s answer.

On trees, going down and up are different directions, so this technique needs also to be used. Query and update orders need also to be respected at the HLD structure. 
Check: https://codeforces.com/gym/101908/problem/H
