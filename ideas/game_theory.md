# Game theory

### Winning condition - Pile pointing to the same set of states
Our game state has the following structure:
- A single pile of stones where I can always take a positive number of stones from it
- From any number from this pile I can go to the same set `S` of states
  
We are in the state `X` w/ `x` stones in our pile  
- If `x >= 2`  
  - If there is a losing state in `S`, `X` sends to it (trivial)  
  - If there is not a losing state in `S`, remove all stones, setting `x := 0`. Since all in `S` is winning, `x=0` is losing  
- Else, I guess it depends on the problem  
  
Check: https://atcoder.jp/contests/arc137/tasks/arc137_c

### Last to play wins/unwanted positions
If the problem presents this variation, set the "about to win" positions as unwanted positions (really high grundy).  
Thus, states leading only to such positions will get a losing status.


### 01 Game - Atcoder
Check: https://atcoder.jp/contests/arc151/tasks/arc151_c  
  
Define:  
- `f_d(n):` grundy for hole of size `n` between **d**ifferent digits
- `f_e(n):` grundy for hole of size `n` between **e**qual digits
- `f_o(n):` grundy for hole of size `n` touching **o**ne digit
- `f_z(n):` grundy for hole of size `n` touching **z**ero gitis
  
Note that for all of these `f(0)` is undefined.
  
We can define these as recursive functions:
```
f_d(1) = 0; f_e(1) = 1; f_o(1) = 1; f_z(1) = 1;

f_d(n) = MEX(f_d(m) ^ f_e(n - m - 1); f_e(n - 1))
f_e(n) = MEX(f_d(m) ^ f_d(n - m - 1); f_d(n - 1))

f_o(n) = MEX(f_o(m) ^ f_e(n - m - 1); f_o(m) ^ f_d(n - m - 1); f_o(n - 1))
f_z(n) = MEX(f_o(m) ^ f_o(n - m - 1); f_o(n - 1))
```
  
First solve `f_d` and `f_e`:
- `f_e(n)` can always access `f_d(1)=0` and never access `f_e` `=>` `f_e(n) >= 1`
- `f_d(n)` can never acess `f_d` without `^ f_e`
- This leads to `f_d(n)=0` never reaches `0` in its mex
- and `f_e(n)=1` only reaches `0` in its mex
  
Now, for `f_o`:
- `f_o(n) = MEX(f_o(m < n - 1) ^ 1; f_o(m < n) ^ 0; f_o(n - 1))`
- This is the definition of mex of a nim pile
- `f_o(n) = n`
  
And `f_z`:
- `f_z(n) = MEX(m ^ n - m - 1; n - 1)`
- When can we reach `0`?   
  - When `f_o(m) ^ f_o(n - m - 1) = 0 <=>`
  - `f_o(m) = f_o(n - m - 1) <=>`
  - `m = n - m - 1 <=>`
  - `m = (n - 1) / 2 <=> n is odd`
- When can we reach `1`?  
  - `n - m - 1 = m <=>`
  - `(n - 2) / 2 = m <=>`
  - `n is even`
- We either reach `1` or `0`, depending on `n % 2`
- `f_z(n) = n % 2`
