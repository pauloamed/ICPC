
namespace pudpt{
  const int DEG_CNT = 3;
  const int DEG[DEG_CNT] = {0, 1, 2};
  int fastexp(int base, int expo){
    int ans = 1;
    while(expo > 0){
      if(expo & 1) ans = (ans * base) % MOD;
      expo >>= 1;
      base = (base * base) % MOD;
    }
    return ans;
  }
}

struct LazyNode{
  int FIXED_SUM[pudpt::DEG_CNT];
  int coefs[pudpt::DEG_CNT];
  LazyNode(){}
  // non-leaf
  LazyNode(const LazyNode &a, const LazyNode &b){
    for(int j = 0; j < pudpt::DEG_CNT; ++j)
      FIXED_SUM[j] = (a.FIXED_SUM[j] + b.FIXED_SUM[j]) % MOD;
    memset(coefs, 0, sizeof coefs);
  }
  // leaf
  LazyNode(int i){
    for(int j = 0; j < pudpt::DEG_CNT; ++j)
      FIXED_SUM[j] = pudpt::fastexp(i, pudpt::DEG[j]);
    memset(coefs, 0, sizeof coefs);
  }
  void merge(LazyNode &ln){
    for(int i = 0; i < pudpt::DEG_CNT; ++i)
      coefs[i] = (coefs[i] + ln.coefs[i]) % MOD;
  }
  int get_i(int i){ return (coefs[i] * FIXED_SUM[i]) % MOD; }
  void reset(){ memset(coefs, 0, sizeof coefs);}
};

struct Node{
  int x;
  Node(int y=0):x(y){}
  Node operator+(Node n){ return {(x + n.x) % MOD}; }
  void consume(LazyNode &ln){
    for(int i = 0; i < pudpt::DEG_CNT; ++i)
      x = (x + ln.get_i(i)) % MOD;
  }
};


LazyNode lazy[4*MAXN];

Node build(int p=1, int l=0, int r=n-1) {
  if (l == r){
    lazy[p] = LazyNode(l);
    return seg[p] = NEUTRAL;
  }
  int m = (l+r)/2;
  seg[p] = build(2*p, l, m) + build(2*p+1, m+1, r);
  lazy[p] = LazyNode(lazy[2*p], lazy[2*p+1]);
  return seg[p];
}

lazy[2*p].merge(lazy[p]), lazy[2*p+1].merge(lazy[p]);
lazy[p].merge(x);

LazyNode ln;
ln.coefs[0] = -(l * l % MOD) - (len * l % MOD) + l + len;
ln.coefs[1] = 2 * l + len - 1;
ln.coefs[2] = -1;
