// 100783C

#include <bits/stdc++.h>
#define rep(i, a, b) for(int i = (a); i < (b); i++)
using namespace std;

typedef complex<long double> cld;
typedef vector<int> vi;
typedef long long ll;
typedef long double ld;

void FFT(vector<cld > &a, bool invert){
	int n = (int)a.size();
	for (int i = 1, j = 0; i < n; i++) {
		int bit = n >> 1;
		for (; j >= bit; bit >>= 1)
			j -= bit;
		j += bit;
		if (i < j) swap(a[i], a[j]);
	}
	for (int len = 2; len <= n; len <<= 1) {
		ld ang = 2 * acos((ld)-1) / len * (invert? -1: 1);
		cld wlen(cos(ang), sin(ang));
		for (int i = 0; i < n; i += len) {
			cld w(1);
			for (int j = 0; j < len / 2; j++) {
				cld u = a[i + j], v = a[i + j + len / 2] * w;
				a[i + j] = u + v;
				a[i + j + len / 2] = u - v;
				w *= wlen;
			}
		}
	}
	if (invert)
		rep(i,0,n) a[i] /= n;
}

void Multiply(const vi &a, const vi &b, vector<ll> &res){
	vector<cld> fa(a.begin(), a.end()), fb(b.begin(), b.end());
	int n = 1;
	while(n < (int)a.size() || n < (int)b.size()) n <<= 1;
	n <<= 1;
	fa.resize(n); fb.resize(n);
	FFT(fa, false); FFT(fb, false);
	rep(i,0,n) fa[i] *= fb[i];
	FFT(fa, true);
	res.resize(n);
	rep(i,0,n)
		res[i] = (ll)(fa[i].real() + 0.5);
}

int main(){
  ios_base::sync_with_stdio(false); cin.tie(NULL);

  int n, m; cin >> n;
  vi v(200000, 0);
  vector<ll> ans;
  rep(i, 0, n){
    int x; cin >> x; v[x] = 1;
  }
  Multiply(v, v, ans);

  cin >> m;
  int resp = 0;
  rep(i, 0, m){
    int x; cin >> x;
    if(v[x] > 0 || ans[x] > 0) resp++;
  }
  cout << resp << endl;
}
