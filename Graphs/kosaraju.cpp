#include<bits/stdc++.h>
using namespace std;

vector<int> v[2001];
vector<int> rv[2001];
stack<int> pilha;
bool visitado[2001];

void dfs(int x){
  visitado[x] = true;

  for(int i = 0; i < v[x].size(); i++){
    if(!visitado[v[x][i]])
      dfs(v[x][i]);
  }

  pilha.push(x);
}

void rdfs(int x){
  visitado[x] = true;
  for(int i = 0; i < rv[x].size(); i++){
    if(!visitado[rv[x][i]])
      rdfs(rv[x][i]);
  }
}

int main(){
    int n,m,a,b,c;

    while(1){
      scanf("%d %d", &n,&m);

      if(!n)
        return n;

      for(int i = 1; i <= n; i++){
        v[i].clear();
        rv[i].clear();
      }

      for(int i = 0; i < m; i++){
        scanf("%d %d %d", &a,&b,&c);
        v[a].push_back(b);
        rv[b].push_back(a);
        if(c == 2){
          v[b].push_back(a);
          rv[a].push_back(b);
        }
      }

      for(int i = 1; i<= n; i++)
        visitado[i] = false;

      for(int i = 1; i <= n; i++){
        if(!visitado[i])
          dfs(i);
      }

      for(int i = 1; i<= n; i++)
        visitado[i] = false;

      int cont = 0;

      while(!pilha.empty()){
        if(!visitado[pilha.top()]){
          rdfs(pilha.top());
          cont++;
          if(cont > 1){
            break;
          }
        }
        pilha.pop();
      }
      while(!pilha.empty())
        pilha.pop();

      if(cont > 1){
        printf("0\n");
      }else
        printf("1\n");
   }
}
