# Geometry


### Convex Hull
Fun facts:
- Set of points s.t. there exists a half-plane for each point that doesnt contain any other point
- If coordinates are `[0;C]`, there are at most `O(C^(2/3))` points inside the convex hull
  - https://codeforces.com/blog/entry/62183

### Sum of `k` vectors "dominates" a query point
If `k=1`, is equivalent to checking if the query point is inside of the Chull of such vectors.  
   
If we are combining these vectors `k` times, we are actually summing (minkoviski sum) the Chull with itself `k` times. 
This is equivalent to multiplying each Chull coordinate by `k`.  
And, for checking if the point is inside, we can also just divide it by `k`, leaving the chull coordinates fixed.  
  
Check: https://open.kattis.com/problems/hiringhelp  

### Upper Hull and CHT
Every point in the CHT maximizes `(x,y=1)` and thus will compose the upper hull border.

### Try working the formulas instead of just using the geometry lib
For example, if you know that the points follow a formula and you are dealing the problem of checking if a line crosses these points, try working this on paper instead of jumping to the code. Use cross product and you may have now a number theory problem.

### Manhattan to Chebyshev distante
Chebyshev distance: `D(X,Y)=max(|X_i-Y_i|)`  
The Manhattan distance between points `X` and `Y` is "equivalent" to the maximum Chebyshev distances between points `X'` and `Y'`, where `P'` is a point in which each the `2^(d-1)` coordinates is the sum of coordinates of `P` while varying signals. Ex:
- `(x,y)` => `(x+y,x-y)` (`Xd=2`, `X'd=2`)
- `(x,y,z)` => `(x+y+z,x+y-z,x-y+z,x-y-z)` (`Xd=3`, `X'd=4`)

Note that the Manhattan distance between `A=(a,b)` and `B=(x,y)` equals `|a-x|+|b-y|`, which can be rewritten as `max(a-x,x-a) + max(b-y,y-b)`.
Instead of creating 2 choices for each coordinate, we can generate all combinations as:
- Manhatthan distance = `max((a-x)+(b-y), (a-x)+(y-b), (x-a)+(b-y), (x-a)+(y-b)) = max(a-x,x-a) + max(b-y,y-b)`
- If we reorder terms, keeping values from each point `A,B` together: `max((a+b)-(x+y), (a-b)-(x-y), (x-y)-(a-b), (x+y)-(a+b))`
- Further: `max(|(a+b)-(x+y)|, |(a-b)-(x-y)|)`
- Now, this is in the form of Chebischev, create `A'=(a+b,a-b)` and `B'=(x+y,x-y)`, the answer is `Chebyschev(A',B')=max(|A'_i, B'_i|)`
  - For each axis, coordinates have the same signal, but one will be switched when perfoming Chebischev's `|a_i-b_i|`, what agrees with Manhattan
  
Check: https://www.spoj.com/problems/DISTANCE/

### Place the largest non-overlapping polygon without touching other already placed
The optimal largest non-overlapping polygon will touch **at least two** that are already placed. If it touches less than two, it can be expanded.  
A special case is when figures are circles and lines. In this case, the places circle will touch at least three other figures (circle/line).
  
Check: https://codeforces.com/gym/101078/problem/E

### Getting through
Getting through a corridor where figures may block the passage if they intersect or touch each other.  
Can be solved using DSU for checking if parallel walls are connected, blocking the passage.  
  
The maximum circle that can go through without being blocked is bounded by one of the `n^2` distances.  
Testing if circle with radius `r` goes through: unite all pair of elements with distance `<= 2*r` in order to simulate a blockage.
Solve using binary search of simple brute force on all sorted distances.
  
Check: https://codeforces.com/gym/100625/problem/G

### Virtual images for reflection/bouncing
Some problems ask for you to reflect/bounce (angle in equals angle out) a line until it reaches a point or crosses some segments. 
For handling this complex operation, you can create virtual images of the original input. 
Now, a line that would be reflected can now just go through in these virtual images.  

For example, if we have a mirror in the bottom edge and a line is going at it, instead of reflecting, create a mirroed input at the bottom and just keep the line going in it.  
  
Every time a virtual image is created, it will be mirroed depending from which direction it is coming from. 
  
