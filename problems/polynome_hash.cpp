// https://codeforces.com/group/XrhoJtxCjm/contest/422718/problem/J

#include<bits/stdc++.h>
using namespace std;

std::mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());

template <class LOW, class HIGH, const LOW mod>
struct modBase {
  using mint = modBase<LOW, HIGH, mod>;
  constexpr modBase() : val(0) {}
  // be careful of negative numbers!
  constexpr modBase(const LOW v) : val((v % mod + mod) % mod) {} 
  LOW val;

  #define add(a, b) a + b >= mod ? a + b - mod : a + b
  #define sub(a, b) a < b ? a + mod - b : a - b

  constexpr mint &operator += (const mint &o) { return val = add(val, o.val), *this; }
  constexpr mint &operator -= (const mint &o) { return val = sub(val, o.val), *this; }
  constexpr mint &operator *= (const mint &o) { return val = (LOW) ((HIGH) val * o.val % mod), *this; }
  constexpr mint &operator /= (const mint &o) { return *this *= o.inverse(); }

  constexpr mint operator + (const mint &b) const { return mint(*this) += b; }
  constexpr mint operator - (const mint &b) const { return mint(*this) -= b; }
  constexpr mint operator * (const mint &b) const { return mint(*this) *= b; }
  constexpr mint operator / (const mint &b) const { return mint(*this) /= b; }

  constexpr mint operator - () const { return mint() - mint(*this); }
  constexpr bool operator == (const mint &b) const { return val == b.val; }
  constexpr bool operator != (const mint &b) const { return val != b.val; }

  template<class E> constexpr mint pow (E e) const { return fexp(*this, e); }
  constexpr mint inverse() const { return pow(mod - 2); }
  constexpr LOW get() const { return val; }
  static constexpr LOW getMod() { return mod; }

  friend ostream& operator << (ostream &os, const mint &p) { return os << p.val; }
  friend istream& operator >> (istream &is, mint &p) { return is >> p.val; }
};

const int MOD = 1e9 + 7;
using mint = modBase<int, long long, MOD>;

const int DEG = 3;
const int MAXN = 100010;

#define ll long long

mint inv[MAXN], invfat[MAXN];
void precalc(){
  inv[1] = invfat[0] = invfat[1] = 1;
  for(int i = 2; i < MAXN; ++i){
    inv[i] = -(inv[MOD % i] * (MOD / i));
    invfat[i] = (invfat[i - 1] * inv[i]);
  }
}

class LagrangePoly {
public:
  LagrangePoly(vector<mint> _a) {
    //f(i) = _a[i]
    //interpola o vetor em um polinomio de grau y.size() - 1
    y = _a;
    den.resize(y.size());
    int n = (int) y.size();
    for(int i = 0; i < n; i++) {
      den[i] = invfat[n - i - 1] * invfat[i] ;
      if((n - i - 1) % 2 == 1) {
          den[i] = -den[i];
      }
    }
  }
  
  mint getVal(mint x) {
    int n = (int) y.size();
    if(x.get() < n) {
      return y[x.get()];
    }
    vector<mint> l, r;
    l.resize(n);
    l[0] = 1;
    for(int i = 1; i < n; i++) {
      l[i] = l[i - 1] * (x - (i - 1));
    }
    r.resize(n);
    r[n - 1] = 1;
    for(int i = n - 2; i >= 0; i--) {
      r[i] = r[i + 1] * (x - (i + 1));
    }
    mint ans = 0;
    for(int i = 0; i < n; i++) {
      mint coef = l[i] * r[i];
      ans += coef * y[i] * den[i];
    }
    return ans;
  }
    
private:
  vector<mint> y, den;
};

const int NUM_HASHES = 3;

struct PolyHasher{
  vector<mint> coef[NUM_HASHES];

  PolyHasher(int degree){
    for(int i = 0; i < NUM_HASHES; ++i){
      coef[i] = vector<mint>(degree + 1);
      
      for(int j = 0; j <= degree; ++j){
        uniform_int_distribution<int> dist(0, MOD - 1);
        coef[i][j] = dist(rng);
      }
    }
  }

  array<mint, NUM_HASHES> eval(mint x){
    array<mint, NUM_HASHES> out;
    for(int i = 0; i < NUM_HASHES; ++i){
      for(auto c : coef[i]) out[i] = out[i] * x + c;
    }
    return out;
  }   
};

PolyHasher hasher(DEG);

struct Node{
  array<mint, NUM_HASHES> hash;
  ll min_val, max_val;

