#include<bits/stdc++.h>
using namespace std;

vector<int> v[100001],c[2];
int jafoi[100001];

bool dfs(int x, int a){

  if(v[x].size() > 0){
    jafoi[x] = a;
    c[a].push_back(x);
  }

  for(int i = 0; i < v[x].size(); i++){
    if(jafoi[v[x][i]] == -1){
      if(!dfs(v[x][i], (a+1)%2))
        return false;
    }else if(jafoi[v[x][i]] == a){
      return false;
    }
  }

  return true;
}

int main(){
  int n,m;

  scanf("%d %d", &n, &m);

  int x,y;
  for(int i = 0; i <= n; i++){
    jafoi[i] = -1;
  }

  for(int i = 0; i < m; i++){
    scanf("%d %d", &x, &y);
    v[x].push_back(y);
    v[y].push_back(x);
  }

  for(int i = 1; i <= n; i++){
    if(jafoi[i] == -1){
      if(!dfs(i,1)){
        printf("-1\n");
        return 0;
      }
    }
  }

  printf("%ld\n%d", c[0].size(),c[0][0]);
  for(int i = 1; i < c[0].size(); i++){
    printf(" %d", c[0][i]);
  }cout << endl;
  printf("%ld\n%d", c[1].size(),c[1][0]);
  for(int i = 1; i < c[1].size(); i++){
    printf(" %d", c[1][i]);
  }cout << endl;
}
