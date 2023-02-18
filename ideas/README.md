# Ideas
Summary of some ~not so~ frequent ideas

```
Q is necessary for P (P => Q): If (P => Q), it is impossible P without Q.
P is sufficient for Q (P => Q)
P is sufficient and necessary for Q, (P => Q) and (Q => P)
```

## General - problems properties

### Operations and invariants
Mainly, there is a `f()` for the global state and operations guarantee decreasal in this state. 
We want to get to `f() = 0`.  
  
Check: https://open.kattis.com/problems/enemydivision  
Check: https://atcoder.jp/contests/arc136/tasks/arc136_c
 
### Make array `A` equal to `B`: change `a[j], j \in [l;r]` into `a[i]`, `i \n [l;r]`
Operation: Substitute each element inside a range `[l;r]` with an element (which element? depends on the problem dur) from this range.
Compressed values: elements in the order they appear, without duplicates: 1 1 2 4 2 2 5 5 3 => 1 2 4 2 5 3

A necessary (but not sufficient) condition is that (i.e. there is only a solution if) compressed values from `B` are a subsequence from `A`.  
The operation can only delete elements from the compressed values of `A`; no new element is created.
  
Moreover, depending on the operation, the range each value can occupy can be freely modified, turning the transformation feasible (sufficient).
  
Check: https://codeforces.com/gym/101964/problem/F

### Quadratic functions in linear models
**TODO** (https://codeforces.com/gym/102644/problem/G)
In linear contexts (linear recurrences, min cost max flow), the quadratic function `i^2` can be modelled as the sum of the `i` first odd numbers.

### Sum between linear functions and between line segments
The sum between linear functions is also a linear function.  
The sum between `N` line segments (summing their `y` values) leads to a function which can be decomposed into at most `2N` line segments.  

A line sweep can be done storing the ongoing accumulated slope and `y`. 
A line segment can be expressed as a slope, the starting `y` offset and the final `y` offset. 
Decompose a line segment into activation and deactivation points at their starting and ending times respectively.
Activating is adding the starting `y` offset to `y` and the slope to the accumulated slope at time `t_start`.  
Deactivating is removing the final `y` offset from `y` and the slope from the accumulated slope at time `t_end`.

When processing a point in the line sweep, update values as (assume that deactivations will have negative event values):
```
y = y + slope * (event_t - last_t) + event_y_offset
slope += event_slope
last_t = event_t
```
Miminals and maximals will occur only in activation and deactivation points.
  
Check: https://codeforces.com/gym/102433/problem/J

### Paths down-right on a grid while summing elements
Take a 2D grid and a path with sum `sum` going either down or right on it. `a_ij` of this grid has a value and passing through `(i,j)` adds it to `sum`. Note that each diagonal is visited exactly once in a path.  

From a path you can go to an adjacent path by replacing a cell on diagonal `D` to another cell in `D` adjacent to it. Note that the removed cell needs to be a corner cell; otherwise, the path disconnects. Also, with such operation you can visit all possible paths. 
  
What happens to `sum` when you switch paths? What happens to its parity? Is the range of possible `sum` values contiguos?
