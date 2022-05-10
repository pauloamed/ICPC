struct Node{
  struct Interv{
    int l, r;
    ll val;
    bool operator< (const Interv &x) const{
      return val < x.val; 
    }
  };

  Interv pref, suf, best;
  int l, r;
  ll val;

  Node(){}
  Node(int L, int R, ll v){
    if(v < 0){
      pref = best = {L, L, v};
      suf = {R, R, v};
    }else{
      pref = suf = best = {L, R, v};
    }
    l = L, r = R, val = v;
  }

  Node operator+(Node x){
    if(x.val == LONG_LONG_MIN) return *this;
    else if(val == LONG_LONG_MIN) return x;

    Node ret(l, x.r, val + x.val);

    ret.pref = max(pref, {l, x.pref.r, val + x.pref.val});
    ret.suf = max(x.suf, {suf.l, x.r, suf.val + x.val});

    Interv best_cand = {suf.l, x.pref.r, suf.val + x.pref.val};

    ret.best = max(best, x.best);
    ret.best = max(ret.best, best_cand);
    return ret;
  }
};
