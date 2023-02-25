struct SlidingWindowPQ{
  // adding elements w/ increasing expiration date
    // if a is added after b, a expires after b
  // expiration is determined by update(l, r)
    // if (l,r) walks right, we are adding elements from left to right
    // if (l,r) walks left, we are adding elements from right to left
  
  // new elements enter at the back, and can expire olders w/ smaller values
  // query at the front

  deque<pair<int,int>> d;
  
  void update(int l, int r) {
    while(d.size()) {
      if(d.front().second < l) d.pop_front();
      else if(d.front().second > r) d.pop_front();
      else break;
    }
  }

  pair<int,int> top() {
    assert(d.size());
    return d.front();
  }

  void clear(){ d.clear(); }
  int size() { return d.size(); }

  void push(pair<int,int> x) {
    while(d.size()) {
      if(d.back().first > x.first) d.pop_back();
      else break;
    }
    d.push_back(x);
  }
};
