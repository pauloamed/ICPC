# Divide and Conquer

- Segtree is divide and conquer with memoization and update.  
Check: https://neps.academy/br/exercise/1107

## D&C Optimization
**Prerequisite: Monge condition**
```
For each (a < b <= c < d),
f(a, c) + f(b, d) <= f(a, d) + f(b, c) [Convex monge]
f(a, c) + f(b, d) >= f(a, d) + f(b, c) [Concave monge]
```
**Suppose we are evaluating**
```
f(i) = min_(j<=i) (cost(j, i)) (can also be max)
```
Lets call `A_i` the best `j` for `f(i)`.
It can be that `A_i` is monotone increasing (decreasing for max).
That is, if `j > i`, `A_j >= A_i`.
This can be noted by:
- printing the points, intuiton, pattern
- Checking that `cost(i,j)` is convex monge (if max, concave monge)
  
Having such propery allows us to enhance a `O(N^2)` evaluation into a `O(NlogN)` evaluation. 
  
This is done by using D&C: find `A_i` for `i=mid` than recurse on each half. The search points `A_k` for the left part are all `A_k <= A_i` and for the right part all `A_k >= A_i`. These splits create a partition over the search space, having each point being visited at most `O(logN)` times.

**Note:** it can be that `cost(l,r) = C(l,r) + f(l)`. If `C()` is convex/concave monge, so it is `cost`.

Examples of problems:
- Partition array into `K` contiguos sets. Cost of a `[l;r]` set is `C(l,r)` which is monge.
  - Check: https://www.hackerrank.com/contests/ioi-2014-practice-contest-2/challenges/guardians-lunatics-ioi14
  - Check: https://www.codechef.com/problems/CHEFAOR
  - Check: https://acm.timus.ru/problem.aspx?space=1&num=1167  
  - Check: https://oj.uz/problem/view/APIO14_sequence  
- Find best range `[l;r]` for maximizing `f(l,r)` knowing that `best_l()` for `r` is monotone decreasing.
  - Check: https://atcoder.jp/contests/arc067/tasks/arc067_d
- Find best pair of elements `(a_i, b_j)`, `a_i \in A` and `b_j \in B`, that maximize a function. Best element `b` for `a` is monotone.
  - Ex.: Maximal rectangle area given list of bottom-left and list of upper-right corners. Check: https://open.kattis.com/problems/money

## Max/min/coprime in range

Max, min and coprimes work as segments partitioners. I mean:
- if `a[i]` is max/min in `[l;r]`, only segments not including `i` will have a different max/min value. 
  - Thus, intervals `[l;i-1]` and `[i+1;r]` are now subproblems.
- If `a[i]` is coprime from `[l;r]`, `gcd([l;r])=1`. 
  - Thus, intervals `[l;i-1]` and `[i+1;r]` are now subproblems (might still hold `gcd=1`).
Check: https://codeforces.com/contest/1156/problem/E
Check: https://codeforces.com/gym/101623/problem/F

## Count good subarrays `(L, R1, R2)` inside query `[Lq;Rq]`
Count good subarrays inside `[L;R]` given that:
- it is given a list of good subarrays in the format `(L, R1, R2)` s.t. every subarray `[L;r]`, `R1 <= r <= R2` is good
- a subarray of a good subarray is also good

Solve this as follows:
- sort queries and good subarrays decreasing in `L`
- iterate through queries in order to process queries `[ql;qr]` s.t. `L >= ql`
- keep a segtree s.t. `seg[i]: ` count of good subarrays until `i` (starting at `L` that we keep decreasing)
  - this `seg` works as a prefix sum
- when a query `[ql;qr]` is processed, it's answer is `seg[qr]`
- when a good subarray `X = (L,R1,R2)` is processed, note that:
  - every interval `[L;r]` s.t. `r > R2` contain all good subarrays from `X`
  - every interval `[L;r]` s.t. `R1 <= r <= R2` contain `r-R1+1` good subarrays from `X`
- in terms of `seg`, this means
  - every `i > R2` in `seg` should be incremented by `R2-R1+1` 
  - arithmetic progression (from `1` to `R2-R1+1` w/ step `1`) update at range `[R1;R2]`  
  
Check: https://codeforces.com/gym/101991/problem/G

## Find minimal good interval containing query `[Lq;Rq]`, good intervals are decomposable

There are good intervals w/ the following properties:
- if two good intervals have a intersection, their union is also a good interval. 
  - thus, **each interval might be decomposed into two intervals that intersect (\*)**.
- there can be at most `O(N^2)` good intervals

We want to answer queries `q=[Lq;Rq]` by finding the minimal good intervals containing `q`.

