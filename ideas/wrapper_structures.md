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

### Removing from structures without `remove` `[OFFLINE]`
**Query: `O(Q*log(N))`**  
**Insert: `O(I*log(N))`**  
**Remove: `O(R*log(N))`**  
TODO

### Removing from structures without `remove` `[ONLINE]`
**Query: `O(Q*sqrt(N))`**  
**Insert: `O(I*sqrt(N))`**  
TODO
