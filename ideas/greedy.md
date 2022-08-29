
# Greedy

### Argument exchange
When trying to find the optimal order for a greedy, analyze the relation between only 2 elements. Define a cost function `f` capable of computing over both orders `AB` and `BA`. Check wich conditions are held for `f(AB) < f(BA)` (assuming `A` goes first).

### Find `k`-th lexicographically smallest sequence
Let's say we can count how many sequences can be genereted by adding `x` at the `i-th` position.  
The problem can be then tackled as a `n`-ary (like Trie) structure in which we can visit nodes in order until the `k`-th sequence is reached.  
After adding `x`, we visit a subproblem which can be tackled in the same way. This is a recursive procedure like searching for the `k`-th smaller node on a binary tree.
  
Check: https://codeforces.com/gym/102433/problem/F

### Building optimal sequences
TODO

Check: https://codeforces.com/gym/103640/problem/M  
Check: https://codeforces.com/contest/678/problem/E

### Maximize sum of `N`, choosing between options `A` and `B` for each element, where the max count of option `A` is `k`
Let's say you want to maximize `sum` of an array of size `N` and that, for each element, you can choose between `a_i_A` and `a_i_B`. But there can be only `k` elements with option `A` choosen.
  
What you can do is:
- Suppose you choose option `B` for all elements. Store this sum in `sumB`
- Sort elements using their balance `a_i_A - a_i_B`. This balance means "how much is it worth to change from `B` to `A`". 
- Iterate through the sorted elements, visiting the first `k`, converting them from `B` to `A`: `sumB -= a_i_B` and `sumA += a_i_A`. Since `bal = a_i_A - a_i_B`, you can also use `sumA += bal + a_i_B`.

### Distributing `k` different block (from a list of pile of blocks) to each person
Suppose you have a list of piles of blocks `A_i`. For each person, we want to give `k` different blocks. If we have `x` people, what is the maximum `k`?
  
The following holds: if `k * x <= sum(min(A_i, x))`, then you can distribute `k` different blocks to `x` people.  
  
It helps if we visualize the problem as filling up a matrix with `x` lines and `k` columns. 
We will be distributing each line to a different person.
  
Keep filling column by column while iterating through the pile of blocks. Since every element has at most `x` instances, there won't be the case in which the same element goes into the same line.
  
The maximum number for `k` is thus `sum(min(A_i, x))/x`. That is, distribute every block and get the number of completed columns.
