#include<bits/stdc++.h>
using namespace std;

bool ok[1001];

int main(){
  int n,m,x,y;

  scanf("%d %d", &n, &m);

  for(int i = 0; i <= n; i++){
    ok[i] = true;
  }

  for(int i = 0; i < m; i++){
    scanf("%d %d", &x,&y);
    ok[x] = false;
    ok[y] = false;
  }

  int ook;
  for(int i = 1; i <= n; i++){
    if(ok[i]){
      ook = i;
      break;
    }
  }

  printf("%d\n", n-1);
  for(int i = 1; i <= n; i++){
    if(i!=ook){
      printf("%d %d\n", ook,i);
    }
  }
}
