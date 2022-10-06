# Divide and Conquer

- Segtree is divide and conquer with memoization and update.  
Check: https://neps.academy/br/exercise/1107

### Max/min/coprime in range

Max, min and coprimes work as segments partitioners. I mean:
- if `a[i]` is max/min in `[l;r]`, only segments not including `i` will have a different max/min value. 
  - Thus, intervals `[l;i-1]` and `[i+1;r]` are now subproblems.
- If `a[i]` is coprime from `[l;r]`, `gcd([l;r])=1`. 
  - Thus, intervals `[l;i-1]` and `[i+1;r]` are now subproblems (might still hold `gcd=1`).
Check: https://codeforces.com/contest/1156/problem/E
Check: https://codeforces.com/gym/101623/problem/F

### Count good subarrays `(L, R1, R2)` inside query `[Lq;Rq]`
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

### Find minimal good interval containing query `[Lq;Rq]`, good intervals are decomposable

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

### CDQ
Divide and Conquer CDQ; que é na vdd D&C com um merge ordenando ponto e fazendo query/update on the fly; que é na vdd D&C offline;
.
Tuto: https://robert1003.github.io/2020/01/31/cdq-divide-and-conquer.html
.
O problema que ela resolve é, dada uma lista de pontos 3d, dizer, para cada ponto, quantos pontos esse domina.
A gnt diz que um ponto A domina outro ponto B sse todas coordenadas de A são maiores que (ou iguais) às de B.
.
A ideia p resolver esse problema modelo eh ordenar os pontos de modo que, se ponto A domina ponto B, index(A) < index(B).
Então, para cada merge com [l;m] e [m+1;r], vamos calcular a interferência dos pontos em [m+1;r] que dominam os pontos em [l;m].
A ordenação garante que não existe relação de dominância na ordem contrária.
.
Dado que temos os subconjuntos [l;m] e [m+1;r] e que a relação de dominância só acontece da dir pra esq, podemos pensar
nos pontos de [l;m] como updates e nos de [m+1;r] como queries (queremos saber quantos pontos da esq cada ponto da dir domina).
.
Esse subproblema parece com esse mesmo problema de dominância em 2D, que é meio manjado.
Pra resolver esse, ordenamos os pontos 2D pela primeira coordenada e usamos uma BIT na segunda coordenada.
A ordem garante que, se um ponto é dominado por mim, ele já foi processado e a BIT permite fazer query em todos valores menores que ou iguais a mim rapidamente.
Diferentemente, agora, os pontos que fazem queries vem de uma lista e os que fazem update de outra lista (no problema 2D original são a mesma lista).
E precisamos garantir que, antes de calcular uma query, todos os pontos de update que podem ser dominados pela query foram processados.
.
O processar dessas duas listas de forma ordenada nos da (de graça) uma nova lista ordenada. Ou seja, ordenados e processamos as queries e updates num mesmo passo.
Parece o MergeSort.
.
Essa técnica é legal, mas parece ser meio inútil pq podemos usar uma BIT2D comprimida. Ambas precisam ser usadas offline.
.
Essa técnica é legal pra problema com query/update em matriz porque usamos o tempo dos eventos (query ou update) como uma dimensão, o que garante o processamento de todos eventos relevantes e anteriores ao atual.
.
Q*log(Q)*log(dim)
