# Transforming
Stuff to try for changing perspective over some problems.

### Abs vs. min function
It is true that `∣∣x−a∣−b∣=min(∣x−(a−b)∣, ∣x−(a+b)∣)`.
  
In a problem where we are interested in minimizing `q(x) = min_i(||x-a_i|-b_i|)`, we can apply this reduction, simplifying the problem to finding the closes point (between all `a_i-b_i`, `a_i+b_i`) to `x`.  
  
Check: https://atcoder.jp/contests/arc155/tasks/arc155_b  

### Operations on subarrays
#### Inverting bits of subarrays
If you have a bit-array `a` and do operations of subarrays bit inversion, there is a bijection to it:
- use the transformed array `b[i] = a[i - 1] ^ a[i]`
- inverting `[l:r]` in `a` is equivalent to inverting `b[l]` and `b[r+1]`
  
Check: https://codeforces.com/gym/101519/problem/D  

#### Summing on a contiguos subarray
Some problems have the operation to sum on contiguos subarrays. Also, depending on the objective, it makes transforming the original array to an array of differences:
- define `bi = a(i+1) - ai`
- assume, enforce `a0 = an + 1 = 0`
- transforming: `0, a1, a2, ..., an, 0 => a1, a2 - a1, a3 - a2, ..., -an`
    
Under this transform, note that all `ai` are 0 iff all `bi` are 0.
Now, consider the operation: add `c` to `a[i:i+k-1]`.
In `b`, this translates to `bi+=c`, `b(i+k)-=c`.
  
Thus, the problem of using this operation in `a` to turn it to `0` can be translated to the equivalent operation and constraint in `b`.  
    
Check: https://atcoder.jp/contests/abc288/tasks/abc288_d  

### Constructive: `x_0 < x_1 < x_2 < ...` => `y_0, y_1, y_2, ...`
You need to build a sequence with a `x_0 < x_1 < x_2 < ...` constraint between variables.
It may be better to change this to constraint over each variable. 
Do this by defining
```
y_i = x_i - x_i-1, i > 0
y_0 = x_0
```
Now, it must be that `y_i > 0` for `i > 0`.
  
Check: https://atcoder.jp/contests/arc153/tasks/arc153_c

### Rotation and reversal of arrays
It is performed several rotations and reversals of an array `N=10^5`, find the final configuration of it.  
  
Basically, perform `p = -p % n` and `p = (p + x) % n` operations in a position `p`.  
Note that these operations can be merged. In the end, just apply the final result to each `i`.
  
Check: https://atcoder.jp/contests/arc153/tasks/arc153_b

### Objective function is a ratio
Let's say each element has a profit `p` and a cost `c`.  
We are selecting a subset of elements s.t. its final cost is `sumP / sumC`, a ratio.
  
You want to find the subset of greatest ratio. You can't use the cost function as is since it is tricky. Do binary search instead:
```
Find greatest R s.t.:
sumP / sumC >= R
sumP >= R*sumC
sumP - R*sumC >= 0
Since P and C are indexed by edges,
sum(p - R*c) >= 0
```
Define a new cost for each element: `p - R*c`. The predicate is true iff there exists a subset w/ non-negative cost.
  
If elements are edges and we interested in cycles, try to use Floyd-Warshall for searching any non-negative cycle.  
Check: https://oj.uz/problem/view/APIO17_merchant  
  
Some tweaks but same main idea. Check: https://atcoder.jp/contests/abc275/tasks/abc275_g

### Maximum size with bounded cost
Can also be solved finding minimum cost for each size and taking the greatest size with cost inside the bounds.

### Convert median to binary vector of `>= x`
Depends on the definition of median.  
Checking the median of a list can be done by binary searching it (search key is `x`) and setting all values `vi` to `eval(vi>=x)`. 
The first value in the search space s.t. `cnt 1s >= N/2` is the median.  
  
Check: https://atcoder.jp/contests/abc107/tasks/arc101_b

#### Median on sub-arrays `[TODO]`
https://codeforces.com/blog/entry/18879?#comment-238126

#### Game: A chooses max vs. B chooses first free
Transform: set bottom half elements to `1` and top half to `-1`  
  
If we apply this transform, A can get N/2 top values if every prefix sum of the vector is non-negative. 
  
Check: https://atcoder.jp/contests/arc138/tasks/arc138_c

### Maximize active variables with clauses `NAND`
`A NAND B`: `A` or `B` but not both. This reduces to maximum independent set where edges are such clauses.
  
Check: https://codeforces.com/gym/101666/problem/E


### Don't put `x` and `y` in the same set (there are 2 sets)
Create a graph `G` such that if `x` and `y` can't be together, there is an edge `(x,y)` in it. We thus want to check if this graph is bipartite.

### Matchings and sums
Lets say we have sets `A` and `B` and we are assigning elements from `B` to `A`. Each element from `B` can only be assigned to one in `A`.  
If `cost(a) = sz(b) + cost(b)`, i.e. the cost of assiging `b \subset B` to element `a` equals to a `cost(b)` plus `sz(b)`,
- Then we can update values in `B` with `-1` since this value will always be accounted in the final result.
- It is like every element has a contribution to `sz(b)` and, since element will be used **exactly** once, we can compute this contribution beforehand.


### Manipulating conditions w/ multiple variables

Check: https://oj.uz/problem/view/JOI18_art
  
**Building a sequence**  
Let's say we have the following condition `|a_j - a_i| <= v(t_j - t_i)` for building a sequence.  
  
This can be manipulated to `a_j - a_i <= vt_j - vt_i` and further to `a_j - vt_j <= a_i - vt_i`. 
If we define `x_i = a_i - vt_i`, we can reduce this to `x_j <= x_i`.
  
Similarly, this can be manipulated to `a_i - a_j <= vt_j - vt_i` and further to `a_j + vt_j <= a_i + vt_i`. 
If we define `y_i = a_i + vt_i`, we can reduce this to `y_j <= y_i`.
  
These two (`x_i` and `y_i`) were possible since `|a-b| <= T iff a-b <= T AND b-a <= T`. 
We are now trying to build the longest (non-strictly) increasing subsequence following `x_i <= x_j AND y_i <= y_j`.
  
If there are multiple conditions `AND`, it is feasible to reduce these to `(x_i <= x_j, y_i <= y_j, ...)`  and solve this as the longest increasing subsequence of tuples.

Check: https://codeforces.com/contest/1662/problem/L

**Count intervals w/ ratio > `X`**  

Another example using preffixes. Count the number of intervals `[L;R]` s.t. the ratio of active bits over its size is greater than `X`:
```
sum_1 / sz > x <=> (sum_r - sum_l) / (r - l) > x <=> 
(sum_r - sum_l) > x (r - l) <=> sum_r - sum_l > xr - xl <=> 
sum_r - sum_l > xr - xl <=> sum_r - xr > sum_l - xl <=> 
y_r > y_l
```  
Check: https://codeforces.com/gym/102134/problem/D
