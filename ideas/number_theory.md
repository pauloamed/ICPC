# Number Theory

```
1- If D divides A and B, A < B, D divides B-A
2- Consecutive Fibonacci numbers are coprimes
3- floor(floor(A/B)/C) = floor(A/(B*C))
4- ceil(ceil(A/B)/C) = ceil(A/(B*C))
5- If x+y is prime, either (x=y=1) or (x and y have different parity)
```

#### Arithmetic progressions with same sum
Between perfect squares X^2 and (X+1)^2, intervals [X^2;X^2+X] and [X^2+X+1;(X+1)^2-1] have the same sum. First interval w/ size X+1 and second w/ size X. 

#### LCM of sequence
The LMC of `a_0, a_1, ..., a_n` is the productory of `p^max_e` for each prime `p` that occurs in the factorization of `a_i` where `max_e` is the maximum exponent `p` has between all `a_i`.

#### GCD of `X+A_i`
By `(1)`, `GCD(X+A_i,X+A_j)=GCD(X+A_i, A_i-A_j)` and now by associativity and idempotency, `GCD(X+A_0, X+A_1, X+A_2, ...) = GCD(X+A_0, A_1-A_0, A_2-A_1, ...)`

#### Number of pairs `(x,y)` in `[L;R]` s.t. `gcd(x,y)=k`
This can be done using inclusion-exclusion.  
Note that:
- Number of pairs `(x,y)` s.t. `gcd(x,y)` is a **multiple** can be computed using the number of multiples of `k` in `[L;R]`
  - `mult=` Number of multiples until `X` equals to `X/k`
  - Number of pairs s.t. gcd is a **multiple** of `k` equals to `mult*mult`
- Number of pairs `(x,y)` s.t. `gcd(x,y)` is **exactly** `k` equals to pairs `(x,y)` ... TODO ai depois subtrai

#### `A ^ (B ^ C) % P` (`P` prime)
We can solve `(X^Y) % P` using fast expo (1).
  
We want `(A ^ (B ^ C)) % P`, that is the remainder of `A ^ (B ^ C)` when divided by `P`. 
- If `A` is a multiple of `P`, answer is 0
- Else, note that, by Fermats Little Theorem, `A^(P-1) = 1 (MOD P)`. So, we only care about `x=(B^C) % (P-1)` which can be solved by `(1)`. Finally solve `A^x % P`

#### Number of `N`-length sequences ending at `X` with `A_i | A_(i+1)`
First, factorize `X = a^x * b^y * c^z * ...` .
This can be solved by choosing which of the `N` numbers will activate which primes from the factorization.  
Further reduced to, given `x` balls of color `a`, `y` balls of color `b`, `z` balls of color `c`, ..., how many ways can I distribute these balls over the boxes?
- Balls are independent from each other (multiply ans for each). Solve each using *bars and starts*: `C(N+x-1, x)`


## Permutations

### Recover permutation from inversion
Given a list of inversions `(i,j)` (there is an inversion between positions `i` and `j`),
recover the original permutation.  
  
Let `g(i):` number of inversions `(i,x)` (element at `i` is greater than `g(i)` elements after it)    
Let `s(i):` number of inversions `(x,i)` (element at `i` is smaller than `s(i)` elements before it)

Than, it must be that `value_i = i + g(i) - s(i)`
  
Check: https://codeforces.com/gym/101964/problem/I  

### Permutation graphs are the union of simple cycles
They just are. Every node has outdegree `= 1`.

### Swapping elements and number of cycles
By choosing `i` and `j` (`i!=j`) and swapping `p_i` and `p_j`, in the functional graph, the number of cycles (including a cycle of size 1) increases or decreases by 1.  

Proof: if elements are from the same cycle, we are dividing this cycle into 2 new ones. If they are from different cycles, we are merging them.  

For instance, in order to reach the `1,2,...,N` permutation, we need to get `N` cycles. Thus, swap `N-c` times (`c`: current number of cycles).

### Swapping elements for sorting
Let's say we want to sort an array **without duplicates**. Note that after compressing this array is a permutation.
Create the permutation graph where `i` points to `j` iff `j` is at position `i`.  
  
The number of swaps required for sorting this permutation is `SUM_cycle len(cycle)-1`.  
  
Also note that any swap between elements in the advances. That is, even if a swap does not put an element at its right position, it will advance since we are creating two new cycles, what compensates. Also, an element in its right position is a unicycle. Also note that a single element can be used in all swaps of a cycle for solving it if we always solve a position.
  
Check: https://atcoder.jp/contests/arc111/tasks/arc111_c
