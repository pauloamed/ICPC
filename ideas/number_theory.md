# Number Theory

## Prime and modular arithmetic

```
1- If D divides A and B, A < B, D divides B-A
2- Consecutive Fibonacci numbers are coprimes
3- floor(floor(A/B)/C) = floor(A/(B*C))
4- ceil(ceil(A/B)/C) = ceil(A/(B*C))
5- If x+y is prime, either (x=y=1) or (x and y have different parity)
6- First multiple of `x >= L`: `ceil(L/x)*x`
```

### Finding primes in `[L;R]`: find primes until `sqrt(R)` : mark as sieve
Note that `x \in [L;R]` is prime iff it is not divisible by any prime `p <= sqrt(R)`.
- Find all primes smaller than `sqrt(R)`
- For each found prime, mark elements inside such range divisible by it
  - Harmonic series, `O(NlogN)`

### Arithmetic progressions with same sum
Between perfect squares X^2 and (X+1)^2, intervals [X^2;X^2+X] and [X^2+X+1;(X+1)^2-1] have the same sum. First interval w/ size X+1 and second w/ size X. 

### LCM of sequence
The LMC of `a_0, a_1, ..., a_n` is the productory of `p^max_e` for each prime `p` that occurs in the factorization of `a_i` where `max_e` is the maximum exponent `p` has between all `a_i`.

### GCD of `X+A_i`
By `(1)`, `GCD(X+A_i,X+A_j)=GCD(X+A_i, A_i-A_j)` and now by associativity and idempotency, `GCD(X+A_0, X+A_1, X+A_2, ...) = GCD(X+A_0, A_1-A_0, A_2-A_1, ...)`

### Number of pairs `(x,y)` in `[L;R]` s.t. `gcd(x,y)=k`
This can be done using inclusion-exclusion.  
Note that:
- Number of pairs `(x,y)` s.t. `gcd(x,y)` is a **multiple ok `k`** can be computed using the number of multiples of `k` in `[L;R]`
  - `mult(A, k):` Number of multiples of `k` until `A` `= A/k`
  - `mult(L,R,k) = mult(R,k) - mult(L-1,k)`
  - Number of pairs s.t. gcd is a **multiple of `k`** equals to `mult(L,R,k)*mult(L,R,k)`
- Number of pairs `(x,y)` s.t. `gcd(x,y)` is **exactly** `k` equals
  - pairs which `gcd = k`: pairs that are multiple of `k` but not exactly `2k`, `3k`, `4k`
  - `exact[i]`: number of pairs which gcd is exactly `i`
  - Go from `R` to `L`, computing `exact[]`, and, when at `i`, `exact[]` will be already computed for all multiples of `i`

Check: https://atcoder.jp/contests/abc206/tasks/abc206_e

### `A ^ (B ^ C) % P` (`P` prime)
We can solve `(X^Y) % P` using fast expo (1).
  
We want `(A ^ (B ^ C)) % P`, that is the remainder of `A ^ (B ^ C)` when divided by `P`. 
- If `A` is a multiple of `P`, answer is 0
- Else, note that, by Fermats Little Theorem, `A^(P-1) = 1 (MOD P)`. So, we only care about `x=(B^C) % (P-1)` which can be solved by `(1)`. Finally solve `A^x % P`

### Number of `n`-length sequences ending at `X` with `A_i | A_(i+1)`
First, factorize `X = a^x * b^y * c^z * ...` .
This can be solved by choosing which of the `N` numbers will activate which primes from the factorization.  
Further reduced to, given `x` balls of color `a`, `y` balls of color `b`, `z` balls of color `c`, ..., how many ways can I distribute these balls over the boxes?
- Balls are independent from each other (multiply ans for each). Solve each using *bars and starts*: `C(N+x-1, x)`

### Schur's theorem and Frobenius: linear combination of elements w/ gcd=1
**Linear combination**: every weight is non-negative  

For every set of numbers w/ `gcd(A_i)=1` there exists a arbitrary large number that can be expressed as a linear combination of `A_i`

#### Frobenius / Coin problem
The largest number that cannot be expressed as a linear combination of a set of numbers w/ `gcd(A_i)=1` is called the **Frobenius number** of this set.  
If `n=2`, `f(A) = a_0 * a_1 - a_0 - a_1`

### Bezout's identity and diofantine equations
Let `gcd(a,b)=d`, then there are `x,y` integers s.t. `ax + by = d`.  

