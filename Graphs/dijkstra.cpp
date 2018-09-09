#include<bits/stdc++.h>
using namespace std;

#define INF 10000000

vector<int> dist;
vector<int> v[100];
set<pair<int,int>> s;
int matriz_pesos[100][100];


int main(){
  int a,b,c,V,M;

  cin >> V >> M;
  for(int i = 0; i <= V; i++){
    dist.push_back(INF);
  }

  for(int i = 0; i < M; i++){
    cin >> a >> b >> c;
    v[a].push_back(b);
    matriz_pesos[a][b] = c;
  }

  cout << "type the  source vertex x, 0 <= x < V\n";
  cin >> a;

  dist.at(a) = 0;
  s.insert(make_pair(0,a));
  int dist_atual, x;
  while(!s.empty()){
    x = s.begin()->second;
    dist_atual = s.begin()->first;
    s.erase(s.begin());

    if(dist_atual > dist.at(x))
      continue;

    for(int i = 0; i < v[x].size(); i++){
      if(dist_atual + matriz_pesos[x][v[x][i]] < dist[v[x][i]]){
        dist[v[x][i]] = dist_atual + matriz_pesos[x][v[x][i]];
        s.insert(make_pair(dist[v[x][i]],v[x][i]));
      }
    }
  }

  for(int i = 0; i < V; i++){
    printf("%d %d\n", i, dist.at(i));
  }


  return 0;
}
