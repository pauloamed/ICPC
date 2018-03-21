#include<bits/stdc++.h>
using namespace std;

int main(){
  int n,h2,h1;
  scanf("%d %d %d", &n, &h2, &h1);
  h2 -= h1;
  if(h2 > h1 || h2 < 0 || (h2+h1+1) > n || (h2 == 0 && h1 == 1 && n > 2)){
    printf("-1\n");
    return 0;
  }else{
    int v_atual = 2;
    for(int i = 0; i < h1; i++){
      printf("%d %d\n", v_atual-1, v_atual);
      v_atual++;
    }
    for(int i = 0; i < h2; i++){
      if(i == 0)
        printf("1 %d\n", v_atual);
      else
        printf("%d %d\n", v_atual-1, v_atual);

      v_atual++;
    }
    if(h2 > 0){
      for(;v_atual <= n; v_atual++)
      printf("1 %d\n", v_atual);
    }else{
      for(;v_atual <= n; v_atual++)
      printf("2 %d\n", v_atual);
    }
  }
}
