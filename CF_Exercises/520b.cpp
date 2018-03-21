#include<bits/stdc++.h>
using namespace std;

int v[20002];

int solve(int cont, int x, int d){
  // printf("%d %d %d\n", cont,x,d);
  if(x == d)
    return cont;
  if(x <= 0)
    return 100000;

  v[x] = cont;

  int ans = 100000;

  if(x < d){
    if(v[x*2] > cont+1)
      ans = min(ans,solve(cont+1, x*2, d));
  }

  if(v[x-1] > cont+1)
    ans = min(ans,solve(cont+1,x-1,d));

  return ans;
}

int main(){
  int x, y;
  cin >> x >> y;

  for(int i = 0; i <= (2*y)+1; i++)
    v[i] = 100000;

  if(x >= y){
    printf("%d\n", x-y);
  }else{
    printf("%d\n", solve(0,x,y));
  }



  return 0;
}
