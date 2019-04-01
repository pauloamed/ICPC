#include<bits/stdc++.h>
using namespace std;

vector<int> v[10001];
bool jafoi[10001];

void dfs(int x){
  jafoi[x] = true;

  for(int i = 0; i < v[x].size(); i++){
    if(!jafoi[v[x][i]])
      dfs(v[x][i]);
  }
}

int main(){
  int n, x;
  scanf("%d", &n);

  for(int i = 1; i<=n; i++){
    scanf("%d", &x);
    v[i].push_back(x);
    v[x].push_back(i);
  }

  int cont = 0;
  for(int i = 1; i <=n;i++){
    if(!jafoi[i]){
      cont++;
      dfs(i);
    }
  }
  printf("%d\n", cont);
}
