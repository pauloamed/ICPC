# Algebra of data structures



## Some definitions
```
Neutral/Identity element I of a binary operation F: F(I,x) = F(x,I) = x
Monoid: set of numbers + associative binary operation w/ identity element
A unary operation F is compatible to a binary G iff F(G(a,b)) = G(F(a),F(b))
A binary opeation F distributes over a binary operation G iff G(F(a, c), F(b, c)) = F(G(a, b), c)
Inverse element of element X in a binary operation F w/ identity element I: the inverse of X is Y iff F(X,Y) = I
```

### Comments

#### Associativity of a binary operation
If an op. is associative, one can accumulate it.  
**Example:** instead of inserting `N` batches of size `1` of balls, one can insert `1` batch of `N` balls

### Structures

#### Non-Idempotent Sparse Table
- Associativity
- **Example:** sum, gcd

#### Idempotent Sparse Table
- Associativity
- Idempotence
- **Example:** gcd, max, min

#### Fenwick Trees
- Associativity
- Neutral
- Inverse if range query. Won't need if only handling preffixes.
- **Example:** sum, (prime) modular multiplication


#### Segtree
- Associativity
- Neutral
- **Example:** sum, gcd

#### Lazy Segtree
- There are two operations now. Let `F` be the lazy operation (or combination of operations) and `G` the query operation.
- Both need to be associative
- Both need to have a neutral element
- Concerning `F`
  - Implementing multiple update functions might be untrivial. Let's say however that you've found a function `F` such that all your updates can be expressed in terms of `F`.
  - Such will be in the format of `F(a, b, c, ..., x)` where `a`, `b` and `c` are operation arguments and `x` is the value in which we are applying the update.
  - Define the family of functions `G` where we fix the valid operation arguments: `F(a,b,c,x) => F_abc(x)`. It must be that `G` is closed under composition: `F_abc(F_def(x)) = F_xyz(x)`. That is, we can combine two updates into one update of the same form.
  - **Example:** combining `set` and `increment` as lazy updates into `F(set_flag, set_val, incr_flag, incr_val, x) = set_flag * set_val + incr_flag * (incr_val + x)`.
- Concerning `F` and `G`
  - If `F` is unary, `F` needs to be compatible to `G`
  - If `F` is binary, `F` needs to be distributive over `G`
  - It is not that simple though. For some operations, the argument may need to be a tuple `(value;l;r)`.   
  Eg.: `F` set and `G` sum: `set((a,l,m) + (b, m+1, r), (x*(r-l+1), l,r)) = set((a,l,m), (x*(m-l+1), l, m)) + set((b, m+1, r), (x*(r-m), m+1, r))`
- **Example:** `F` multiplication and `G` sum, `F` set_val and `G` sum, both `F` and `G` sum
