#include<bits/stdc++.h>
using namespace std;

vector<int> lista[101];

int deverasgrafo(int n){
  if(n == 1){
    if(lista[1][0] == 0)
      return 1;
    else
      return -1;
  }else{
    int ans = 1;
    for(int i = 0; i < n; i++){
      if(lista[n][i] < 0){
        return -1;
      }else if(lista[n][i] == 0){
        ans = min(ans,1);
      }else{
        ans = 0;
      }
    }
    return ans;
  }
}

void printg(int n){
  for(int i = n-1; i >= 0; i--)
    printf("%d ", lista[n][i]);
printf("\n");
}

void createg(int n){
  for(int i = 1; i <= n; i++)
    lista[n].push_back(lista[n+1][n-i]);
  for(int i = 0; i < lista[n+1][n]; i++)
    lista[n][n-1-i]--;
}

bool solve(int n){
  sort(lista[n].begin(),lista[n].end());
  printg(n);

  int aux = deverasgrafo(n);
  if(aux == -1){
    printf("Does not exist!\n");
    return false;
  }else if(aux == 0)
    printf("Does such graph exist?\nY/N/D\t(yes/no/don't know): ");
  else{
    printf("Exists!\n");
    return true;
  }

  char c;
  while(1){
    scanf(" %c", &c);
    switch(c){
      case 'y':
      case 'Y':
        printg(n);
        printf("Exists!\n");
        return true;
      break;
      case 'n':
      case 'N':
        printg(n);
        printf("Does not exist!\n");
        return false;
      break;
      case 'd':
      case 'D':
        createg(n-1);
        if(solve(n-1)){
          printg(n);
          printf("Exists!\n");
          return true;
        }else{
          printg(n);
          printf("Does not exist!\n");
          return false;
        }
      break;
      default:
        printf("Invalid char\n");
      break;
    }
  }
}

int main(){
  int n,x;
  printf("Havel-Haikimi algorithm solve the question whether exists\na graph with such degree sequence\n");
  printf("Type v, the number of vertices (max 100)\n");
  scanf("%d", &n);

  printf("Type the degree of each vertice\n");
  for(int i = 0; i < n; i++){
    scanf("%d", &x);
    lista[n].push_back(x);
  }
  solve(n);
}
