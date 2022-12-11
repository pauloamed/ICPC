# Strings

## KMP

### KMP with ordered patterns
KMP can also be used for ranked sequence matching i.e. find matchings of a `P_0 P_1 ... P_k` pattern in which, if `P_i > P_j` then `S_(k+i) > S_(k+j)`. For this, we need to generalize the exact char matching (`P[i]==P[j]?`) of the original prefix function to a *can I fit `P[0:i]` into `P[j-i:j]`?* predicate:
```
Given P[0:i] (pattern prefix I'm trying to fit) and P[j-i:j] (suffix for the current char),
If, for every distance D<i, the order relation (<,= or >) between (P_(j-D) and P_j) and (P_(i-D) and P_i)
(note that P_(j-D) is correspondent to P_(i-D)) are the same, then, the prefix can be fitted.

That is, in both prefix and suffix,
the last char which we are trying to add have the same order relation to the other chars positions.    

Note that, when trying to match to P[0:i], this same predicate was asserted for all char positions < i.
Thus, only this new position needed to be checked.
```
Such formulation costs `O(n)` for checking the predicate. Some optimizations can lead this to `O(1)`:
- `=> O(alphabet)`: when adding `x`, for each possible value `y \in ALPHA`, we only need to check last position of `y`. 
Suppose that our pattern has two occurrences of the same value `y`, the second occourence has already accepted the first one, so we don't need to do this again.
- `=> O(1)`: it we are trying to fit value `v`, we only need to check the last potions of `prev(v)` and `next(v)` (not necessarily adjacent). Due to transitivity.


Check: https://szkopul.edu.pl/problemset/problem/6b-q_dPI_KRHD3VArapVq7EP/site/?key=statement  
Check: http://poj.org/problem?id=3167  

### Size of greatest prefix of A that ends in B[i] : `O(N+M)`
- `A = yabc`, `B = xabc`
- Create `A#B: yabc#xabc`
- `pi[j], j >= len(A) + 1` will keep the graetest prefix from `A#B` (prefix from `A`) that ends in `j` (`j-len(A)-1`-th position from `B`).
- `#` acts as a separator, not allowing info from `A` get into sufix ending at `B[]`

### Size of greatest suffix from A that starts in B[i] : `O(N+M)`
- `A = yabc`, `B = xabc`
- Create `rev(A)#rev(B) : cbay#cbax`
- `pi[j]`, `j = len(A)+1+i`, is the size of the greatest prefix from `rev(A)` (reversed suffix from `A`) that ends at `j` (at `i` in `rev(B)`)
- If something ENDS at `i` in a reversed string, it STARTS at `N-i` at the original strings

### Greatest common substring between `A` and `B` : `O(N(N+M))`
- `A = xabcd`, `B = xabc`
- Create `A#B: xabcd#xabc`
- Assume that we are solving the problem: greatest prefix from `A` that happens in `B`. Use "size of greatest prefix of `A` that ends in `B[i]` to solve it.
- Iterate through all `A[i:N-1]` suffixes from `A`: any substring can be seen as a prefix from a suffix. Solve the greatest prefix problem.

### Greatest possibly rotated substring between `A` and `B`
- `A = xcdabx`, `B = oabcdo`
- Let's say that the base form of the substring (to be found) is `abcd`. In `A`, it is splitted in `cd` and `ab`.
- We will explore all `N` splitting of `A` into preffixes and sufixes. 
 - Check the `xcd : abx` split.
 - Run "Size of greatest prefix of A that ends in B[i] : `O(N+M)`" between `abx` and `B=oabcdo`, saving the prefix function of `B` in `P0`
 - Run "Size of greatest suffix from A that starts in B[i] : `O(N+M)`" between `xcd` and `B=oabcdo`, saving the prefix function of `B` in `P1`
 - For every pair `i,i+1` positions in `B`
  - `P0[i]` preffix from `abx` that ends at `i`
  - `P1[i+1]` sufix from `xcd` that starts at `i+1`
  - `P0[i]+P1[i+1]` greatest rotated string that contains `i;i+1`


### Put automaton on segtree
Read `segtree.md`.

