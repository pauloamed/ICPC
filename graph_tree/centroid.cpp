namespace centree{
  bool rmvd[MAXN];
  int sz[MAXN];
  int get_next_centroid(int x, int p, int tree_sz){
    for(auto y : g[x]) if(y != p && !rmvd[y] && sz[y] > (tree_sz / 2))
      return get_next_centroid(y, x, tree_sz);
    return x;
  }

  void comp_sz(int x, int p){
    sz[x] = 1;
    for(auto y : g[x]) if(y != p && !rmvd[y]){
      comp_sz(y, x);
      sz[x] += sz[y];
    } 
  }

  int ct_par[MAXN];
  void centroid(int x, int p){
    comp_sz(x, -1);
    int c = get_next_centroid(x, -1, sz[x]);
    rmvd[c] = 1;
    ct_par[c] = p;
    for(auto y : g[c]){
      if(!rmvd[y]) centroid(y, c);
    }
  }
}
