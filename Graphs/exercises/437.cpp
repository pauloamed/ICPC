#include<bits/stdc++.h>
using namespace std;


int vals[1001];

int main(){
  int n,m,x,y;

  cin >> n >> m;

  //init
  for(int i = 1; i <= n; i++)
    scanf("%d", &vals[i]);


  //ans
  long long ans = 0;
  for(int i = 0; i < m; i++){
    scanf("%d %d", &x, &y);
    ans += min(vals[x],vals[y]);
  }

  cout << ans << endl;



}
