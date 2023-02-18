# Structures

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

### Use offset in structures for values
If modifying values kept in a structure by subtracting/adding `x` at each iteration, instead of updating the stored values, create an offset for both stored values and values to be stored comprising such modifications.
  
Check: https://atcoder.jp/contests/agc024/submissions/33929120


# Wrapper structures

We are **assuming queries are associatives**. If they aren't, just merge each structure if this isn't `O(n)`.  
Also, update may be seen as `remove` followed by `insert`.

```
Q: query cost
I: insertion cost
R: removal cost
U: update cost
N: number of inserted elements/operations
```


### Inserting after building (`log` structures) `[ONLINE]`
**Query: `O(log(N) * Q)`**  
**Insert: `O(log(N) * I)`**  
If you are dealing with structures without `inserts` after querying, you can keep a set of structures with sizes of power of 2, 
keeping only one structure with size `2^x` at a time.  
Always try to insert at the `2^0`-sized structure and solve `2^x` duplicates by merging and creating a `2^(x+1)`-sized structure.  
Query on all `O(log(elements))` structures.
  
Check: https://atcoder.jp/contests/abc244/tasks/abc244_h

### Implementing two pointers with 2 stacks / structures without `remove` `[ONLINE]`
**Query: `O(Q)`**  
**Insert: `O(I)`**  
A queue can be implemented using 2 stacks `A`, `B`, each stack will be responsible for a range `[lA;rA]` and `[lB;rB]`. The union of theses ranges is also contiguos.:
- New elements are added into `A`.
- Old elements are popped from `B`. When `B` reaches size `0`, build `B` using elements from `A`. Also, build it from `rB` to `lB`, that is, the top of the stack will be `lB`. Thus, when popping, elements from `[lB+1;rB]` will keep inside the structure.
- Query `A` then `B` and combine answers.
  
This is particularly useful if you are implementing 2 pointers in a structure without `remove` operation.  
  
Check: https://www.codechef.com/problems/MIXFLVOR

### Element `i` is available at time `i`. Query elements in `[lq;rq]` `[OFFLINE]`
**Query: `O(Q*log(N))`**  
**Insert: `O(I*log(N))`**  

Keep a segtree in which element available at time `i` is a leaf at position `i`.
Segments are built by mergining children just like normal segtree; 
node `(l;r)` will have all available elements from `l` to `r`.
  
Querying `[lq;rq]` is just like a normal segtree: at most `O(logN)` nodes will be visited. 
Since the query function is associative, combine answers from all visited nodes.
  
Check: https://codeforces.com/gym/103934/problem/L

### Element `i` is avaiable in `[li;ri]`. Query elements at time `i` `[OFFLINE]`
**Query: `O(Q*log(N))`**  
**Insert and delete: `O(I*log(N))`**    

First, note that we can create blocks of operations using queries as delimiters.
All insertions and deletions between two queries are joined to the block of the previous query. 
```
Q0: guard, phantom
(Q0 IIDI) (Q1 IDII) (Q2 DIDD) ...
B0        B1        B2        B...
```
If an element is inserted at `Bi`
- and deleted at `Bi`, no query will access it
- and deleted at `Bj, j > i`, only queries from blocks `[i+1;j]` will see it
 
Thus, 
- Create a segtree where each position is a block
- Add elements from `Bi,Bj` at segment `[i+1;j]` (range update)
 - As usual, decompose `[i+1;j]` in at most `log(N)` segments
- Query all segments containing `i` and combine answers from all of these
    
Check: https://codeforces.com/contest/678/problem/F  

### Removing from structures without `remove` `[ONLINE]`
**Query: `O(Q*sqrt(N))`**  
**Insert: `O(I*sqrt(N))`**  
TODO
