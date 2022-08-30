namespace NTT{
  typedef long long ll;
  typedef complex<double> C;
 
  void fft(vector<C>& a) {
    int n = a.size(), L = 31 - __builtin_clz(n);
    static vector<complex<long double>> R(2, 1);
    static vector<C> rt(2, 1);  // (^ 10% faster if double)
    for (static int k = 2; k < n; k *= 2) {
      R.resize(n); rt.resize(n);
      auto x = polar(1.0L, acos(-1.0L) / k);
      for(int i=k;i<2*k;i++) rt[i] = R[i] = i&1 ? R[i/2] * x : R[i/2];
    }
    vector<int> rev(n);
    for(int i=0;i<n;i++) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    for(int i=0;i<n;i++) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k *= 2)
      for (int i = 0; i < n; i += 2 * k) for(int j=0;j<k;j++) {
        // C z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  /// include-line
        auto x = (double *)&rt[j+k], y = (double *)&a[i+j+k];        /// exclude-line
        C z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);           /// exclude-line
        a[i + j + k] = a[i + j] - z;
        a[i + j] += z;
      }
  }
 
  template<int M> 
  vector<ll> convMod(const vector<ll> &a, const vector<ll> &b) {
    if (a.empty() || b.empty()) return {};
    vector<ll> res(((int) a.size() + b.size()) - 1);
    int B=32-__builtin_clz(res.size()), n=1<<B, cut=int(sqrt(M));
    vector<C> L(n), R(n), outs(n), outl(n);
    for(int i=0;i<a.size();i++) L[i] = C((int)a[i] / cut, (int)a[i] % cut);
    for(int i=0;i<b.size();i++) R[i] = C((int)b[i] / cut, (int)b[i] % cut);
    fft(L), fft(R);
    for(int i=0;i<n;i++){
      int j = -i & (n - 1);
      outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
      outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / 1i;
    }
    fft(outl), fft(outs);
    for(int i=0;i<res.size();i++){
      ll av = (ll)(real(outl[i])+.5), cv = (ll)(imag(outs[i])+.5);
      ll bv = (ll)(imag(outl[i])+.5) + (ll)(real(outs[i])+.5);
      res[i] = ((av % M * cut + bv) % M * cut + cv) % M;
    }
    return res;
  }
}

namespace FFT{
  typedef long long ll;
  const long double PI = acos(-1);
  typedef complex<long double> doublex;
  
  void FFT(vector<doublex> &a, bool inverse) {
    int n = a.size();
    assert(n == (n & -n));
    
    vector<int> rev(n);
    for (int i = 1; i < n; i++) {
      rev[i] = (rev[i>>1]>>1) | (i&1 ? n>>1 : 0);
      if (rev[i] < i) swap(a[i], a[rev[i]]);
    }

    for (int m = 2; m <= n; m <<= 1) {
      long double theta = (inverse ? -1 : 1) * 2 * PI / m;
      doublex unity_root(cos(theta), sin(theta));

      for (int k = 0; k < n; k += m) {
        doublex omega = 1;
        for (int j = 0; j < m/2; j++) {
          doublex t = a[k + j + m/2] * omega;
          doublex u = a[k + j];
          a[k + j] = u + t;
          a[k + j + m/2] = u - t;
          omega *= unity_root;
        }
      }
    }
    for (int j = 0; inverse && j < n; j++) a[j] /= n;
  }
  
  vector<ll> conv(vector<ll> &a, vector<ll> &b) {
    vector<doublex> ca(a.begin(), a.end()), cb(b.begin(), b.end());
    int n;
    for (n = 1; n < a.size() + b.size(); n <<= 1);
    ca.resize(n); cb.resize(n);

    FFT(ca, false);
    FFT(cb, false);
    for (int i = 0; i < n; i++) ca[i] *= cb[i];
    FFT(ca, true);

    vector<ll> ret(n);
    for(int i = 0; i < n; i++) ret[i] = round(ca[i].real());
    return ret;
  }
}


// DIVIDE AND CONQUER
{
  vector<vector<ll>> pols;
  // pols[i]: polynomial from computing transition at state i 

  while(pols.size() >= 2){
    vector<vector<ll>> nxt;
    for(int i = 0; i + 1 < pols.size(); i += 2){
      nxt.push_back(convMod<MOD>(pols[i], pols[i + 1]));
    }
    if(pols.size() % 2) nxt.push_back(pols.back());
    swap(nxt, pols);
  }
}