Note that there are 3 cases for a good interval `[Ls;Rs]` totally inside `[L;R]`:
1- `[m;m+1]` is in `[Ls;Rs]`
2- `[Ls;Rs]` is in `[L;m-1]`
3- `[Ls;Rs]` is in `[m+1;R]`

For each query inside `[L;R]`, a good intervals that contains in might be from case `1` or either `2` or `3`.

There may be `O(N^2)` good intervals inside `[L;R]` that contain [m;m+1]. 
For handling this, we want to decompose each `[Ls;Rs]` into two **good** intervals that intersect **(\*)**:
- `left`: `[ll;rl]` s.t. `L <= ll <= m` and `m+1 <= rl <= R`
- `right`: `[lr;rr]` s.t. `L <= lr <= m` and `m+1 <= rr <= R`
- note that `A` and `B` intersect at `[m;m+1]`.
- `min(ll, lr) = Ls` and `max(rl, rr) = Rs`

Note that this decomposition isn't unique (there may be different intervals `left` and `right` that satisfy these properties).
We can thus think of an efficient way to decompose these. Note that if, 
- for each `l` in `[L;m-1]`, we find the minimum `r` in `[m+1;R]` s.t. `[l;r]` is good and, (`left`)
- for each `r` in `[m+1;R]`, we find the maximum `l` in `[L;m-1]` s.t. `[l;r]` is good, (`right`)
- `right` and `left` intervals still intersect with each other
- every `[Ls;Rs]` will have a `left` and `right` interval that united result in `[Ls;Rs]`
We will have found `O(N)` good intervals that decompose all good intervals `O(N^2)`. 

For computing `left` and `right` a greedy algorithm is used. A sketch for `left` is shown:
- Start a `l` pointer at `m` and a `r` pointer at `m+1`. We want to find, for each `l` in `[L;m-1]`, the minimum `r` in `[m+1;R]` s.t. `[l;r]` is good. Thus, we will be decrementing `l` and incrementing `r` when needed.
- Try build a good interval for the current `l`. The current numbers inside `[l;r]` are `S`.
 - If `S` is contiguos, this is a good interval, decrement `l`.
 - If number `x` is missing in `S`
   - If `x` is before `l`, there isn't a good interval for `l`. Decrement it.
   - Else (if `x` is after `r`), increment `r` and add `v[r+1]` to `S`.

Thus, for a query `[Lq;Rq]` being processed in `[L;R]`:
- binary search a `left` interval `[ll;rl]` for it s.t. `ll <= Lq` and `ll` is max
- binary search a `right` interval `[lr;rr]` for it s.t. `Rq <= rr` and `rr` is min
- merge `[ll;rl]` to `[lr;rr]`
- if `Rq < m` or `Lq > m` solve this query in `[L;m-1]` or `[m+1;R]` respectively
  
Check: https://codeforces.com/gym/101620/problem/I

## CDQ
Divide and Conquer CDQ; which is actually D&C in which merging also orders points and doing query/update on the fly; which is actually D&C offline;
  
The problem it solves is, given a list of 3d points, say, for each point, how many points that point dominates.
We say that a point A dominates another point B if all coordinates of A are greater (or equal) to those of B.
  
The idea is to order the points so that, if point `A` dominates point `B`, `index(A) < index(B)`.
Then, for each merge with `[l;m]` and `[m+1;r]`, we will compute the interference of the points in `[m+1;r]` that dominate the points in `[l;m]`.
The ordering ensures that there is no dominance relation in the opposite order.
  
Given that we have the subsets `[l;m]` and `[m+1;r]` and that the dominance relation only occurs from right to left, we can think of
the points of `[l;m]` as updates and those of `[m+1;r]` as queries (we want to know how many left points each right point dominates).
  
This subproblem looks like this same problem of dominance in 2D, which is kind of common.
To solve this one, we order the 2D points by the first coordinate and use a BIT in the second coordinate.
The order guarantees that if a point is dominated by me, it has already been processed and the BIT allows querying all values less than or equal to me quickly.
Differently, now, the points for querying come from one list and the ones for updating come from another list (in the original 2D problem they are the same list).
And we need to make sure that, before computing a query, all the update points that can be dominated by the query have been processed.
  
Processing these two lists in an ordered fashion gives us (for free) a new ordered list. That is, we sorted and processed the queries and updates in the same step.
It looks like MergeSort.
  
This technique is nice, but it seems to be kinda useless because we can use a compressed BIT2D. Both need to be used offline.
  
This technique is nice for matrix query/update problems because we use the time of the events (query or update) as a dimension, which guarantees the processing of all relevant events prior to the current one.
  
Cost: `Q*log(Q)*log(dim)`

Check: https://robert1003.github.io/2020/01/31/cdq-divide-and-conquer.html
