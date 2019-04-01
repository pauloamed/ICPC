#include<bits/stdc++.h>
using namespace std;

//vector para identificar cor e aresta
vector<int> v[101][101];
bool dacerto[101][101][101],jafoip[101][101][101],jafoit[101];

bool dfs(int x, int y, int c){
  if(jafoip[x][y][c])
    return dacerto[x][y][c];


  jafoit[x] = true;
  bool ans = false;

  if(x == y){
    ans = true;
  }else{
    for(int i = 0; i < v[c][x].size(); i++){
      if(!jafoit[v[c][x][i]])
        ans = max(ans,dfs(v[c][x][i],y,c));
    }
  }

  jafoit[x] = false;
  return ans;
}

int main(){
  int n,m;
  int a,b,c;
  scanf("%d %d", &n, &m);

  for(int i = 0; i <= n; i++){
    for(int j = 0; j <= n; j++){
      for(int k = 0; k <= n; k++)
        jafoip[i][j][k] = false;
    }
  }

  for(int i = 0; i < m; i++){
    scanf("%d %d %d", &a, &b, &c);
    v[c][a].push_back(b);
    v[c][b].push_back(a);
  }

  int ans;
  scanf("%d", &c);
  for(int i = 0; i < c; i++){
    ans = 0;
    scanf("%d %d", &a, &b);
    for(int j = 1; j <= m; j++){
      if(v[j][a].size() > 0){
      dacerto[a][b][j] = dfs(a,b,j);
      jafoip[a][b][j] = true;

      if(dacerto[a][b][j]){
          ans++;
        }
      }
    }
    printf("%d\n", ans);
  }
}
