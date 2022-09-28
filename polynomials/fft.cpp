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
