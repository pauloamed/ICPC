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