Check: https://codeforces.com/problemset/problem/241/C  
Check: https://codeforces.com/gym/101519/problem/F  

### Side of polygon
A polygon has every side smaller ~or equal~ to the sum of all other sides.

### 3 colinear points / Bad point between good points
For each (good) point `p`, do polar sort of all the points using `p` as center. If there are colinear points, they will be adjacent in this sorting (bad will be adjacent to good).

### Perimeter and area of convex polygons
- Given a fixed perimeter, approximating the polygon to a circle will maximize its area
- Given fixed edge lenghts, the area of a polygon determined by such edges will be maximized when inscribed on a circle
- Bretschneider's formula:
```
area_of_quadrilateral = sqrt((s-a)(s-b)(s-c)(s-d)-abcd*cos^2((â+ĉ)/2))
s: semiperimeter
â and ĉ: any opposite angles

- The quadrilateral can be both convex or concave, but it mustn't cross itself
- If `d=0`, this is a triangle (Heron's formula)
- A convex quadrilateral ABCD is cyclic iff its opposite angles are equal `180deg` => `cos(...) = 0` (Brahmagupta's formula)
```

### Helly's theorem (intersection between convex polygons)
Let `C` be a finite family of convex polygons in `R^n` such that, for `k ≤ n + 1`, any `k` members of `C` have a nonempty intersection. 
Then the intersection of all members of `C` is nonempty.
Eg.: In the plane (2d), if, for every triple (3) of convex polygons, there is a non-empty intersection, the intersention of all polygons is non-empty.

### Pick's theorem (area, integer points)
Let `P` be a polygon with integer coordinates for its vertices.
Let:
```
- A: Area of P
- i: #integer points inside the polygon
- b: #integer points in the polygon boundaries
Then, A = i + (b/2) - 1
```
### Range of points inside trapezoidal defined by segment `AB` and query point `Q`
![Ancient Towers. Thanks kobus!](assets/ancient_towers.png)

Note that we can decompose the range into two prefixes if we keep points polar sorted using `A` and `B` as pivots in lists `X` and `Y` respectively.
  
The desired points are `prefix_i(X) - prefix_j(Y)`, `i` and `j` can be found by querying `BÂQ` angle in `X` and `A^BQ` angle in `Y`.
  
This is a special case of the "contribution" techinique in which we decompose a complex update into simpler ones and solve the final result at the end of all updates.
  
Check: https://codeforces.com/gym/103640/problem/A  

### Minkoviski sum
Definition: `A ^ B = {a + b | a \in A, b \in B}`

Properties:
- `A ^ NULL = A`
- `A ^ {v} = {a + v | a \in A} (translating)`
- `A ^ {0} = A`
- `A ^ B = B ^ A`
- `(A ^ B) ^ C = A ^ (B ^ C)`
- `c(A ^ B) = cA ^ cB (scaling)`
- `A /\ B != NULL` iff `0` is inside `A-B`.
  - If `0` lies on a (non-deg) vertice of `A-B`, `A /\ B` is a point
  - If `0` lies on an edge of `A-B`, `A /\ B` is a segment
  - If `0` lies on inside `A-B`, `A /\ B` is a polygon
  - `0` is inside `A-B` iff exists `a \in A` and `b \in B` s.t. `a = b <=> a - b = 0`. Since the image of `a - b` equals `A-B`, `0 \in A-B`.
- `argmin_v((A + {v}) /\ B = NULL) = argmin_v(0 \not_in A-B+{v})`
  
Can be seen as the combination of convex sets represented by convex polygons.
Combination in the sense of the definiton (`x + y, x \in X, y \in Y`) 
   
Check: https://open.kattis.com/problems/joiningflows
  
### Subset of vectors w/ sum w/ maximal sqrt norm
Observe the answer vector `V`. Only vectors `u` with `angle(V,u) <= 90degs` were used to build `V`.
If we sort the list of input vectors by angle (polar sort), the answer will be a subsegment of the final list in which the distance between the first and last vector does not exceed `90degs`. There may be a border case if `angle == 90`.
  
Check: https://atcoder.jp/contests/abc139/tasks/abc139_f
  
## Analysis

### General observations
- Avoid using floating points (division, square root, trigonometric functions); try to use fractions
- Avoid doing too much comparisons w/ floating points
- Avoid using floating points with big magnitude. This implies a greater error.

