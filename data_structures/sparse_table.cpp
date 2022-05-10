#include<bits/stdc++.h>
using namespace std;

#define MAXN 10000000
#define K 25

int st[MAXN][K]; 
int v[MAXN]; 
int vlog[MAXN+1]; // only for idempotent functions

void precalc(int n){
  for(int i = 0; i < n; ++i) st[i][0] = v[i];
  for(int i = 1; i < K; ++i){ 
    int j = 0; 
    int interv_sz = (1 << i); 
    while(j + interv_sz <= n){ 
      st[j][i] = st[j][i - 1] +  st[j + interv_sz / 2][i - 1]; // OP
      j++;
    }
  }
  // below only for idempotent functions
  vlog[1] = 0;
  for(int i = 2; i <= MAXN; i++) vlog[i] = vlog[i/2] + 1; 
}

int query(int l, int r){ // idempotent
  int interv_sz = r - l + 1; 
  int j = vlog[interv_sz]; 
  return min(st[l][j], st[r - (1 << j) + 1][j]); // OP
}

int query(int l, int r){ // non-idempotent
  int query_sz = r - l + 1; 

  int ret = 0;    
  for(int i = K - 1; i >= 0; i--){
    int interv_sz = (1 << i); 
    if(interv_sz <= query_sz){
      ret += st[l][i];  // OP
      query_sz -= interv_sz; 
      l += interv_sz; 
    }
  }
  return ret;
}
