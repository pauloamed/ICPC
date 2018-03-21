#include<bits/stdc++.h>
using namespace std;

vector<int> vt[401];
vector<int> vo[401];
bool matriz[401][401];
int distt[401];
int disto[401];

set<pair<int,int>> ordem;


int main(){
  int n,m;
  int x,y;
  cin >> n >> m;

  for(int i = 1; i <= n; i++){
    distt[i] = 500;
    disto[i] = 500;
    for(int j = 1; j <= n; j++){
      matriz[i][j] = false;
    }
  }

  for(int i = 0; i < m; i++){
    scanf("%d %d", &x, &y);
    vt[x].push_back(y);
    vt[y].push_back(x);
    matriz[x][y] = true;
    matriz[y][x] = true;
  }

  if(!matriz[1][n]){
    distt[1] = 0;
    ordem.insert(make_pair(0,1));
    int va,da;
    while(!ordem.empty()){
      va = ordem.begin()->second;
      da = ordem.begin()->first;
      ordem.erase(ordem.begin());

      if(distt[va] < da)
        continue;

      for(int i = 0; i < vt[va].size(); i++){
        if(distt[vt[va][i]] > da + 1){
          distt[vt[va][i]] = da + 1;
          ordem.insert(make_pair(da+1,vt[va][i]));
        }
      }
    }
    if(distt[n] != 500)
      printf("%d\n", distt[n]);
    else
      printf("-1\n");
    return 0;
  }else{
    for(int i = 1; i <= n; i++){
      for(int j = 1; j <= n; j++){
        if(!matriz[i][j] && i != j){
          matriz[i][j] = true;
          matriz[j][i] = true;

          vo[i].push_back(j);
          vo[j].push_back(i);
        }
      }
    }
    disto[1] = 0;
    ordem.insert(make_pair(0,1));
    int va,da;
    while(!ordem.empty()){
      va = ordem.begin()->second;
      da = ordem.begin()->first;
      ordem.erase(ordem.begin());

      if(disto[va] < da)
        continue;

      for(int i = 0; i < vo[va].size(); i++){
        if(disto[vo[va][i]] > da + 1){
          disto[vo[va][i]] = da + 1;
          ordem.insert(make_pair(da+1,vo[va][i]));
        }
      }
    }
    if(disto[n] != 500)
      printf("%d\n", disto[n]);
    else
      printf("-1\n");
    return 0;
  }


}
