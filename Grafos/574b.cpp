#include<bits/stdc++.h>
using namespace std;

#define INF 10000000

vector<int> v[4001];

int dfs(int f, int x, int cont){

  int ans = INF;

  if(v[x].size()>=2){
    if(cont < 3){
    for(int i = 0; i < v[x].size(); i++){
        if(v[x][i] > x)
          ans = min(ans,dfs(f,v[x][i],cont+1)+((int)v[x].size()-2));
      }
    }else if(cont == 3){
      for(int i = 0; i < v[x].size(); i++){
        if(v[x][i] == f)
          return v[x].size()-2;
      }
    }
  }

  return ans;
}

int main(){
  int n,m;
  int a,b;

  scanf("%d %d", &n,&m);

  for(int i = 0; i < m; i++){
    scanf("%d %d", &a, &b);
    v[a].push_back(b);
    v[b].push_back(a);
  }

  int ans = INF;
  for(int i = 1; i <= n; i++)
    ans = min(ans,dfs(i,i,1));
    
  if(ans == INF)
    ans = -1;

  printf("%d\n", ans);
}
