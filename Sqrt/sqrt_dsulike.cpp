#include<bits/stdc++.h>
using namespace std;

#define MAXN 100010
#define BLOCK 200

int nextBlock[MAXN];
int jumps2Next[MAXN];
int power[MAXN];
int blockId[MAXN];


void processPos(int i, int n){
  int nextPos = i + power[i];
  if(nextPos >= n){
    nextBlock[i] = n;
    jumps2Next[i] = 1;
  }else if(blockId[nextPos] > blockId[i]){
    nextBlock[i] = nextPos;
    jumps2Next[i] = 1;
  }else{ // estao no mesmo bloco
    nextBlock[i] = nextBlock[nextPos];
    jumps2Next[i] = jumps2Next[nextPos] + 1;
  }
}

int main(){
  int n, m; scanf("%d %d", &n, &m);


  for(int i = 0; i < n; ++i) scanf("%d", &power[i]);
  for(int i = 0; i < n; ++i) blockId[i] = i / BLOCK;

  for(int i = n - 1; i >= 0;){
    int currBlock = blockId[i];
    while(i >= 0 && blockId[i] == currBlock) processPos(i--, n);
  }


  while(m--){
    int x; scanf("%d", &x);
    if(x == 0){
      int a, b; scanf("%d %d", &a, &b); a--; // val de a vai pra b
      power[a] = b;
      // int curr = a;
      int curr = min(n - 1, ((blockId[a] + 1) * BLOCK) - 1);
      while(curr >= 0 && blockId[curr] == blockId[a]) processPos(curr--, n);
    }else{
      int a; scanf("%d", &a); a--;
      int ans = 0;

      while(true){
        ans += jumps2Next[a];
        if(nextBlock[a] == n) break;
        a = nextBlock[a];
      }

      int lastA;
      while(true){
        lastA = a;
        a += power[a];
        if(a >= n) break;
      }

      printf("%d %d\n", lastA + 1, ans);
    }
  }

}
