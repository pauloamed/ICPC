// s[l:r] == s[0:r-l] => s[i:r] == s[0:min(z[i-l], r-i)]
// uses own function for faster computing
// not always `r` will be updated, z[i-l] can be really low

// z[i]: size of longest substring starting from i that is also a prefix
vector<int> compute_z(string &s){
  int n = s.size();
  vector<int> z(n);
  int l = -1, r = -1; // [l;r): rightmost matched interval
  for(int i = 1; i < n; ++i){
    if(i >= r) l = i;
    else z[i] = min(r - i, z[i - l]);
    while(i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
    if(i + z[i] > r){ r = i + z[i], l = i; }
  }
  return z;
}

// can be used for pattern matching (Pattern, String): 
// P+$+S, search for positions in S w/ z[i]=len(P)
