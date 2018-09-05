#include<bits/stdc++.h>
using namespace std;

bool visited[101], inside[101];
vector<int> v[101];
int qntsv[101];

int tafeio(int x){
  visited[x] = true;

  int ans = 0;

  for(int i = 0; i < v[x].size(); i++){
    if(!visited[v[x][i]])
      ans += tafeio(v[x][i]);
  }
  return ans + 1;
}

int main(){
  int n, m;
  int a,b;
  scanf("%d %d", &n, &m);

  for(int i = 0; i <= n; i++){
    visited[i] = false;
    qntsv[i] = 0;
  }

  for(int i = 0; i < m; i++){
    scanf("%d %d", &a, &b);
    v[a].push_back(b);
    v[b].push_back(a);
    qntsv[a]++;
    qntsv[b]++;
  }

  if(tafeio(1) != n){
    printf("NO\n");
    return 0;
  }

  set<pair<int,int>> s;
  for(int i = 1; i <= n; i++){
    visited[i] = false;
    s.insert(make_pair(qntsv[i],i));
  }

  int qntatual, vatual;
  while(1){
    if(s.empty()){
      printf("NO\n");
      return 0;
    }

    qntatual = s.begin()->first;
    vatual = s.begin()->second;
    // printf("%d %d\n", qntatual, vatual);
    s.erase(s.begin());

    if(visited[vatual])
      continue;

    if(qntatual == 2)
      break;

    visited[vatual] = true;

    for(int i = 0; i < v[vatual].size(); i++){
      qntsv[v[vatual][i]]--;
      s.insert(make_pair(qntsv[v[vatual][i]],v[vatual][i]));
    }
  }

  for(int i = 1; i <= n; i++){
    if(!visited[i]){
      if(qntsv[i] != 2){
        printf("NO\n");
        return 0;
      }
    }
  }
  printf("FHTAGN!\n");

}
