// extracted from https://codeforces.com/blog/entry/12145?#comment-168098
struct SingleHash {
    vector<int> suf, b;
    int mod;

    SingleHash(string s, int base = 153, int _mod = 1000000009) {
        int n = s.length();
        suf.assign(n + 1, 0); // suf[n] = 0
        b.assign(n + 1, 0);
        b[0] = 1;
        b[1] = base;
        mod = _mod;
        for (int i = n - 1; i >= 0; --i) {
            suf[i] = (s[i] + (ll)suf[i + 1] * b[1]) % mod;
        }
        for (int i = 2; i <= n; ++i) {
            b[i] = (ll)b[i - 1] * b[1] % mod;
        }
    }

    int substr(int l, int r) const { // [l, r]
        ll v = suf[l] - (ll)suf[r + 1] * b[r - l + 1];
        v %= mod;
        v += mod;
        v %= mod;
        return v;
    }
};
