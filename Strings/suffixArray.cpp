namespace SA{
  vector<int> r, p, lcp;
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
};