#### Catastrophic cancelletion
Assume that the relative error is `10^-6`. 
Lets say we cancel out `A=10^6` and `B=10^6`, their erros are `10^0`. `A-B` is now `10^0` with error `10^0`.
We don't want this to happen.

### Convex/Concave function
- A function is convex iff its derivative is monotonic non-decreasing. It has one minimal=minimum point.
- A function is concave iff its derivative is monotinic non-increasing. It has one maximal=maximum point.
- You can ternary search a convex/concave function  
- The linear combination (weigthed pointwise sum) of convex/concave functions is convex/concave
- Pointwise Max/Min of convex/concave functions is also convex/concave
- Linear functions are both convex and concave
- `f(x)=|A-x|` is convex
- Convolution (+, Max) between concave functions is also concave (Mikoviski sum on upper hull)
  - `c_k = Max_i+j=k(a_i + b_j)`   
- Intersection between `f(x)` and a translation `f(x + d) + k` is at most 1 point
  - `f(x) = f(x + d) + k` iff  `f(x) - f(x + d) - k = 0`
  - There can only be more than 1 point if there is a `x^2` factor; but this will be cancelled
  
Check: https://codeforces.com/gym/104128/problem/H
Check: https://www.thehuxley.com/problem/615

#### Abstracting parameters can help
For example, finding the maximum segment sum on an array where we can do `a_i - x` for all `i` is described as:
```
max_x max_(i<j) sum_i_j a_i - x
```
But we can note that `max_(i<j) sum_i_j a_i - x` is a function decreasing on `x`. 
Abstracting `i` and `j` as inputs and only think of `f(x)`, that outputs this maximum value.  
We can now think of `f(x)` as a non-decreasing function, not analyzing the behaviour of variables `i` and `j`.
  
Check: https://codeforces.com/contest/1355/problem/E

### Absolute error and squared euclidean minimization
If in 1D, the median of `A`s minimizes the sum of `|x - A|` errors.
Also, the mean minimizes the sum of **squared** euclidian distances (`||x - A||^2`).

