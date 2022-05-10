#include<bits/stdc++.h>
using namespace std;
 
#define N 22
#define MAXMASK (1 << N)
 
// inv(X): all bits flipped
// LEMMA 1: X&Y=0 <=> Y is submask of inv(X) 
// LEMMA 2: X is submask of Y <=> inv(Y) is submask of inv(X)

// number of elements Y such that X∣Y=X
// Y is a submask of X
vector<int> fa(MAXMASK); 

// number of elements Y such that X&Y=X
// number of elements Y s.t. X is submask of Y
// number of elements Y s.t. inv(Y) is submask of inv(X)
vector<int> fb(MAXMASK);
               
// number of elements Y s.t. X&Y != 0
// n - (number of elements Y s.t. X&Y = 0) 
// n - sum_over_subsets of inv(X)
vector<int> fc(MAXMASK);
 
int main(){
  cin.tie(NULL)->sync_with_stdio(false);
  
  int n; cin >> n;
  vector<int> v(n);
  for(auto &x : v){
    cin >> x;
    fa[x]++;
    fb[x ^ (MAXMASK - 1)]++;
    fc[x]++;
  }
 
  // SOS pd
  for(int i = 0;i < N; ++i){
    for(int mask = 0; mask < (1<<N); ++mask){
      if(mask & (1<<i)) fa[mask] += fa[mask^(1<<i)];
      if(mask & (1<<i)) fb[mask] += fb[mask^(1<<i)];
      if(mask & (1<<i)) fc[mask] += fc[mask^(1<<i)];
    }
  }
  
  for(auto x : v){
    cout << fa[x] << " ";
    cout << fb[x ^ (MAXMASK - 1)] << " ";
    cout << (n - fc[x ^ (MAXMASK - 1)]) << "\n";
  }
}
