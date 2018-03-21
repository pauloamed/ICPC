#include<bits/stdc++.h>
using namespace std;

vector<int> v[2001];

int dfs(int x, int cont){
  int ans = 0;

  if(v[x].size() == 0)
    return cont;
  else{
    for(int i = 0; i < v[x].size(); i++)
      ans = max(ans,dfs(v[x][i], cont+1));
  }

  return ans;
}

int main(){
  int n, x;
  cin >> n;
  for(int i = 1; i <= n; i++){
    scanf("%d", &x);
    if(x == -1)
      v[0].push_back(i);
    else
      v[x].push_back(i);
  }

  printf("%d\n", dfs(0,0));



  return 0;
}
