#define MAXN 100010
#define MAXLOG 25


vector<int> g[MAXN];

namespace lca{
  int st[MAXN][MAXLOG], d[MAXN];

  void get_par(int x, int p){
    st[x][0] = p;
    if(p != -1) d[x] = d[p] + 1;
    for(auto y : g[x]) if(y != p) get_par(y, x);
  }

  void init(int root, int n){
    get_par(root, -1);
    for(int l = 1; l < MAXLOG; ++l) for(int i = 0; i < MAXN; ++i){
      if(st[i][l-1] == -1) st[i][l] = -1;
      else st[i][l] = st[st[i][l-1]][l-1];
    }
  }

  int lca(int x, int y){
    if(d[x] < d[y]) swap(x, y);
    int falta_subir = (d[x] - d[y]);
    for(int i = MAXLOG-1; i >= 0; --i) if((1<<i) <= falta_subir){
      falta_subir -= (1<<i);
      x = st[x][i];
    }
    if(x == y) return x;
    for(int i = MAXLOG-1; i >= 0; --i) if(st[x][i] != st[y][i])
      x = st[x][i], y = st[y][i];
    return st[x][0];
  }

  int dist(int a, int b){
    int x = lca(a, b);
    return (d[a] - d[x]) + (d[b] - d[x]);
  }
}
