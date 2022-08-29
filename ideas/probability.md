# Probability

#### Equiprobable subsets of same size on uniform distribution
Given a set of numbers from which we are sampling (with or without replacement), subsets with the same amount of different elements are all equally probable.
That is, given that we are interested in subsets of size `k` while sampling, the probability of accessing any of these is: `1 / Choose(n, k)`.

#### Expected number of trials until success
If probability of success is `p`, the expected number of trials until success is `1/p`.

#### Expected number of moves until final state
Let's say you have a process in which you keep updating a state and there is a set of final states you may reach. You wan't to know the expected number of moves until you reach a final state.  
  
Note that states can be seen as a graph and for each state there is a set of edges going out from it to other states. Cycles may be allowed.
There are several modellings for this since this is quite generic. One of such modellings is:
- Partition states such that for each partition you are able to compute:
  - Probability of a state in this partiton not being a final state
  - Expected number of moves for leaving this partition
  - Note: There can't be cycles between different partitions
  - We are then finding the answer not aiming a final state but counting the number of steps non-final states take until leaving the current partition