Given a solution `(x,y)`, all other solutions have the form:
```
(x - k * b/d , y + k * a/d)
```

#### 3 or more variables
If `gcd(A_0, A_1, ... A_n)=d`, then there is a solution for
```
d = x_0 * A_0 + x_1 * A_1 + ... + x_n * A_n
```
where `d` is the smallest positive integer of this form

### Chinese Remainder Theorem

Given a systems of modular equations, find a solution.
Solution is of the form `A (MOD M)`.
That is, `X = M * k + A`, for any integer `k`.

Input can be of the form:
```
X = A_0 (MOD M_0)
X = A_1 (MOD M_1)
...
X = A_N (MOD M_N)
```

Or given as integer line equations:
```
X = M_0 * x_0 + A_0
X = M_1 * x_1 + A_1
...
X = M_N * x_N + A_N
```
Constraints on `x_i` will be constraints on `k`.
Eg, if `x_i >= 1`, `N >= M_0 + A_0`; implying that there exists a `k_min` s.t. `k >= k_min` needs to happen.

Check: https://codeforces.com/gym/101472/problem/H

## Counting

### Extended stars and bars
Stars and bars: number of ways to split a `N` sized array into `K` sub-arrays.  
Solve using combination: create `K-1` artificial elements for acting as splitters (bars).  
Choose `K-1` elements from `N+K-1` to be bars; the other `N` elements will the stars (elements to be splitted).  

The first extension concearns forcing each array to be non-empty.   
For this, just pretend that there are `N-K` elements to be splitted by assigning previously one to each array.  
  
Other extension builds on, instead of selecting only `K-1` elements, selecting also some of the stars.  
For instance, how many ways to partition into `K` subarrays and choose one element from each array.  
For this, `C(N + K - 1, 2*K - 1)` does the job, because we are selecting extra `1*K` elements.  
We choose `K-1` bars and `K` stars, disposed as `S B S B ... S`.  
  
One can also vary the interleaving between stars and bars.  
For instance, select an element from at most `3` boxes. We are then interested in how many ways can one interleave `K` `B`s and 3 `S`s such that there are no `S` adjacent.
Suppose that `f(K, 3)` counts this. The final answer would be `C(N + K - 1, K - 1 + 3) * f(K, 3)`.

### Stars and bars: Sum of products of `f(`subarrays sizes`)`
  
Stars and bars can be formulated as:
```
SUM (for each S_1 + S_2 + ... + S_K = N) 1 [S_i: size of ith subarray]
or
SUM (for each S_1 + S_2 + ... + S_K = N) f(S_1)f(S_2)...f(S_K) [productory of f over sizes],
where f(m) = 1
```
  
