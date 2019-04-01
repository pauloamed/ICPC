#include<bits/stdc++.h>
using namespace std;

vector<int> X[1001];
vector<int> Y[1001];
pair<int,int> v[101];
bool jafoi[101];

void dfs(int x){
  jafoi[x] = true;

  for(int i = 0; i < X[v[x].first].size(); i++){
    if(!jafoi[X[v[x].first][i]])
      dfs(X[v[x].first][i]);
  }

  for(int i = 0; i < Y[v[x].second].size(); i++){
    if(!jafoi[Y[v[x].second][i]])
      dfs(Y[v[x].second][i]);
  }

}

int main(){
  int n,a,b;
  scanf("%d", &n);

  for(int i = 0; i < n; i++){
    jafoi[i] = false;
    scanf("%d %d", &a, &b);
    X[a].push_back(i);
    Y[b].push_back(i);
    v[i] = make_pair(a,b);
  }

  int cont = 0;
  for(int i = 0; i < n; i++){
    if(!jafoi[i]){
      cont++;
      dfs(i);
    }
  }
  cout << cont-1 << endl;
}
