namespace color_updt{
  struct Interv{
    mutable int l, r, val;
    Interv(int _l=-1, int _r=-1, int _v=0):
    l(_l), r(_r), val(_v){}
    bool operator<(const Interv& x) const{ return l < x.l; }
    bool operator<(const int x) const { return r < x; }
  };

  set<Interv, less<>> s;
  int n;
  void init(int m){
    n = m;
    s.clear();
    // attention
    s.insert(Interv(1, n, 0));
  }

  int updt(int L, int R, int new_val){
    if(L > R) return -1;
    auto it_l = s.lower_bound(L);
    auto it_r = s.lower_bound(R);
    auto at_l = *it_l, at_r = *it_r;
    auto same = (it_l == it_r);

    if(same){
      s.erase(it_l);
      it_l = it_r = s.insert(Interv(L, R, at_l.val)).first;
    }else{
      s.erase(it_l); s.erase(it_r);
      it_l = s.insert(Interv(L, at_l.r, at_l.val)).first;
      it_r = s.insert(Interv(at_r.l, R, at_r.val)).first;
    }

    // attention
    int sum = 0;

    bool past_r = false;
    for(auto it = it_l; !past_r; it = s.erase(it)){
      auto [l, r, val] = *it;
      // attention
      sum += query_d(l, r, val, new_val);     
      sum %= MOD;

      if(it == it_r) past_r = true;
    }

    if(L - 1 >= at_l.l) s.insert(Interv(at_l.l, L - 1, at_l.val));
    if(R + 1 <= at_r.r) s.insert(Interv(R + 1, at_r.r, at_r.val));
    s.insert(Interv(L, R, new_val));
    
    // attention
    return sum;
  }
}
