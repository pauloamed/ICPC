// https://codeforces.com/gym/102392/problem/F
#include<bits/stdc++.h>
using namespace std;

#define MAXN 100010

vector<int> v[MAXN];  

int get_matching(int x, int p){
  bool is_leaf = true;
  int d = 0;
  for(auto y : v[x]){
    if(y == p) continue;
    is_leaf = false;
    d += get_matching(y, x);
  }
  if(is_leaf) return 1;
  else{
    if(d > 0)return d - 1;
    else return 1;
  }
}

int main(){
  int n; cin >> n;
  for(int i = 0; i < n - 1; ++i){
    int a, b; cin >> a >> b;
    v[a].push_back(b);
    v[b].push_back(a);
  }

  if(get_matching(1, -1) == 0){
    cout << "Bob\n";
  }else{
    cout << "Alice\n";
  }
}
