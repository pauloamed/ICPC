### Hash polynome multisets
Some multisets `S` are well described by the union of `K` image multisets on contiguos points of polynomes.
For instance,
```
{1,2,3,4,5}: f(x) = x [1:5]
{1,4,9,16,12,8,4,0}: f(x) = x^2 [1:4] UNION g(x) = 4x [0:3]
{a, a+b, a+2b, a+3b, ..., a+kb}: f(x) = a + x*b [0:k]
{a, a+2b, a+6b, a+14b, ..., a+(k^2 - k)b }: f(x) = a + x^2*b - x*b [0:k]
```
Some tasks asks us to check is a set of numbers in a subarray `[L;R]` has a certain property that can be modelled as the union of polynomes images (as described above).  
For instance, checking if consecutive numbers in a subarray `[L;R]`, after sorting them, are all separated by the same delta can be modelled as checking if these numbers are the image of a polynome `g(x) = min_val + x * step` (where `step` is `(max_val - min val) / (rng_size - 1)`) (`min_val`, `max_val`, `rng_size` are specific from each subarray query).    
Other more arbitrary examples can be thought off by simply uniting polynomes.
  
Let's suppose (**1**) we can uniquely define a set of numbers by it's sum: `sum[L:R]` is the sum of elements in `L:R` and defines uniquely the (sorted) elements in it; `SUM_i 0...rngsize-1 g(i)` (**2**) equals to `(min_val) + (min_val + step) + (min_val + 2*step) + ...` and defines uniquely the polynome we are checking.  
  
Thus, if the sum of elements in `[L:R]` equals `SUM_i 0...rngsize-1 g(i)`, then, the subarray is the polynome we want and the query should answer `YES`. Otherwise, `NO`.
  
This idea presents yet 2 issues, marked above. These can be solved as follows:
- **1**: we can't assume that the sum of the numbers of a set will define it uniquely. However, using hash, we define each number `x` as `F(x)` where `F` is a fixed polynome w/ random coeficients, the probability that `sum S={s0, s1, ...}` defines `S` uniquely is high. Also, we can define multiple `Fi: F0, F1, F2` in order to ensure it (double, triple hash).
- **2**: we can't iterate from `0` to `rng_size-1` since that would be `O(N)`. However, since the desired set is the image of consecutive points of a polynome, the sum of these points is also a polynome. By this, we can find this sum-polynome using Lagrange Interpolation after sampling `DEG+1` points from it (`DEG <<< N`). Finally, if the desired set has size `K`, interpolate to find the `sum_g(K-1)` value and compare it to `sum[L:R]`.
  
Note:
- We can use the polynome hasher since the composition of polynomes is a polynome
- The degree of `sum_g` will be `deg(g) + 1 + deg(F)`: `deg(g)+1` since we are acumulating elements of `g` and `deg(F)` since it is composition of 2 polynomes.
  
Check: https://codeforces.com/group/XrhoJtxCjm/contest/422718/problem/J  
