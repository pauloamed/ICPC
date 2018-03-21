#include<bits/stdc++.h>
using namespace std;

#define INF 2000000000

bool estoque[100001];
vector<int> ks;

vector<pair<int,int>> v[100001];

int main(){
  int n,m,k;
  int a,b,c;

  scanf("%d %d %d", &n,&m,&k);
  for(int i = 0; i <= n; i++){
    estoque[i] = false;
  }

  for(int i = 0; i < m; i++){
  scanf("%d %d %d", &a,&b,&c);
  v[a].push_back(make_pair(b,c));
  v[b].push_back(make_pair(a,c));
  }
  for(int i = 0; i < k; i++){
    scanf("%d", &a);
    ks.push_back(a);
    estoque[a] = true;
  }

  int dist = INF;
  for(int i = 0; i < k; i++){
    for(int j = 0; j < v[ks[i]].size(); j++){
      if(!estoque[v[ks[i]][j].first]){
        dist = min(dist,v[ks[i]][j].second);
      }
    }
  }
  if(dist == INF)
    printf("-1\n");
  else
    printf("%d\n", dist);
}
