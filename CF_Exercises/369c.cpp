#include<bits/stdc++.h>
using namespace std;

bool jafoi[100001];
vector<pair<int,int>> v[100001];
set<int> r;
set<int> ::iterator it;

int marcar(int x, int f){
  jafoi[x] = true;
  int ans = 0;

  for(int i = 0; i < v[x].size(); i++){
    if(!jafoi[v[x][i].first]){
      if(marcar(v[x][i].first, v[x][i].second) == 2)
        ans = 2;
      else
        ans = max(1, ans);
    }
  }

  if(ans == 1 || ans == 0){
    ans = f;
    if(ans == 2)
      r.insert(x);
  }
  return ans;
}

int main(){
  int n,a,b,c;
  scanf("%d", &n);
  for(int i = 0; i < n-1; i++){
    scanf("%d %d %d", &a, &b, &c);
    v[a].push_back(make_pair(b,c));
    v[b].push_back(make_pair(a,c));
  }

  marcar(1,1);

  printf("%d\n", r.size());
  for(it = r.begin(); it != r.end(); it++){
    printf("%d ", *it);
  }printf("\n");
}