### Convex closures
(http://www.cs.cmu.edu/afs/cs/academic/class/15456-s10/ClassNotes/lecture2.pdf)  
A convex combination of a set of points is a linear combination that is both non-negative and affine i.e. a weighted sum of such points s.t. their coefficients sum up to 1 and all are >= 0.
- The convex closure of a point is the point itself. 
- The convex closure of two points is the line segment between them. 
- The convex closure of a set of points in the plane is a convex polygon.
With this, we know that a point is inside a polygon iff it can be represented as a convex combination of some of its vectors (which can be the polygon's vertixes).
Also, a polygon can be seen as an infinite set of vectors.

Given a convex set, a point `P` is in its convex hull border iff there is a vector `(x,y)` s.t. `scalar(P, (x,y))` is maximum. If there is an edge point `eP` with `scalar(eP, (x,y)) = X`, there is also a vertice `vP` s.t. `scalar(vP, (x,y)) = X`.

# Slope tricks

## Keeping difference array (increasing seq. if convex)

#### Treaps for convoluting (Mink sum) upper hulls in `O(logN^2)`
Let's say that two arrays `A`, `B` are each an upper hull. 
We can compute their Minkoviski sum in `O(logN^2)` if using treaps.  
  
Note that upper hulls are concave, which present non-ascending derivative.  
We can use `A': a'_i = a_i - a_i-1` and `B'` here.  
Merging `A'` and `B'`, using Minkoviski Sum algorithms, reduces to merging 2 sorted lists (derivatives are edges, here sorted in both non-ascending). 
Using treaps (`A'` and `B'` stored as treaps), this can be done in `O(logN^2)`.
  
Check: https://codeforces.com/gym/104128/problem/H  
  
#### Priority queue for `f(x) = max(f(x), f(x+1) + w)`
Using the problem as context `f(x):` best profit when holding `x` stocks
  
There are `n` steps as follows:  
- 1: Buy a stock for price `w`: `f(x) = f(x - 1) - w`
- 2: Maybe sell stock for price `w`: `f(x) = max(f(x), f(x + 1) + w)`
- 3: 2 again
  
If we think of the arrays of differences:  
- 1: changes nothing, since all elements change by the same amount  
- 2: there is only one intersection between `f(x)` and `f(x + 1) + w`  
  - When `f(x)` overtakes `f(x+1)+w`, it is the first `x` s.t. `f(x)>f(x+1)+w`   
  - There element before it was thus `f(x)+w` and now we know we have `f(x)`  
  - This leads to adding a `w` difference to our difference list  
  - Since it's concave, keep it sorted (keep a PQ)  
  - When applying `f(x)=f(x-1);f(x)=f(x+1);f(x)=f(x+1)`, we create a negative entry for `f()`. This is not allowed, pop the first difference (first entry)  
Check: https://codeforces.com/contest/866/problem/D

#### Asc and Desc deques while lazy evaluating `f`
```
OPERATIONS:
shifting f(x) = f(x +- delta) in O(delta)
f(x) = min(f(x), f(x - 1) + A) in O(1) (invariant, not op)
f(x) = min(f(x), f(x + 1) + B) in O(1) (invariant, not op)
adding |x| to f(x)
```
  
Check: http://www.usaco.org/index.php?page=viewproblem2&cpid=650  
  
## Keeping step function in best increasing subseq

Check: https://oj.uz/problem/view/CEOI19_magictree

## Keeping piecewise-linear convex function

#### Building non-desc sequence
A recurrent problem is, given an array,
build a non-desc sequence w/ min num of ops where
the op is adding or subtracting 1 to any element over cost of 1.
  
This is solved by using two functions in each `i`: `f_i(x)` and `g_i(x)`:
- `f_i(x):` min cost of solving sequence until `i` and turning `i`-th element equal to `x`
- `g_i(x):` min cost that `i+1` element would deal if equal to `x`
- `f_i(x) = g_(i-1)(x) + |A_i - x|` (**SUM OP**)
- `g_i(x) = min_y<=x f_i(y)` (**MIN PREF OP**)
  
##### `a_(i + 1) - a_i >= d` constraint
Some problems modify this constraint a bit by setting `a_(i + 1) - a_i >= d` (eg. `d=1` iff increasing sequence)
  
For this, we build a sequence `a'` where:
- `a'_i = a_i - d * i`
- `a_(i + 1) - a_i >= d` IFF `a'_(i + 1) - a'_i >= 0` (solvable non-desc constraint) 
- adding 1 in `a'` is also adding 1 in `a` (ops have the same cost)
  
Check: https://codeforces.com/contest/713/problem/C  
Check: https://codeforces.com/gym/102576/problem/C  
Check: https://www.codechef.com/problems/CCDSAP  

##### For all `i`, `a_i >= 0`
It may also be that `a_i >= k` for all `i`. In order to solve this, watch out for the **MIN PREF OP**.  
It must be that for any `k' < k`, `f(k') = k`. This comes as a problem when the starting slope `a` is positive (`a > 0`).  
  
When `a > 0` and **MIN PREF OP** is executed, we don't want `g(x)=-inf`, but rather `g(x)=f(0)` (`a=0`,`b=f(0)`).
  
Check: https://oj.uz/problem/view/LMIO19_bulves    
Check: https://www.codechef.com/problems/CCDSAP  
  
**`a_i >= k`:** Just define `a'_i = a_i - k`  
  
##### `a_n = x`
Instead of taking the `f_n(x)` where it is min, we may want to get `x=a_n`.  
For this, don't take `f_n(x)` when slope is `0`, but keep walking until a turning point `x>a_n` is reached.
The value `f_n(a_n)` can be evaluated using the stored `a` and `b`.
  
Check: https://oj.uz/problem/view/LMIO19_bulves

#### Further operations: `g_i(x) = min_y f_i(y)` where `y \in [x - da; x + db]`
Since we are convex, analyze the curve before minimum and the curve after:
- before: every `x` will look at `[x;x+db]` and take the minimum from there  
  - this will make all this descending curve to be shifted `db` points to the left
- after: every `x` will look at `[x-da;x]` and take the minimum from there
  - this will make all this ascending curve to be shifted `da` points to the right
- minimum will be extended `da` to left and `db` to right  
  
Keep a priority queue with lazy update in order to solve this.

