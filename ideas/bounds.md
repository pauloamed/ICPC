### List of `K` funcs of the form `b + k*M` visiting elements in the range `[1;N]`
**There will be at most `O(sqrt(K) * N)` pairs `(M, pos)` visited.**
- Note that `(b, M)` is equivalent to `(b', M)` iff `b = b' (mod M)`  
- For each `M \in [1;...]`, there are `M` different values of `b` that are pairwise distinct
- The maximum possible number of visited positions occurs when `M[] = [1,2,3,...]` and their total contribution is `N`
- At most `sqrt(K)` `M` values will be activated if we force this configuration of `M[]`
- Thus, `O(contrib_of_M * num_M) = O(N * sqrt(K))`
  
Check: https://oj.uz/problem/view/APIO15_skyscraper  

### Pidgeon principle on complexity analysis
Check: https://atcoder.jp/contests/abc260/tasks/abc260_f