### Compute KMP for common preffix and multiple suffixes
This is a nice exercise for understanding 2 things about KMP:
- Matching `S` to `S`
-- Building preffix function is basically trying to match `S` to itself. Note that `S` may well be seen as the concatenation of 2 strings.
- Complexity: 
  - It is amortized. Remember that there are 2 pointers: `pref` and `suf`. `pref:` current preffix-func value and `suf:` pointer to current char.
It is linear because `pref` and `suf` increment together and `pref` decresal is bounded by their value. However, amortization (?) can fail if you reuse a preffix computation on different suffixes. That is, imagine that for every new suffix we decrement `pref` that is `O(n)`. This leads to `O(n*q)`.  
  - For solving this, just use the idea of KMP Automaton (just precomputation / dynamic programming).


Check: https://codeforces.com/contest/1721/problem/E  

## Suffix Array

### Unique substrings
Note that `LCP(i,i+1)` is the maximum size of a common prefix between suffixes that do not start at the same position.
If we are interested in unique substrings, we need to skip already ocourred strings using the LCP.
For instance,
```
ABABA:
4:A => >[A]
2:ABA => >[ABA]
0:ABABA => >ABA[BA]
3:BA => >[BA]
1:BABA => >BA[BA]
```
Here, `>[]` means a substring starting right after `>` and ending between `[` and `]`.
Note that `[` occurs after the LCP, implying that repeated substrings are skipped.
  
#### Representing unique substrings
For each suffix, we can represent the unique substrings that start at it by `(P, i)` where `P` is a common prefix and `i` is a starting position of the unique suffixes.
For instance, substrings that start at `0` can be represented as `(ABA, 3) = ABA+B, ABA+BA`.
  
This decomposition is particulary useful when substrings are associated with an associative score. 
`P` can be precomputed (associative) and suffixes starting at `i` can be solved using a suffix-query algo.
  
Check: https://codeforces.com/gym/102302/problem/K

## Aho-chorasik
A Trie with fail/suffix links that resemble the prefix function.

### Reverse patterns and input for finding starting positions
Instead of finding the ending positions, one can find the starting positions by reversing both input and patterns.
  
Check: https://www.beecrowd.com.br/judge/pt/challenges/view/683/7

### Precompute transitions?
You can choose to precompute transitions or not when using Aho.  

If you choose to precompute it, Aho will be seen as an Automaton in which all transitions are already computed. On the build phase, since all alphabet needs to be visited, a cost of `O(N*ALPHA_SIZE)` will incur.  
  
If you choose to not precompute it, processing a transition might search for a valid search link before advancing (what amortizes to `O(n)` on a input string, *but not on a input trie*). 

### Online or offline
You can solve a multi-pattern matching problem with Aho either online or offline.

**Online**
You will solve while consuming string `S`. That is, if you visited node `v` of the Aho Trie, `v` needs to keep info from accepted states that are ancestors. Compute this in the `build` phase.

**Offline**
First process the input string, then solve the suffix-link tree problem.  In this tree, a vertex is a node in the Trie and edges are the fail links.  
Vertex `p` is parent of `v` if there is a fail link from `v` to `p`, that is, `p` is the max prefix that is also a suffix from `v`. 
Since `p` is a suffix from `v`, all matches that occur in `p` also occur in `v`.
  
Thus, every match that occur in the subtree of `p`, occur also for `p`. This yields a tree subproblem:  
Traverse the tree, gathering matches in a structure so, when visiting `v`, you have access to all matches from its subtree.
You which patterns were added to `v`, so these can be handled as queries in `v`.

### Process DAG/trie instead of string
One can search for patterns in a DAG/trie instead of in a string. 
For this, run a euler tour on the Trie in order to flatten it (treat it as a string); also keep a stack while processing the flattened string in the Aho. 
A timestep that enters a node will advance on the Aho and create push to the stack; a timestep that leaves will pop the stack.
  
Check: https://www.beecrowd.com.br/judge/pt/challenges/view/683/7

## Trie are graphs/tree, solve graph/tree problems
In a typing context, you can think of a trie as a graph and run graph algorithms in it (eg. shortest path).
  
Check: https://codeforces.com/gym/101550/B 
  
Also, use euler tour decomposition and query/update efficiently on nodes of a trie.

Check: https://codeforces.com/contest/1207/problem/G
