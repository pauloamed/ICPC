#include<bits/stdc++.h>
using namespace std;


vector<int> ts;
//so 10 vertices (estudo)
vector<int> v[10];
bool perm[10];
bool temp[10];

bool loop(int x){
  if(perm[x])
    return false;
  if(temp[x])
    return true;

  bool ans = false;

  if(v[x].size() > 0){
    temp[x] = true;
    for(int i = 0; i < v[x].size(); i++){
      ans = max(ans, loop(v[x][i]));
    }
  }
  temp[x] = false;
  ts.push_back(x);
  perm[x] = true;
}

int main(){
  int n,m,nr;
  int x,y;
  cin >> n >> m;

  for(int i = 0; i < n; i++){
    perm[i] = false;
    temp[i] = false;
  }

  for(int i = 0; i < m; i++){
    scanf("%d %d", &x, &y);
    v[x].push_back(y);
  }

  for(int i = 0; i < n; i++){
      if(!perm[i])
        loop(i);
  }

  for(int i = 0; i < ts.size(); i++){
    printf("%d ", ts[i]);
  }cout << endl;


}
