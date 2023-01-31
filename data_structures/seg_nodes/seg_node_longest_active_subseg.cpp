struct Value{
  struct Interv{
    int l, r;
    Interv():l(-1), r(-1){}
    Interv(int _l, int _r):l(_l), r(_r){}
    bool operator< (const Interv x) const{
      return r - l < x.r - x.l; 
    }
    bool operator== (const Interv x) const{
      return (l == x.l) && (r == x.r);
    }
  };

  Interv pref, suf, best;
  
  Value(){}
  Value(int i){
    pref = suf = best = Interv(i, i);
  }

  void print(){
    cout << pref.l << " " << pref.r << ", ";
    cout << suf.l << " " << suf.r << ", ";
    cout << best.l << " " << best.r << "\n";
  }

  Value operator+(Value x){
    if(best.l == -1) return x;
    if(x.best.l == -1) return *this;


    Value ret;
    ret.pref = pref, ret.suf = x.suf;
    ret.best = max(best, x.best);

    if(suf.r == x.pref.l - 1){
      ret.best = max(ret.best, Interv(suf.l, x.pref.r));
      if(x.pref == x.suf) ret.suf = Interv(suf.l, x.suf.r);
      if(pref == suf) ret.pref = Interv(pref.l, x.pref.r);
    }

    ret.best = max(ret.best, ret.suf);
    ret.best = max(ret.best, ret.pref);

    return ret;
  }
};