In other problems, it may be a different `f`. 
It is nice when `f(S_i)` can be expressed as `C(S_i, l)`
For instance (https://atcoder.jp/contests/abc214/tasks/abc214_g), `f(S_i) = S_i = C(S_i, 1)`.
In this problem, we are interested in the sum of all products of subarray sizes from each possible partition.
   
If `f(S_i) = C(S_i, l)`, we can think of choosing `l` elements from each of the `k` splitted subarray (of size `S_i`).
That is, we want all possible manners of splitting `N` elements in `k` subarrays and combine the ways of choosing `l` elements from each:
`C(N + k - 1, k - 1 + l * k)`

## Permutations

### Recover permutation from inversion
Given a list of inversions `(i,j)` (there is an inversion between positions `i` and `j`),
recover the original permutation.  
  
Let `g(i):` number of inversions `(i,x)` (element at `i` is greater than `g(i)` elements after it)    
Let `s(i):` number of inversions `(x,i)` (element at `i` is smaller than `s(i)` elements before it)

Than, it must be that `value_i = i + g(i) - s(i)`
  
Check: https://codeforces.com/gym/101964/problem/I  

### Permutation graphs are the union of simple cycles
They just are. Every node has out and in degree `= 1`.

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

### How many lists of elements given that values `<=i` happen at most `f(i)` times; f() non-dec; any size; order matters
Values range from `1` to `MAX=3`. Examples for this: `[1,2,3], [1,3,3], [3,1,1]`.
  
Solve this using push-DP.  
`f(n, j):` current size of `n` and only elements with value `<= j` are being considered.
  
Compute this by iterating through values from `1` to `MAX`.
For each new value `i+1`, itereate through how many `x` elements from this value will be added.
It must be that `x + n <= f(i+1)`.  
There are `C(x + n, x)` ways of interleaving these new elements.
```
dp[0][0] = 1
for i: 0...MAX-1:
  for n: 0...f(i):
    for x: 0...(n + x <= f(i + 1)):
      dp[i + 1][n + x] += C(x + n, x) * dp[i][n]
```

Check: https://codeforces.com/gym/104012/problem/I

## Inclusion-Exclusion

There is a set `P` of properties. `f(T), T \in P,` equals the number of elements that satisfy at least properties in `T`.  
`f(empty):` num. of elements that satisfy any property, but at least one
```
f(empty) = SUM_k_1_N (-1)^k (SUM_T\inP_|T|=k f(T))


for every set size k from 1 to N:
  for every subset T of P of size k:
    ans += f(T) * (-1) ^ k
```

**Homogeniety: `|A| = |B| -> f(A) = f(B)`**. If homogeniety of properties is true, it can be simplified to
```
f(empty) = SUM_k_1_N (-1)^k C(N, k) * f(k)
```
There can be less obvious forms of homogeniety also.   
The main idea however is group sets `T` of size `k` by `f()`.  
Suppose that we can partition the property sets `T`s by the count of a `l` i.e. `(|A| = |B| && cnt(Al) = cnt(Bl)) -> f(A) = f(B)`.  
Then, count the number of sets with size `k` and `l` (similar to the `C(N,k)` above) and multiply by `f(k, l)`.
  
Check: https://atcoder.jp/contests/abc214/submissions/36887251

### Defining properties to compute answer (mainstream)
  
If the problem asks for number of configurations that respect (AND) a list of constraints,
it may be useful to define a propertie as the negation of each constraint and compute `all - f(empty) = elements with zero properties`.
  
Meanwhile, if problem asks for number of configurations w/ at least one constraint true, define a property for each constraint and find `f(empty)`.

#### More on modelling

The same problem can accept different modellings of properties.
For instance, in (https://atcoder.jp/contests/abc214/tasks/abc214_g), 
we have a list of `K` constraints:
- `r_0` != `p_0` AND `r_0` != `q_0`
- `r_1` != `p_1` AND `r_1` != `q_1`
- ...
  
We will negate these contraints and compute `all - f(empty)`. This can be done in 2 ways:
- **Ap1**: `r_i` = `p_i`
- **Ap2**: `r_i` = `p_i` OR `r_i` = `q_i`  
Using **Ap1** approach, there would be `2K` properties and this can be modelled to selecting **nodes** from a graph.
In **Ap2**, there would be `K` properties and this can be modelled to selecting **edges** from another graph.
   
### Examples
- Solution to `x1 + x2 + ... + xn = K` w/ `xi <= Ai` constraints
  - Define `P_i` as `xi > Ai`. Find `all - f(empty)`.  
  - `f({xi > Ai, xj > Aj}): #confs x1+x2+...+xn = K-(Ai+1)-(Aj+1)`
- Solution to `x1 + x2 + ... + xn = K` w/ `xi <= M` constraints
  - Define `P_i` as `xi > M`. Find `all - f(empty)`.  
  - Note that **homogenity** holds.  
  - `f(k): #confs x1+x2+...+xn = K-k*(M+1)`
- Number of onto (surjectives) functions `A -> B`
  - Define `P_i` as `Bi not in range(f)` (`Bi` is element in `B`). Find `all - f(empty)`.   
  - Note that **homogenity** holds. 
  - `f(k): #confs w/out k elements = (|B|-k)^|A|
- Derangements; permutation not keeping original position
  - Define `P_i` as `p_i staying in i`.  Find `all - f(empty)`.
  - Note that **homogenity** holds. 
  - `f(k): #perms fixing k positions = (n-k)!`
  - Check: https://atcoder.jp/contests/abc214/tasks/abc214_g
- Permutations of `R`, `G` and `B` elements without `RG` occuring adjacent
  - A property `P` here would be an occurence of `RG`: there are a lot of properties and distinguishing them is not the objective
  - Here, instead of counting 
  ```
    How many ways to select `k`-sized property sets
    Given a fixed set of `k` properties, how many permutations have at least this exact set
  ```
  - It is done
  ```
  Compute all possible permutations where at least `k` properties are satisfied, varying which
  properties composed the `k`-sized set
  ```
  - Check: https://atcoder.jp/contests/abc266/tasks/abc266_g

