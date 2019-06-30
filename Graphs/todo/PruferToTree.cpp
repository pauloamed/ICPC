#include<bits/stdc++.h>
using namespace std;

vector<int> pseq;
int cont[101];

int main(){
  int n,x;
  printf("Prufer to Tree will find the correspondent tree to your Prufer sequence\n");
  printf("Type the number of elements in your sequence\n");
  scanf("%d", &n);
  for(int i = 0; i <= n+2; i++){
    cont[i] = 1;
  }
  printf("Type the sequence\n");
  for(int i = 0; i < n; i++){
    scanf("%d", &x);
    pseq.push_back(x);
    cont[x]++;
  }

  set<int> s;

  printf("\nThe degrees of each node in your tree are:\n");
  for(int i = 1; i <= n+2; i++){
    printf("Node %d has degree %d", i, cont[i]);
    if(cont[i] == 1){
      s.insert(i);
      printf("\t(LEAF)");
    }
    printf("\n");
  }printf("\n");

  printf("The edges in your tree are:\n");
  int va, count = 0;
  while(count < n){
    va = *s.begin();
    s.erase(s.begin());

    printf("%d %d\n", va, pseq[count]);
    if(--cont[pseq[count]] == 1){
      s.insert(pseq[count]);
    }
    count++;
  }
  printf("%d %d\n", *(s.begin()), *(++s.begin()));

}
