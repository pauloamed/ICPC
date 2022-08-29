# Strings

## KMP

### KMP with ordered patterns
KMP can also be used for ranked sequence matching i.e. find matchings of a `P_0 P_1 ... P_k` pattern in which, if `P_i > P_j` then `S_pi > S_pj` (`S_pi` char in substring matched to `P_i`). For this, we need to generalize the exact char matching (`P[i]==P[j]?`) of the original prefix function to a *can I fit `P[0:i]` into `P[j-i:j]`?* predicate. Such predicate .:
```
Given P[0:i] (pattern prefix I'm trying to fit) and P[j-i:j] (suffix for the current char),
If, for every distance D<i, the order relation (<,=,>) between (P_(j-D) and P_j) and (P_(i-D) and P_i)
(note that P_(j-D) is correspondent to P_(i-D)) are the same, then, the prefix can be fitted.

That is, in both prefix and suffix,
the last char which we are trying to add have the same order relation to the other chars positions.    

Note that, when trying to match to P[0:i], this same predicate was asserted for all char positions < i.    
Thus, only this new position needed to be checked.
```
Such formulation is however `O(n)`. Some optimizations can lead this to `O(1)`:
- `=> O(alphabet)`: for each possible value, we only need to check its last position. Suppose that our pattern has two occurrences of the same value, the second occourence has already accepted the first one, so we don't need to do this again.
- `=> O(1)`: it we are trying to fit value `v`, we only need to check the last potions of `prev(v)` and `next(v)` (not necessarily adjacent). Due to transitivity.


Check: https://szkopul.edu.pl/problemset/problem/6b-q_dPI_KRHD3VArapVq7EP/site/?key=statement  
Check: http://poj.org/problem?id=3167  

### KMP capabilities
**TODO**
Given two strings, KMP can solve in `O(n+m)`:  
1- biggest prefix from A that ends in `B[i]`  
2- biggest suffix from A that starts in `B[i]`: if a suffix `S` starts in `T[i]`, `S` and `S` suffixes end in `T[i]+len(S)-1`  
3- biggest substring between A and B  
4- biggest possibly rotated substring between A and B

### Put automaton on segtree
Read `segtree.md`.

### Compute KMP for common preffix and multiple suffixes
This is a nice exercise for understanding 2 things about KMP:
- Matching `S` to `S`
-- Building preffix function is basically trying to match `S` to itself. Note that `S` may well be seen as the concatenation of 2 strings.
- Complexity: 
-- It is amortized. Remember that there are 2 pointers: `pref` and `suf`. `pref:` current preffix-func value and `suf:` pointer to current char.
It is linear because `pref` and `suf` increment together and `pref` decresal is bounded by their value. However, amortization (?) can fail if you reuse a preffix computation on different suffixes. That is, imagine that for every new suffix we decrement `pref` that is `O(n)`. This leads to `O(n*q)`.  
-- For solving this, just use the idea of KMP Automaton (just precomputation / dynamic programming).


Check: https://codeforces.com/contest/1721/problem/E  

## Aho-chorasik
A Trie with fail/suffix links that resemble the prefix function.

### Precompute transitions?
You can choose to precompute transitions or not when using Aho.  

If you choose to precompute it, Aho will be seen as an Automaton in which all transitions are already computed. On the build phase, since all alphabet needs to be visited, a cost of `O(N*ALPHA_SIZE)` will incur.  
  
If you choose to not precompute it, processing a transition might search for a valid search link before advancing (what amortizes to `O(n)` on a input string, *but not on a input trie*).

### Online or offline
You can solve a multi-pattern matching problem with Aho either online or offline.

**Online**
You will solve while consuming string `S`. That is, if you visited node `v` of the Aho Trie, `v` needs to know all possible accepted states in it's subtree. Compute this in the `build` phase.

**Offline**
First process the input string, then solve the suffix-link tree problem.  In this tree, a vertex is a node in the Trie and edges are the fail links.  
Vertex `p` is parent of `v` if there is a fail link from `v` to `p`, that is, `p` is the max prefix that is also a suffix from `v`. Since `p` is a suffix from `v`, all matches that occur in `v` also occur in `p`.  
  
Thus, every match that occur in the subtree of `p`, occur also for `p`. This yields a tree subproblem:  
Traverse the tree, gathering matches in a structure so, when visiting `v`, you have access to all matches from its subtree. You which patterns were added to `v`, so these can be handled as queries in `v`.

### Process trie instead of string
One can search for patterns in a trie instead of in a string. 
For this, run a euler tour on the Trie in order to flatten it (treat it as a string); also keep a stack while processing the flattened string in the Aho. 
A timestep that enters a node will advance on the Aho and create push to the stack; a timestep that leaves will pop the stack.

## Trie are graphs/tree, solve graph/tree problems
In a typing context, you can think of a trie as a graph and run graph algorithms in it (eg. shortest path).
  
Check: https://codeforces.com/gym/101550/attachments/download/6031/20162017-acmicpc-nordic-collegiate-programming-contest-ncpc-2016-en.pdf - B 
  
Also, use euler tour decomposition and query/update efficiently on nodes of a trie.

Check: https://codeforces.com/contest/1207/problem/G
