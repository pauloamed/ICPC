# Probability

#### Equiprobable subsets of same size on uniform distribution
Given a set of numbers from which we are sampling (with or without replacement), subsets with the same amount of different elements are all equally probable.
That is, given that we are interested in subsets of size `k` while sampling, the probability of accessing any of these is: `1 / Choose(n, k)`.

#### Expected number of trials until success
If probability of success is `P`, the expected number of independent trials until success is `1/P`.

#### Expected number of moves until final state
Let's say you have a process in which you keep updating a state and there is a set of final states you may reach. You wan't to know the expected number of moves until you reach a final state.  
  
Note that states can be seen as a graph and for each state there is a set of edges going out from it to other states. Cycles may be allowed.
There are several modellings for this since this is quite generic. One of such modellings is:
- Partition states such that for each partition you are able to compute:
  - Probability of a state in this partiton not being a final state
  - Expected number of moves for leaving this partition
  - Note: There can't be cycles between different partitions
  - We are then finding the answer not aiming a final state but counting the number of steps non-final states take until leaving the current partition

Check: https://atcoder.jp/contests/abc242/tasks/abc242_h

# Randomized

Mainly from Randomized algorithms lectures from Errichto.  

There are some problems that ask you to find **the biggest** set with `O(n)` of elements. The sample **is built** with such constraint. You will need to do a trial and error approach. For example:
- Given `N` points, find the line that crosses more points. It is guaranteed that such line crosses at least `N/K` points.
  - Probability of choosing a pair of points in such line is `1/K^2`. Probability of not being in this line is `(K^2-1)/K^2`, that, when repeated a lot of times (`^big`), gets really small.
- Given `N` elements, find the greatest `x` s.t. `x` divides at least `N/K` elements.
  - Probability of a random element being divided by `x`: `1/K`. Choose a random position, find all its divisors, update the answer if it divides at least `N/K` elements. Probability of not choosing is `(K-1)/K` which repeated a lot of times gets small.

Others still ask for a set, but don't rely on a given constraint:
- Given a DAG with `N` vertices and `M` edges, find a binary configuration of the vertices s.t. there are at least `M/4` nice edges w/ format `(1->0)` (1 vertex pointing to a 0 vertex).
  - If we randomly choose a configuration for each vertex, the probabilty of an edge being `(1->0)` is `1/2*1/2=1/4`. Thus, the expected value of its count as a nice edge is `1/4`. 
  - By linearity of expectation, sum all edges and you get `M/4`. 
  - Check: https://codeforces.com/gym/101964/problem/H
  - This probably can be extended to more classes and different relations between theses classes.
  - The probability of a random configuration not satisfying is the probability of a random variable having value smallest then its mean (expected value)
- Similar to the above, but on undirected graph and interested in `(a,b), a^b=1`
  - Check: https://onlinejudge.org/external/109/10982.pdf

### Birthday paradox - colisions

```
n: number of classes
k: number of independent trials, each has 1 class as outcome

probability that there is a colision: P(A)
probability that there is NOT a colision: P(B) = 1 - P(A)

not having a colision: probability of trials being an ordered permutation w/ different elements

number of ordered perms w/ dif els: n! / (n-k)!
number of all possible outcomes: n^k

P(B) = (n!/(n-k)!) / n^k = n! / (n^k * (n-k)!)
P(A) = 1 - n! / (n^k * (n-k)!)
```

##### Expected number of trials until colision
A colision is a pair of trials `x,y` s.t. `class(x) = class(y)`.
  
The expected number of colisions from a sample of size 2 is `1/n` (per birthday paradox).  
  
In order to having the expected number of colisions equals to `1`, we have to see `n` samples of size 2 i.e. `n` pairs of trials.
Since the number of pairs is quadratic in the number of elements, the number of elements needed to be seen is `sqrt(n)`.
  
Note that this isnt the probability of a colision, which can be computed using the birthday paradox.

##### Hashing
Hashing is just a random assignment of an element to a class. Thus colisions need to be avoided and the probability of a colision can be computed using the birthday paradox. Here, the biggest the size of the sample, highest is the probability of colision.
  
Comparing if two subarrays have the same hash implies a sample of size 2.
  
Comparing if a set of `N` strings are all different implies a sample of size `N`. Thus, bigger is the probability of colision.

### Guessing sequence
Random shuffle the choices before each trial.

### Maximum in random sequence - Blogewoosh 6
Given `n` numbers in a random order, the expected times that the maximum seen value changes is `O(log(n))` while processing such numbers.
  
Proof:
- Expected position of the maximum is in the middle of the sequence. Now look at the element that was maximum before it. It happens in the first half and its expected position is in the middle of this preffix... There are `O(log(n))` such prefixes and maximums.
- Probability of a new element being the maximum of its prefix is `1/i`, `i:` prefix size. Sum these up as expected values and you get `O(ln(n))`.