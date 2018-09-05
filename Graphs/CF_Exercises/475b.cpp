#include<bits/stdc++.h>
using namespace std;

bool coldir[21], lindown[21];
bool visitado[21][21];

stack<pair<int,int>> pilha;

void dfs(int x, int y, int n, int m){
  visitado[x][y] = true;

  if(coldir[x]){
    if(y<m-1 && !visitado[x][y+1])
      dfs(x,y+1,n,m);
  }else{
    if(y>0 && !visitado[x][y-1])
      dfs(x,y-1,n,m);
  }

  if(lindown[y]){
    if(x < n-1 && !visitado[x+1][y])
      dfs(x+1,y,n,m);
  }else{
    if(x > 0 && !visitado[x-1][y])
      dfs(x-1,y,n,m);
  }

  pilha.push(make_pair(x,y));

}

int main(){
  int x,y;
  char c;
  cin >> x >> y;

  for(int i = 0; i < x; i++){
    for(int j = 0; j < y; j++)
      visitado[i][j] = false;
  }

  for(int i = 0; i < x; i++){
    scanf(" %c", &c);
    coldir[i] = (c == '>');
  }
  for(int i = 0; i < y; i++){
    scanf(" %c", &c);
    lindown[i] = (c == 'v');
  }

  for(int i = 0; i < x; i++){
    for(int j = 0; j < y; j++){
      if(!visitado[i][j])
        dfs(i,j,x,y);
    }
  }

  for(int i = 0; i < x; i++){
    coldir[i] = !coldir[i];
    for(int j = 0; j < y; j++)
      visitado[i][j] = false;
  }

  for(int i = 0; i < y; i++)
    lindown[i] = !lindown[i];

  int a,b,cont=0;
  while(!pilha.empty()){
    a = pilha.top().first;
    b = pilha.top().second;
    if(!visitado[a][b]){
      if(cont > 1){
        printf("NO\n");
        return 0;
      }
      dfs(a,b,x,y);
      cont++;
    }
    pilha.pop();
  }
  printf("YES\n");


}
