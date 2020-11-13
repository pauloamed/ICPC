/*
https://codeforces.com/edu/course/2/lesson/2/5/practice/contest/269656/problem/C
*/

#include<bits/stdc++.h>
using namespace std;

#define MAXN 400010
#define K 19

namespace SA{
  vector<int> r, p, lcp, vlog;
  vector<vector<int>> st;
  int h, n;

  bool cmp(int i, int j){
    if(r[i] == r[j]){
      if(max(i,j)+h>=n) return i > j;
      else return r[i+h] < r[j+h];
    }else return r[i] < r[j];
  }

  void prepare(string const& s){
    n = s.size();
    vector<int> aux;
    aux = p = r = vector<int>(n);
    for(int i = 0; i < n; ++i){
      p[i] = i; r[i] = s[i];
    }

    for(h = 1;; h <<= 1){
      sort(begin(p), end(p), cmp);
      aux[p[0]] = 0;
      for(int i = 1; i < n; ++i){
        aux[p[i]] = aux[p[i-1]] + cmp(p[i-1], p[i]);
      }
      swap(aux, r);
      if(r[p[n-1]] == n-1) break;
    }
  }

  void prepare_lcp(string const& s) {
    lcp = vector<int>(n, 0);
    int k = 0;
    for (int i = 0; i < n; i++){
      if (r[i] == n - 1){
        lcp[r[i]] = k = 0;
      }else{
        int j = p[r[i] + 1];
        while (max(i, j) + k < n && s[i+k] == s[j+k]) k++;
        lcp[r[i]] = k;
        if(k) k--;
      }
    }
  }

  void precalc(int n){
    for(int i = 0; i < MAXN; ++i){
      if(i<=1) vlog.push_back(0);
      else vlog.push_back(vlog[i/2] + 1);
    }

    st = vector<vector<int>>(MAXN, vector<int>(K));
    for(int i = 0; i < n; ++i) st[i][0] = n - p[i];
    for(int i = 0; i < n; ++i) st[i][1] = lcp[i];



    // preenchendo restante da st
    for(int i = 2; i < K; ++i){ // para cada tam de intervalo
      int j = 0; // comeco na pos inicial. para cada posicao.
      int interval_size = (1 << i); // tamanho do intervalo def pelo for externo
      while(j + interval_size <= n){ // enquanto o interv. estiver num pos valida
        int last_interv = i-1; // recuperando valor de i para o intervalo anterior
        int last_invert_size = (1 << (i-1)); // recuperando tam do interv anterior

        // calculo o intervalo atual somando as metades
        // uma comecando em j e outra em j+((2^j)/2)
        st[j][i] = min({st[j][last_interv], st[j + last_invert_size][last_interv], st[j + last_invert_size - 1][1]}); // OPERACAO
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

    // printf(">> %d %d %d %d\n", l, r, used_interv_size, r - used_interv_size + 1);
    int ans = min({st[l][j], st[r - used_interv_size + 1][j]}); // ok ter sobreposicao IDEMPOTENCIA
    // printf("j: %d l: %d r: %d ans: %d x: %d y: %d\n", j, l, r, ans, st[l][j], st[r - used_interv_size + 1][j]);
    return ans;
  }
};



int eval(pair<int,int> &a, pair<int,int> &b, string &s){
  int la = a.first, ra = a.second;
  int lb = b.first, rb = b.second;
  int sa = ra - la, sb = rb - lb;

  int l = min(SA::r[la], SA::r[lb]);
  int r = max(SA::r[la], SA::r[lb]);

  int lcp = SA::query(l, r);

  char ca = 0, cb = 0;
  if(la+lcp <= ra) ca = s[la+lcp];
  if(lb+lcp <= rb) cb = s[lb+lcp];

  if(ca < cb) return 1;
  else if(ca == cb){
    if(sa == sb) return 0;
    else if(sa < sb) return 1;
    else return -1;
  }
  else return -1;
}

char str[MAXN];
int main(){
  scanf("%s", str);
  string s(str);
  SA::prepare(s);
  SA::prepare_lcp(s);
  SA::precalc(s.size());


  int n; cin >> n;
  vector<pair<int,int>> v(n);
  for(auto &x : v){
    scanf("%d %d", &x.first, &x.second);
    x.first--; x.second--;
  }

  sort(begin(v), end(v), [&](pair<int,int> &a, pair<int,int> &b){
    int x = eval(a,b,s);
    if(x == 0) return a < b;
    else return (x==1);
  });

  for(auto &x : v){
    printf("%d %d\n", x.first+1, x.second+1);
  }
}
