#include<bits/stdc++.h>
using namespace std;

vector<int> conv[300];
vector<int> conp[300];
map<int,int> corresp;
map<int,int> ::iterator it;
vector<int> atual;

vector<int> v[301];
bool jafoi[301];

void dfs(int x, int mini){
  jafoi[x] = true;

  for(int i = 0; i < v[x].size(); i++){
    if(!jafoi[v[x][i]])
      dfs(v[x][i], mini);
  }

  conv[corresp[mini]].push_back(atual[x-1]);
  conp[corresp[mini]].push_back(x);
}

int main(){

  char c;

  int n,x;
  scanf("%d", &n);

  for(int i = 0; i < n; i++){
    scanf("%d", &x);
    atual.push_back(x);
    jafoi[i+1] = false;
  }

  for(int i = 0 ; i < n; i++){
    for(int j = 0; j < n; j++){
      scanf(" %c", &c);
      if(c == '1'){
        v[i+1].push_back(j+1);
        v[j+1].push_back(i+1);
      }
    }
  }

  int cont = 0;
  for(int i = 1; i <= n; i++){
    if(!jafoi[i]){
      corresp[i] = cont++;
      dfs(i,i);
    }
  }

  int ans[n];

  for(it = corresp.begin(); it!= corresp.end(); it++){
    sort(conv[it->second].begin(),conv[it->second].end());
    sort(conp[it->second].begin(),conp[it->second].end());
    for(int i = 0; i < conv[it->second].size(); i++){
      ans[conp[it->second][i]-1] = conv[it->second][i];
    }
  }

  printf("%d", ans[0]);
  for(int i = 1; i < n; i++)
    printf(" %d", ans[i]);

  cout << endl;
}
