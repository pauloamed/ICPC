// https://codeforces.com/edu/course/2/lesson/7/3/practice/contest/289392/problem/C
// solves dynamic conn offline with following input format:
// ?: query # numComponents
// + a b: adds edge (a,b)
// - a b: removes edge (a,b)
#include<bits/stdc++.h>
using namespace std;

#define MAXN 300010


struct DSU{
  int numComponents;
  int sizes[MAXN]; // vetor com tamanhos
  int parents[MAXN]; // vetor com pai de cada no
  stack<pair<int,int>> lastPar, lastSize;
  vector<int> checkpoints;

  DSU(int n){
    checkpoints.push_back(0);
    numComponents = n;
      for(int i = 0; i < n; ++i){
          sizes[i] = 1; // tamanho inicial
          parents[i] = i; // valor padrao: cada um eh seu pai
      }
  }

  int find(int current){
      int newRoot = current; // variavel para guardar nova raiz
      while(newRoot != parents[newRoot]) // enquanto nao encontro no raiz
          newRoot = parents[newRoot]; // subo na arvore
      return newRoot; // retornamo a raiz da arvore
  }

  void onion(int a, int b){
      a = find(a); b = find(b); // unimos uma raiz a outra

      if(a == b) return; // se for a mesma raiz, nao tenho o que unir

      // uniao por tamanho
      if(sizes[a] < sizes[b]) swap(a,b); // quero unir "b" a "a"

      checkpoints.back()++;
      lastSize.push({a, sizes[a]});
      lastPar.push({b, parents[b]});

      sizes[a] += sizes[b]; // atualizando tamanho de "a"
      parents[b] = a; // pai de "b" eh "a"
      numComponents--;
  }

  void check(){
    checkpoints.push_back(0);
  }

  void rollback(){
    int x = checkpoints.back();
    numComponents += x;
    while (x--) {
      sizes[lastSize.top().first] = lastSize.top().second; lastSize.pop();
      parents[lastPar.top().first] = lastPar.top().second; lastPar.pop();
    }
    checkpoints.pop_back();
  }
};

struct Struc{
  int u, v;
  int l, r;
  Struc(int a, int b, int c, int d){
    u = a, v = b, l = c, r = d;
  }
};
vector<int> consulta, ret;

void solve(int l, int r, int lCons, int rCons, vector<Struc> edges, DSU &dsu){
  while(lCons < consulta.size() && consulta[lCons] < l) lCons++;
  while(rCons >= 0 && consulta[rCons] > r) rCons--;
  if(lCons == consulta.size() || rCons == -1 || lCons > rCons) return;

  // lCons: pos do primeiro cara com valor maior que ou igual a l
  // rCons: pos do ultimo cara com valor menor que ou igual a r
  dsu.check();

  vector<Struc> newEdges;
  for(auto x : edges){
    if(x.l <= l && r <= x.r){
      dsu.onion(x.u, x.v);
    }else if(min(x.r, r) - max(x.l, l) >= 0){
      newEdges.push_back(x);
    }
  }

  if(l == r){
    for(int i = lCons; i <= rCons; ++i){
      if(consulta[i] == l){
        ret[i] = dsu.numComponents;
      }
    }
  }else{
    int mid = (l + r) / 2;
    solve(l, mid, lCons, rCons, newEdges, dsu);
    solve(mid + 1, r, lCons, rCons, newEdges, dsu);
  }
  dsu.rollback();
}


int main(){
  int n, q; cin >> n >> q;
  DSU dsu(n);

  map<pair<int,int>, int> m;

  vector<Struc> edges;

  for(int i = 0; i < q; ++i){
    char c; cin >> c;
    if(c == '+' || c == '-'){
      int a, b; cin >> a >> b; a--, b--;
      if(a > b) swap(a, b);

      if(c == '+'){
        m[{a, b}] = i;
      }else{
        edges.push_back(Struc(a, b, m[{a, b}], i));
        m[{a, b}] = -1;
      }
    }else{
      consulta.push_back(i);
    }
  }
  for(auto x : m){
    if(x.second != -1){
      int a = x.first.first;
      int b = x.first.second;
      edges.push_back(Struc(a, b, x.second, q));
    }
  }

  ret = vector<int>(consulta.size());
  int c = consulta.size();

  solve(0, q, 0, c - 1, edges, dsu);

  for(auto x : ret){
    cout << x << "\n";
  }
}
