#define MAXN 200010
#define MOD 1000000009
#define P 153
#define INVP 228758172

struct Hash{
    vector<int> hashes, pPref, invPPref;

    int m, p, invP;

    Hash(int prime, int mod, int invPrime){
        int p = prime;
        int m = mod;
        int invP = invPrime;
    }

    void hashAndPrep(string s){
        int n = s.size();

        pPref.push_back(1);
        invPPref.push_back(1);
        for(int i = 0; i < n - 1; i++){
            pPref.push_back((pPref.back() * (long long) p) % m);
            invPPref.push_back((invPPref.back() * (long long) invP) % m);
        }

        for(int i = 0; i < n; i++){
            hashes.push_back(((s[i]) * (long long) pPref[i]) % m);
            if(i) hashes[i] = (hashes[i] + (long long) hashes[i - 1]) % m;
        }
    }

    int getIntervHash(int l, int r) const{
        int hashA, hashB = 0, x;

        hashA = hashes[r];
        if(l) hashB = hashes[l - 1];

        x = ((hashA - hashB) + mod) % mod;

        return ((long long) x * invPPref[l]) % mod;
    }

    int getHash(string s) const{
        int n = s.size();
        int h = 0;
        int cp = 1;

        for(int i = 0; i < n; i++){
            int hh = ((s[i]) * (long long) cp) % m;
            h = (h + (long long) hh) % m;
            cp = (cp * (long long )p) % m;
        }
    }
};

vector<int> search(string p, string s){
    vector<int> occs;

    Hash hasher(P, MOD, INVP);
    auto ph = hasher.getHash(p);

    hasher.hashAndPrep(s);
    for(int i = 0; i <= s.size() - p.size(); ++i){
        auto sh = hasher.getIntervHash(i, i + p.size() - 1);
        if(sh == ph) occs.push_back(i);
    }

    return occs;
}
