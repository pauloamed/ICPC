## XOR base

### Given that we consumed `N` elements, number of subsets w/ xor `= X`
**First, note that "number of subsets w/ xor `0`" equals `2^(N-B)`**, where `B` is the basis rank. 
This is because
- combinations of only basis vectors wont result 0 since these are independent
- assume we are only observing subsets of non-basis vectors. For each of these, only one combination of basis vectors will null it.

Answering for `xor = X` is similar, but
- If `X` is in SPAN, result is `2^(N-B)`
  - Suppose we are answering for `X=0` and at the end we `xor` all results w/ `basis(X)`
- If not, result is 0 (trivial)

### Allowing dependent vector into the basis - Odd length cycle

We can't add a vector to the basis unless it is independent from the other ones there.  
  
However, if we create a new dimension, and set it to `1` in every vector, we will be able to add a dependent vector to the basis
AS LONG AS it is formed by the combination of an even number of basis vectors.   
This will create an odd-length cycle with this added vector and the ones that formed it.
  
Check: https://codeforces.com/gym/101611/problem/I
