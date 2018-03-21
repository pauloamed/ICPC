#include<bits/stdc++.h>
using namespace std;

int v[30001];
bool jafoi[30001];

bool dfs(int x, int d){
  if(x == d)
    return true;

  bool ans = false;

  if(v[x] == -1)
    return ans;

  if(!jafoi[v[x]])
      ans = max(ans,dfs(v[x],d));

  return ans;

}

int main(){
  int n, d, x;
  cin >> n >> d;

  for(int i = 1; i <= n-1; i++){
    jafoi[i] = false;
    scanf("%d", &x);
    v[i] = x + i;
  }jafoi[n] = false;
  v[n] = -1;

  if(dfs(1,d))
    printf("YES\n");
  else
    printf("NO\n");
}
