#include<bits/stdc++.h>
using namespace std;

#define MAXN 400020
#define K 19

#define int long long

namespace SA{
  // suffix id is position where it starts
  // id(s[i...]) = i

  // r is indexed using suffix id
  // p is indexed using suffix order id
  vector<int> r; // r[i]: equiv class of suffix s[i...]
  vector<int> p; // p[i]: suffix s[j...] is in index i in order
  int h; // step in suffix array construction (in 2^i form)
  int n; // strings size

  vector<vector<int>> st;
  vector<int> lcp; // lcp[i]: lcp between i-th and (i+1)-th ordered suffix
  vector<int> vlog;
  string s;


  void sort_suffixes(){
    for(int j = 1; j >= 0; --j){ // h*j: (0, h), used for retriving suffixes halves
      vector<int> cnt(n); // counting vector for counting sort
      for(int i = 0; i < n; ++i) cnt[r[(i+(h*j))%n]]++;
      vector<int> pos(n); // positon where each bucket starts
      for(int i = 1; i < n; ++i) pos[i] = pos[i - 1] + cnt[i - 1];

      vector<int> tmp(n); // tmp vector for keeping new p order
      for(int i = 0; i < n; ++i){
        int eqivClass = r[(p[i]+(h*j))%n]; // eqiv class for respective half
        tmp[pos[eqivClass]++] = p[i]; // defining new order
      }
      p = tmp;
    }
  }



  // function for suffix array construction
  // tot cost: n log(n)
  void prepare(const string &t){
    s = t;
    s.push_back(0); n = s.size();
    vector<int> aux; // temp for keeping new values for r
    aux = p = r = vector<int>(n);

    string u = s;
    sort(u.begin(), u.end());
    map<int,int> m;
    for(auto c : u){
      if(m.count(c)) continue;
      m[c] = m.size();
    }

    for(int i = 0; i < n; ++i){
      // init s[i...] in index i
      p[i] = i; r[i] = m[s[i]];
    }

    for(h = 1;; h <<= 1){ // log steps
      // sort_suffixes(); // sorting for step h
      sort_suffixes();

      // computing new equiv. classes
      // if two consecutives substrs in the new order
      // compare diff., it is a new equiv. class
      aux[p[0]] = 0;
      for(int i = 1; i < n; ++i){
        int diff = (r[p[i-1]] < r[p[i]]);
        diff |= (r[p[i-1]] == r[p[i]] && r[(p[i-1]+h)%n] < r[(p[i]+h)%n]);
        aux[p[i]] = aux[p[i-1]] + diff;
      }
      swap(aux, r); // setting new vals of r

      // if there are already n equiv. classes
      if(r[p[n-1]] == n-1) break;
    }
  }

  // finds t. O(|t|*log(n))
  int queryStr(string t){
    if(t.size() > s.size()) return 0;
    else if(t.size() == s.size()) return (t==s? 1 : 0);
    int bigPot = 1; while(bigPot < n) bigPot *= 2;
    int top = 0, bottom = n - 1; // delimiters of current search. indexes of S.A
    int currPos = 0; // current position in t
    for(;currPos < t.size(); currPos++){
      if(s[p[top]+currPos] < t[currPos]){
        // trying to find last substr in SA[top...bottom] such that
        // its char at suffix[currPos] is less than t[currPos]
        int pot = bigPot;
        while(pot){
          int newTop = top + pot;
          if(newTop <= bottom){
             if(p[newTop]+currPos < n){
                if(s[p[newTop]+currPos] < t[currPos]) top = newTop;
             }else top = newTop;
          }
          pot /= 2;
        }
        top++;
        // cerr << top << " " << p[top] << " " << s[p[top]+currPos] << " " << t[currPos]<< endl;
      }
      if(top > min(n-1, bottom) || p[top]+currPos >= n || s[p[top]+currPos] != t[currPos]) return 0;
      int pot = bigPot;
      int newBottom = top;
      while(pot){
        int maybeNewBottom = newBottom + pot;
        if(maybeNewBottom <= bottom){
          if(p[maybeNewBottom]+currPos < n){
            if(s[p[maybeNewBottom]+currPos] == t[currPos])
              newBottom = maybeNewBottom;
          }
        }
        pot /= 2;
      }
      bottom = newBottom;
      // cerr << top << " " << bottom << endl;
    }
    // return p[top];
    return bottom - top + 1;
  }

  // function for calc lcp function
  void prepare_lcp() {
    lcp = vector<int>(n, 0);
    int k = 0;
    for (int i = 0; i < n; i++){
      if (r[i] == n - 1){ // substr on last pos
        lcp[r[i]] = k = 0;
      }else{
        // r[i]: index of suffix s[i...] in order
        // r[i] + 1: id of consecutive suffix after s[i...]
        // p[r[i] + 1]: suffix id of consecutive suffix
        int j = p[r[i] + 1];

        // keep moving k forward
        while(max(i, j) + k < n && s[i+k] == s[j+k])
          k++;

        lcp[r[i]] = k; // setting r[i]'s lcp
        if(k) k--;
      }
    }
  }

  void precalc_st(){
    for(int i = 0; i < MAXN; ++i){
      if(i<=1) vlog.push_back(0);
      else vlog.push_back(vlog[i/2] + 1);
    }

    st = vector<vector<int>>(MAXN, vector<int>(K));
    for(int i = 0; i < n; ++i) st[i][0] = n - p[i];
    for(int i = 0; i < n; ++i) st[i][1] = lcp[i];


    for(int i = 2; i < K; ++i){
      int j = 0;
      int intvSize = (1 << i);
      while(j + intvSize <= n){
        int lastIntv = i-1;
        int lastIntvSize = (1 << (i-1));

        int a = st[j][lastIntv];
        int b = st[j + lastIntvSize][lastIntv];
        int c = st[j + lastIntvSize - 1][1];
        st[j][i] = min({a, b, c});
        j++;
      }
    }
  }

  int query(int l, int r){
    // O(1)
    int interv_size = r - l + 1; // recuperando o tamanho do intervalo
    int j = vlog[interv_size]; // recuperando pot que def o tam do interv.
    // tamanho de intervalo que vai ser considerado ja que o log eh capado
    int used_interv_size = (1 << j);

    int ans = min({st[l][j], st[r - used_interv_size + 1][j]});
    return ans;
  }
};
