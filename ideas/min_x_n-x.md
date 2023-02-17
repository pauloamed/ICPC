### `min(x, n - x)`
You are given a list of elements that have a linear order and that compose a recursive structure (eg. list of tree elements in inorder).
You want to divide and conquer these elements. However, splitting them into the recursive calls isn't trivial.
We can apply `min(x,n-x)` if there is a search algorithm that traverses these elements following the given order for finding a delimiter and thus splitting.
Instead of searching in only one direction with 1 pointer in `O(x), x <= n`, we will use 2 pointers w/ opposite direction, one starting at the beggining and the other at the end (we will traverse these elements following the given order and its reverse). 
Now, the cost of this search is `O(min(x,n-x))`.

Note that:
- We will split the elements of the current call (`all`) into 2 sets: `small` and `large`. 
  - `small`: elements visited in the direction in which the delimiter was found (`all` >= 2*`small`)
  - `large`: the remaining. 
  - `all` will be splitted into these two disjoint sets for the child calls. 
- For each call, we don't traverse more than `O(|small|)` elements.
- An element is at most at `O(logN)` `small` sets: from bottom to top, these sets have their size at least doubled (union-by-size); their sizes don't exceed `N`.
- For each `small` element in a call, we execute a `O(C)` operation (eg. adding to a set, sorting).
- The final cost is bounded by the sum of `small` sets along the divide and conquer
Thus, the final cost is:
```
N: number of elements
log(N): max. number of small sets an element is
C: cost of operation per element inside a small set
= N*log(N)*C
```

In some problems, both original and reverse order can be expressed inside the same list that will be traversed in forward in backward directions.
However, in some less trivials problems, one list for each direction (original and reverse order) need to be build.
For such cases, we will still traverse in both direciton simultaneously, but we need to know which elements will be passed for the child calls, since a simple suffix/preffix split won't work.
What can be done is:
1. Create new lists for the `small` elements, sort if necessary (`C=log(N)`).
2. Solve for the `small` set
3. Delete the `small` set elements from `all`. Can be done with lazy deleting.
4. Solve `large`. Use `all` as `large`, orders are preserved after deleting in (3).
