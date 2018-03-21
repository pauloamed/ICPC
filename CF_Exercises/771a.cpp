#include<bits/stdc++.h>
using namespace std;

#define max 150001

vector<int> v[max];
int vm[max];

int dfs(int x, int menor){
  vm[x] = menor;
  int ans = 1;

  for(int i = 0; i < v[x].size(); i++){
    if(vm[v[x][i]] == 0)
      ans += dfs(v[x][i], menor);
  }

  return ans;
}

int main(){
  int n, m, x, y;
  cin >> n >> m;

  for(int i = 1; i <= n; i++){
    vm[i] = 0;
  }
  for(int i = 0; i < m; i++){
    scanf("%d %d", &x, &y);
    v[x].push_back(y);
    v[y].push_back(x);
  }

  map<int,int> mapa;
  for(int i = 1; i <= n; i++){
    if(vm[i] == 0)
      mapa[i] = dfs(i, i);
  }

  for(int i = 1; i <= n; i++){
    if(mapa[vm[i]] != v[i].size()+1){
      cout << "NO" << endl;
      return 0;
    }
  }cout << "YES" << endl;
}
