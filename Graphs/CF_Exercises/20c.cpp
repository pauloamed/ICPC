#include<bits/stdc++.h>
using namespace std;

#define MAX 100001
#define INF 1000000000000000

int last[MAX];
vector<int> r;
bool solve(int x){
  bool ans = false;

  if(x == -1)
    return false;

  if(x == 1){
    r.push_back(1);
    return true;
  }

  ans = max(ans, solve(last[x]));

  if(ans)
    r.push_back(x);

  return ans;
}

int main(){
  set<pair<long long,int>> ordem;
  vector<pair<int,long long>> v[MAX];
  long long dist[MAX];

  int n,m;
  int x,y,z;
  scanf("%d %d", &n,&m);

  for(int i = 1; i <= n; i++){
    last[i] = -1;
    dist[i] = INF;
  }

  for(int i = 0; i < m; i++){
    scanf("%d %d %d", &x, &y, &z);
    v[x].push_back(make_pair(y,z));
    v[y].push_back(make_pair(x,z));
  }

  ordem.insert(make_pair(0,1));

  int va;
  long long da;
  long long aux;
  while(ordem.size() > 0){
    va = ordem.begin()->second;
    da = ordem.begin()->first;
    ordem.erase(ordem.begin());

    if(dist[va] < da)
      continue;

    for(int i = 0; i < v[va].size(); i++){
      aux = da + v[va][i].second;
      if(dist[v[va][i].first] > aux){
        dist[v[va][i].first] = aux;
        ordem.insert(make_pair(aux, v[va][i].first));

        last[v[va][i].first] = va;
      }
    }
  }

  if(solve(n)){
    printf("%d", r[0]);
    for(int i = 1; i < r.size(); i++){
      printf(" %d", r[i]);
    }cout << endl;
  }else
    printf("-1\n");


}
