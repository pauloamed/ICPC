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

**Note:** dividing by `K` or successive `phi()`, `C=log`
  
Check: https://atcoder.jp/contests/abc256/tasks/abc256_h