  Node(){
    min_val = INT_MAX;
    max_val = INT_MIN;
    hash[0] = hash[1] = 0;
  }

  Node(int x){
    min_val = max_val = x;
    hash = hasher.eval(x);
  }

  Node operator+(Node x){
    Node ret;
    ret.min_val = min(min_val, x.min_val);
    ret.max_val = max(max_val, x.max_val);

    for(int i = 0; i < NUM_HASHES; ++i)
      ret.hash[i] = hash[i] + x.hash[i];

    return ret;
  }
};

namespace seg {
	Node seg[4*MAXN];
	int n;
  const Node NEUTRAL;

	Node build(int p=1, int l=0, int r=n-1) {
		if (l == r) return seg[p] = NEUTRAL;
		int m = (l+r)/2;
		return seg[p] = build(2*p, l, m) + build(2*p+1, m+1, r);
	}
	void init(int n2) {
		n = n2;
		build();
	}
	void prop(int p, int l, int r, Node x) {
		seg[p] = x;
	}
	Node query(int lq, int rq, int p=1, int l=0, int r=n-1) {
		if (lq <= l && r <= rq) return seg[p];
		if (rq < l || r < lq) return NEUTRAL;
		int m = (l+r)/2;
		return query(lq, rq, 2*p, l, m) + query(lq, rq, 2*p+1, m+1, r);
	}
	void update(int i, Node x, int p=1, int l=0, int r=n-1) {
		if(i <= l && r <= i){
			prop(p, l, r, x);
		}else if(i >= l && r >= i){
      int m = (l+r)/2;
      update(i, x, 2*p, l, m); update(i, x, 2*p+1, m+1, r);
      seg[p] = seg[2*p] +	seg[2*p+1];
    }
	}
};

int main(){
  precalc();

  int n, q; cin >> n >> q;
  seg::init(n);

  vector<int> v(n);
  for(int i = 0; i < n; ++i){
    int x; cin >> x;
    seg::update(i, Node(x));
    v[i] = x;
  }

  for(int i = 0; i < q; ++i){
    int t; cin >> t;
    if(t == 1){
      int x, y; cin >> x >> y; x--;
      seg::update(x, Node(y));
      v[x] = y;
    }else{
      int l, r; cin >> l >> r; l--; r--;
      auto node = seg::query(l, r);

      int range_size = r - l + 1;
      if(range_size < 3){
        cout << "YES\n"; continue;
      }

      // magic happens down here
      
      // we want to check whether what is inside [l;r] is a set
      // of numbers w/ a specific (poylnomial) format
      
      // since each set is uniquely (prob.) represented by the sum of
      // its elements hashes, we want to check wheter the hash sum inside [l;r]
      // follows the specific desired (polynomial) format
      // we check that using equality and lagrange interpolation

      // forget hashes for 1 second and think only of polynomials;
      // our set of interest follows:

      // step = (max - min) / (r - l + 1)
      // g(i) = f(min + step * i)
        // i-th element from our set is defined as this
      
      // note that the sum (g(0) + g(1) + ... + g(r - l)) defines uniquely
      // this set
      
      // since g is a polynome, a sum of a contiguos interval is also a polynome
      // thus, we dont need to iterate through (r - l + 1) value to compute it
      // it suffices to sample NEW_DEG+1 points and interpolate the unique polynome defining it

      // if this equals the hash sum in our segtree, the sets are (prob.) equal

      // what follows is task specific
      ll range = (node.max_val - node.min_val);
      if(range % (range_size - 1)){
        cout << "NO\n";
      }else{
        ll step = range / (range_size - 1);
        int NEW_DEG = DEG + 2;

        vector<mint> g_accu_pts[NUM_HASHES];
        array<mint, NUM_HASHES> g_accu = {0, 0, 0};

        for(int j = 0; j < NEW_DEG; ++j){
          ll x = node.min_val + j * step;
          array<mint, NUM_HASHES> g_j = hasher.eval(x);
          
          // NUM_HASHES
          for(int k = 0; k < NUM_HASHES; ++k){
            g_accu[k] += g_j[k];
            g_accu_pts[k].push_back(g_accu[k]);
          }
        }

        bool ok = true;
        for(int j = 0; j < NUM_HASHES; ++j){
          LagrangePoly lp(g_accu_pts[j]);
          // -1 pq eh 0 indexado  
          if(lp.getVal(range_size - 1) != node.hash[j]){
            ok = false;
            break;
          }
        }

        if(ok) cout << "YES\n"; else cout << "NO\n";
      }
    }
  }
}
