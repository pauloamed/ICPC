struct LazyNode{
  ll start, step;
  LazyNode():start(0),step(0){}
  ll get_sum(ll n){
    ll pa = (n * (n - 1)) / 2;
    return n * start + pa * step;
  }

  void merge(LazyNode &ln, int sz_at_left=0){
    // called in `update` and `lazy_prop`
    // in both cases, when updting right tree, 
    // start needs to add steps from right subtree

    start += ln.start + ln.step * sz_at_left;
    step += ln.step;
  }

  void reset(){ start = step = 0; }
};
