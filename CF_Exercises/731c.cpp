#include<bits/stdc++.h>
using namespace std;

int cor[200001];
bool visited[200001];
vector<int> vcores;

vector<int> v[200001];

int solve(int x){
  visited[x] = true;
  int ans = 0;

  vcores.push_back(cor[x]);

  for(int i = 0; i < v[x].size(); i++){
    if(!visited[v[x][i]])
      ans += solve(v[x][i]);
  }

  if(ans == 0) return 1;
  else return ans+1;

}
int main(){
  int s, d, c, x,y;
  scanf("%d %d %d", &s, &d, &c);
  for(int i = 1; i <= s; i++){
    scanf("%d", &cor[i]);
    visited[i] = true;
  }

  for(int i = 0; i < d; i++){
    scanf("%d %d", &x, &y);
    v[x].push_back(y);
    v[y].push_back(x);
    visited[x] = false;
    visited[y] = false;
  }

  int vs, maior, cont,ans = 0;
  for(int i = 1; i <= s; i++){
    if(!visited[i]){
      maior = 0;
      vs = solve(i);
      sort(vcores.begin(), vcores.end());

      cont = 1;
      for(int j = 1; j < vcores.size(); j++, cont++){
        if(vcores[j] != vcores[j-1]){
          maior = max(cont,maior);
          cont=0;
        }
      }maior = max(maior,cont);


      ans += vs-maior;
      vcores.clear();
    }
  }
  printf("%d\n", ans);
}
