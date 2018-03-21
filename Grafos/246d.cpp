#include<bits/stdc++.h>
using namespace std;

bool cmp(pair<int,int>& a, pair<int,int>& b){
  if(a.first == b.first){
    return a.second < b.second;
  }else{
    return a.first > b.first;
  }
}

int main(){
  int n, m, a,b;
  scanf("%d %d", &n, &m);

  int cor[n+1];
  map<int,bool> cont[100001];

  for(int i = 0; i < n; i++)
    scanf("%d", &cor[i+1]);
  for(int i = 0; i < m; i++){
    scanf("%d %d", &a, &b);
    if(cor[a] == cor[b])
      continue;
    cont[cor[a]][cor[b]] = true;
    cont[cor[b]][cor[a]] = true;
  }

  vector<pair<int,int>> ans;
  for(int i = 1; i <= n; i++){
    ans.push_back(make_pair(cont[cor[i]].size(),cor[i]));
  }sort(ans.begin(),ans.end(),cmp);

  printf("%d\n", ans[0].second);
}
